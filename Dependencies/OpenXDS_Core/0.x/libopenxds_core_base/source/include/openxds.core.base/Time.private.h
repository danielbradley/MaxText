/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_TIME_PRIVATE_H
#define OPENXDS_CORE_BASE_TIME_PRIVATE_H

#include "openxds.core.base/Time.h"

	#ifdef __cplusplus
	namespace openxds {
		namespace core {
			namespace base {
	extern "C"
	{
	#endif

typedef struct _Time Time;

/*
 *  Lifecycle functions
 */
EXPORT	Time*                              free_Time(       Time* self );
EXPORT	Time*                              Time_copy( const Time* self );
EXPORT	const char*                  Time_getTextual( const Time* self );
EXPORT  unsigned long long Time_getSecondsSinceEpoch( const Time* self );

	#ifdef __cplusplus
	}
	};};};
	#endif
#endif
