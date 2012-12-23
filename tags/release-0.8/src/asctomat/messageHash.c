/*  messageHash.c --  map message id to message structure
    Copyright (C) 2007-2011 Andreas Heitmann

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
#include <dbcModel.h>
#include "messageHash.h"
#include "../hashtable/hashtable.h"
#include "../hashtable/hashtable_itr.h"

/*
 * J1939 extended message decomposition
 * http://www.can-wiki.info/SaeJ1939
 */
const uint32 mask_ext = 0x80000000UL;
const uint32 mask_29  = 0x1FFFFFFFUL;
const uint32 mask_11  = 0x000007FFUL;
const uint32 mask_pri = 0x1C000000UL; /* Priority */
const uint32 mask_pgn = 0x03FFFF00UL; /* Parameter Group Number */
const uint32 mask_res = 0x02000000UL; /* Reserved */
const uint32 mask_dp  = 0x01000000UL; /* Data Page */
const uint32 mask_pf  = 0x00FF0000UL; /* PDU Format */
const uint32 mask_ps  = 0x0000FF00UL; /* PDU Specific */
const uint32 mask_sad = 0x000000FFUL; /* Source Address */

/* hash function for canIDs */
static unsigned int hash_from_canid(void *keyp)
{
  const messageHashKey_t key = *(messageHashKey_t *)keyp;

  //  printf("key = %lx, key & mask_ext = %lx, key & ~mask_11 = %lx\n",key, key&mask_ext, key&~mask_11);
  if(key & mask_ext) {         /* ext bit set? */
    //    printf("                      B\n");
    return key & mask_pgn;
  } else if(key & ~mask_11) {  /* 29 bit message? */
    //    printf("                                           C\n");
    return key & mask_pgn;
  } else {
    //    printf("  A\n");
    return key;
  }
}

static int canids_equal(void *key1p, void *key2p)
{
  const messageHashKey_t key1 = *(messageHashKey_t *)key1p;
  const messageHashKey_t key2 = *(messageHashKey_t *)key2p;
  int eq;

  /* J1939 extended message? */
  if((key1 & mask_ext) || (key2 & mask_ext)) {
    /* mask out priority and source */
    eq = ((key1 & mask_pgn) == (key2 & mask_pgn));
  } else {
    eq = (key1 == key2);
  }
  return eq;
}

struct hashtable *messageHash_create(message_list_t *message_list)
{
  struct hashtable *h;

  h = create_hashtable(16, hash_from_canid, canids_equal);

  if(h != NULL) {
    for(message_list = message_list;
        message_list != NULL;
        message_list = message_list->next) {
      message_t *message = message_dup(message_list->message);

      /*
       * id needs to be allocated, because hashtable_destroy wants to
       * free it :(
       */
      messageHashKey_t *key = malloc(sizeof(messageHashKey_t));
      *key = message->id;
      hashtable_insert(h, key, message);
    }
  } else {
    fprintf(stderr, "error: could not create message hash.\n");
  }

  return h;
}

void messageHash_free(struct hashtable *const h)
{
  if(h != NULL) {
    if (hashtable_count(h) > 0) {
      struct hashtable_itr *itr = hashtable_iterator(h);
      do {
        message_t *m = hashtable_iterator_value(itr);
        message_free(m);
      } while (hashtable_iterator_advance(itr));
      free(itr);
    }
    hashtable_destroy(h, 0);
  }
}
