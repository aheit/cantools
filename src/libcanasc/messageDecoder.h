#ifndef INCLUDE_MESSAGEDECODER_H
#define INCLUDE_MESSAGEDECODER_H

#include "ascReader.h"
#include <dbcModel.h>

/* signal procesing callback function */
typedef void (* signalProcCb_t)(
				const signal_t *s,
				const canMessage_t *canMessage,
				uint32 rawValue,
				double physicalValue,
				void *cbData
				);

void canMessage_decode(message_t *dbcMessage,
		       canMessage_t *canMessage,
		       signalProcCb_t signalProcCb,
		       void *cbData);

#endif
