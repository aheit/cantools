#include "config.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <matio.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "mdfcg.h"
#include "mdffilter.h"
#include "mdffile.h"
#include "mdfdg.h"

#define CREATE_LNK(mdf, type, obj) link_t obj = create_link(mdf,sizeof(type))

#define CREATE_LINK(mdf, type, obj) \
  link_t obj##_link;						\
  type *obj = create_link(mdf, sizeof(type), &(obj##_link))

void *
create_link(mdf_t *mdf, size_t objsize, link_t *lnk)
{
  char *obj;

  mdf->base = realloc(mdf->base, mdf->size + objsize);
  assert(mdf->base);
  *lnk = mdf->size;
  obj = mdf->base + mdf->size;
  mdf->size += objsize;
  return obj;
}

link_t
create_id_block(mdf_t *mdf)
{
  CREATE_LINK(mdf, id_block_t, id_block);

  strncpy(id_block->file_identifier,"FILE-ID ",8);
  strncpy(id_block->format_identifier,"FORM-ID ",8);
  strncpy(id_block->program_identifier,"PROG-ID ",8);
  id_block->byte_order = 0;
  id_block->floating_point_format = 0;
  id_block->version_number = 0;
  id_block->reserved1 = 0;
  id_block->reserved2[0] = 0;
  id_block->reserved2[1] = 0;
  memset(id_block->reserved3,0,sizeof(id_block->reserved3));

  return id_block_link;
}

link_t
create_dg_block(mdf_t *mdf)
{
  CREATE_LINK(mdf, dg_block_t, dg_block);

  dg_block->block_identifier[0] = 'D';
  dg_block->block_identifier[1] = 'G';
  dg_block->block_size = sizeof(dg_block);
  dg_block->link_next_dg_block = 0;
  dg_block->link_cg_block = 0;
  dg_block->link_reserved = 0;
  dg_block->link_dr_block = 0;
  dg_block->number_channel_groups = 1;
  dg_block->number_record_ids = 1;

  return dg_block_link;
}

int
main(int argc, char **argv)
{
  link_t dg_block_link;
  CREATE(mdf_t, mdf);

  mdf->size = 0;
  mdf->base = NULL;
  mdf->verbose_level = 0;
  mdf->fd = -1;

  create_id_block(mdf);
  dg_block_link = create_dg_block(mdf);
}
