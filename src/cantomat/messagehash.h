#ifndef INCLUDE_MESSAGEHASH_H
#define INCLUDE_MESSAGEHASH_H

/*  messagehash.h --  declarations for messagehash
    Copyright (C) 2016-2017 Andreas Heitmann

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

#include "cantools_config.h"

#include <stdio.h>
#include "dbcmodel.h"
#include "hashtable.h"

typedef uint32 messageHashKey_t;
typedef struct hashtable messageHash_t;

struct hashtable *messageHash_create(message_list_t *ml);
void messageHash_free(messageHash_t *const h);

#endif
