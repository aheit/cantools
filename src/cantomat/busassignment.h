#ifndef INCLUDE_BUSASSIGNMENT
#define INCLUDE_BUSASSIGNMENT

/*  busassignment.h -- declarations for busassignment
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "messagehash.h"

typedef struct {
  int bus;
  char *filename;
  messageHash_t *messageHash;
} busAssignmentEntry_t;

typedef struct {
  int n;
  busAssignmentEntry_t *list; /* array of n busAssigmentEntry_t's */
} busAssignment_t;

busAssignment_t *busAssignment_create(void);
void busAssignment_associate(busAssignment_t *busAssigment,
                             int bus, char *filename);
void busAssignment_free(busAssignment_t *busAssigment);
int busAssignment_parseDBC(busAssignment_t *busAssignment);

#endif
