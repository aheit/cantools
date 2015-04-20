/*  mdfcg.c --  access MDF channel groups
    Copyright (C) 2012-2015 Andreas Heitmann

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <assert.h>
#include "mdfcg.h"
#include "mdfcn.h"
#include "mdfmodel.h"

/* declaration of local functions */
static void
mdfProcessChannelGroup(const mdf_t *const mdf,
                       const filter_t *const filter,
                       const cg_block_t *const cg_block,
                       const double *const cg_decoded,
                       mdfSignalCb_t const mdfSignalCb,
                       const void *const cbData);

/* find time channel of channel group */
cn_block_t *
find_time_channel(mdf_t *mdf, cg_block_t *cg_block)
{
  cn_block_t *cn_block;
  int icn;
  cn_block_t *time_channel = NULL;

  for( cn_block = cn_block_get(mdf, cg_block->link_cn_block)      , icn=0;
       cn_block != NULL;
       cn_block = cn_block_get(mdf, cn_block->link_next_cn_block), icn++) {
    if(cn_block->channel_type == 1) {
      time_channel = cn_block;
      break;
    }
  }
  return time_channel;
}

static void
mdfProcessChannelGroup(const mdf_t *const mdf,
                       const filter_t *const filter,
                       const cg_block_t *const cg_block,
                       const double *const cg_decoded,
                       mdfSignalCb_t const mdfSignalCb,
                       const void *const cbData)
{
  cn_block_t *cn_block;
  uint16_t icn;
  const double *time = NULL;

  /* copy time channel */
  for( cn_block = cn_block_get(mdf, cg_block->link_cn_block) , icn=0;
       cn_block;
       cn_block = cn_block_get(mdf, cn_block->link_next_cn_block), icn++) {
    if(cn_block->channel_type == 1) {
      time = &cg_decoded[icn*cg_block->number_of_records];
    }
  }
  assert(time != NULL);

  /* copy value channels */
  for( cn_block = cn_block_get(mdf, cg_block->link_cn_block) , icn=0;
       cn_block;
       cn_block = cn_block_get(mdf, cn_block->link_next_cn_block), icn++) {
    if(cn_block->channel_type == 0) {
      const double *const value = &cg_decoded[icn*cg_block->number_of_records]; 
      mdfProcessChannel(mdf, cg_block, cn_block, filter, time, value,
                        mdfSignalCb, cbData);
    }
  }
}

/* prochess channel groups */
void
mdfProcessChannelGroupsUnsorted(const mdf_t *const mdf,
                                const filter_t *const filter,
                                const link_t cglink,
                                const uint16_t number_record_ids,
                                const uint8_t *const data_base,
                                mdfSignalCb_t const mdfSignalCb,
                                const void *const cbData)
{
  uint16_t version_number = id_block_get(mdf)->version_number;
  cg_block_t *cg_block;
  uint32_t nbytes = 0;
  uint16_t icg;

  struct {
    uint16_t record_size;
    int      filter_pass;
  } lookup[256];

  /* clean lookup table */
  for(icg = 0; icg < 256 ; icg++) {
    lookup[icg].record_size = 0;
    lookup[icg].filter_pass = 0;
  } 

  /* build lookup table for channels */
  for( cg_block = cg_block_get(mdf, cglink)                      , icg=0;
       cg_block;
       cg_block = cg_block_get(mdf, cg_block->link_next_cg_block), icg++) {

    /* store record size */
    lookup[cg_block->record_id].record_size = cg_block->record_size;

    /* check if channel group contains any channel which passes the filter */
    lookup[cg_block->record_id].filter_pass =
      filter_test_channel_group(mdf,filter, cg_block);
  }

  /* determine size of data record block */
  for( cg_block = cg_block_get(mdf, cglink)                      , icg=0;
       cg_block;
       cg_block = cg_block_get(mdf, cg_block->link_next_cg_block), icg++) {
    nbytes += (number_record_ids + cg_block->record_size)
      *cg_block->number_of_records;
  }
  if(mdf->verbose_level >= 2) {
    printf("data record has %lu bytes\n",(unsigned long)nbytes);
  }

  /* for all channel groups */
  for( cg_block = cg_block_get(mdf, cglink)                      , icg=0;
       cg_block;
       cg_block = cg_block_get(mdf, cg_block->link_next_cg_block), icg++) {

    /* if channel in channel group passes filter */
    if(lookup[cg_block->record_id].filter_pass) {

      /* decoded channel group */
      double *cg_decoded = (double *)malloc(  (size_t)cg_block->number_channels
                                            * (size_t)cg_block->number_of_records
                                            * sizeof(double));
      const uint8_t *input; 
      uint32_t ibytes;
      uint32_t irecord;

      assert(cg_decoded != NULL);
      if(mdf->verbose_level >= 1) {
        printf("channel group %hu\n", (unsigned short)icg);
      }

      /* for all data records */
      irecord = 0;

      for(input = data_base, ibytes = 0, irecord = 0; ibytes < nbytes; ) {
        uint16_t icn;
        cn_block_t *cn_block;
        uint8_t record_id;

        record_id = *input++;
        
        /* matching record? */
        if(record_id == cg_block->record_id) {

          /* for all channels */
          for( cn_block = cn_block_get(mdf, cg_block->link_cn_block) , icn=0;
               cn_block;
               cn_block = cn_block_get(mdf, cn_block->link_next_cn_block), icn++) {
            uint32_t offset = cn_block->first_bit/8;
            if(version_number >= 300) {
              offset += cn_block->additional_byte_offset;
            }
            if(mdf->verbose_level >= 3) {
              printf("input = %p, offset = %x (%x, %x)\n",
                     input, offset,  cn_block->additional_byte_offset,
                     cn_block->first_bit );
            }
            const double value = mdf_signal_convert(&input[offset], mdf, cn_block);
            const size_t index = icn*cg_block->number_of_records + irecord;

            /* extract signal */
            cg_decoded[index] = value;
           
            if(mdf->verbose_level >= 3) {
              printf("%hu %lu %lu %hu %u %g\n",
                     (unsigned short)icg,
                     (unsigned long)ibytes, 
                     (unsigned long)irecord,
                     (unsigned short)icn,
                     (unsigned int)index,
                     value);
            }
          } /* for all channels */

          irecord++;
        }

        /* advance one record */
        input += lookup[record_id].record_size;
        if(number_record_ids == 2) {
          input++;
        }
        ibytes += lookup[record_id].record_size + number_record_ids;
      } /* for all data records */

      /* process channel group */
      mdfProcessChannelGroup(mdf, filter, cg_block, cg_decoded,
                             mdfSignalCb, cbData);

      free(cg_decoded);
    } /* if channel in channel group passes filter */
  } /* for all channel groups */
}

void
mdfProcessChannelGroupsSorted(const mdf_t *const mdf,
                              const filter_t *const filter,
                              link_t link,
                              uint16_t number_record_ids,
                              uint8_t *data,
                              mdfSignalCb_t const mdfSignalCb,
                              const void *const cbData)
{
  cg_block_t *cg_block;
  uint16_t icg;

  /* loop over all channel groups */
  for( cg_block = cg_block_get(mdf, link)                        , icg=0;
       cg_block;
       cg_block = cg_block_get(mdf, cg_block->link_next_cg_block), icg++) {
    const char *comment = tx_block_get_text(mdf, cg_block->link_comment);

    if(mdf->verbose_level >= 2) {
      if(comment == NULL) comment = "(null)";
      printf("  CGBLOCK %hu, nCH=%hu, rec_id=%hu, nRec=%lu, szRec=%hu, c=%s\n",
             (unsigned short)icg,
             (unsigned short)cg_block->number_channels,
             (unsigned short)cg_block->record_id,
             (unsigned long)cg_block->number_of_records,
             (unsigned short)cg_block->record_size,
             comment);
    }
    /* loop over all channels in current channel group */
    mdfProcessChannelsSorted(mdf,
                             filter,
                             cg_block->link_cn_block,
                             cg_block->number_of_records,
                             number_record_ids,
                             cg_block->record_size,
                             data,
                             mdfSignalCb,
                             cbData);
  }
}
