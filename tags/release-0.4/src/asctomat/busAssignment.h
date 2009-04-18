#ifndef INCLUDE_BUSASSIGNMENT
#define INCLUDE_BUSASSIGNMENT

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "messageHash.h"

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
