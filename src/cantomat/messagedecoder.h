#ifndef INCLUDE_MESSAGEDECODER_H
#define INCLUDE_MESSAGEDECODER_H

/*  messagedecoder.h --  declarations for messagedecoder
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

#include "dbcmodel.h"
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
