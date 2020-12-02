/*
 *  Copyright (C) 2004-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_THREADS_CONDITIONVARIABLE_H
#define OPENXDS_CORE_THREADS_CONDITIONVARIABLE_H

#include "openxds.core.threads/Mutex.h"
#include <openxds.core.base.h>
#include <openxds.core.threads.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace threads {
		extern "C"
		{
	#endif

struct _IConditionVariable
{
	IConditionVariable*      (*free)( IConditionVariable* self );
	bool                   (*signal)( IConditionVariable* self );
	bool                (*broadcast)( IConditionVariable* self );
	bool                     (*wait)( IConditionVariable* self, IMutex* aMutex );
	bool                (*timedWait)( IConditionVariable* self, IMutex* aMutex );
};

EXPORT	IConditionVariable* new_ConditionVariable(void);


	#ifdef __cplusplus
		}
		};};};
	#endif
#endif
