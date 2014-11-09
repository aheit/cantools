#ifndef INCLUDE_MESSAGEDECODER_H
#define INCLUDE_MESSAGEDECODER_H

#include "dbcModel.h"
#include "measurement.h"

#ifdef __cplusplus
extern "C" {
#endif

/* signal procesing callback function */
typedef void (* signalProcCb_t)(const signal_t     *s,
				double              dtime,
				uint32              rawValue,
				double              physicalValue,
				void               *cbData);

void canMessage_decode(message_t      *dbcMessage,
		       canMessage_t   *canMessage,
		       sint32          timeResolution,
		       signalProcCb_t  signalProcCb,
		       void           *cbData);

#ifdef __cplusplus
}
#endif

#endif
