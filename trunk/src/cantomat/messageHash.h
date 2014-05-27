#ifndef INCLUDE_MESSAGEHASH_H
#define INCLUDE_MESSAGEHASH_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <dbcModel.h>
#include "../hashtable/hashtable.h"

typedef uint32 messageHashKey_t;
typedef struct hashtable messageHash_t;

struct hashtable *messageHash_create(message_list_t *ml);
void messageHash_free(messageHash_t *const h);

#endif
