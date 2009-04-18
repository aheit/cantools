/*  messageHash.c --  map message id to message structure
    Copyright (C) 2007-2009 Andreas Heitmann

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

static unsigned int hash_from_canid(void *t)
{
  return (unsigned int)*(messageHashKey_t *)t;
}

static int canids_equal(void *key1, void *key2)
{
  return (*(messageHashKey_t *)key1) == (*(messageHashKey_t *)key2);
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
