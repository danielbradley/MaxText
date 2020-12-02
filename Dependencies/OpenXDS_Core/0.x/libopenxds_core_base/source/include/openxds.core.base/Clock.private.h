/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_CLOCK_PRIVATE_H
#define OPENXDS_CORE_BASE_CLOCK_PRIVATE_H

#include "openxds.core.base/Clock.h"

	#ifdef __cplusplus
	namespace openxds {
		namespace core {
			namespace base {
	extern "C"
	{
	#endif

typedef struct _Clock Clock;

/*
 *  Lifecycle functions
 */
EXPORT	Clock* free_Clock( Clock* self );

/*
 *  Functions
 */
EXPORT	void               Clock_start( Clock* self );
EXPORT	void               Clock_stop( Clock* self );
EXPORT	unsigned long long Clock_getInterval( const Clock* self );

	#ifdef __cplusplus
	}
	};};};
	#endif
#endif
