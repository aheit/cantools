#ifndef INCLUDE_ASCREAD_H
#define INCLUDE_ASCREAD_H

#include <stdio.h>
#include <dbcTypes.h>
#include <time.h>

/* CAN message type */
typedef struct {
  struct timespec t; /* time stamp */
  uint8   bus;     /* can bus */
  uint16  id;      /* numeric CAN-ID */
  uint8   dlc;
  uint8   byte_arr[8];
} canMessage_t;

/* message received callback function */
typedef void (* msgRxCb_t)(canMessage_t *message, void *cbData);

/* ascRead function */
void ascReader_processFile(FILE *fp, msgRxCb_t msgRxCb, void *cbData);

#endif
