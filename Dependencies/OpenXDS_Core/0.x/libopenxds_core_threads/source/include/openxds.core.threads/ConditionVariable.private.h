/*
 *  Copyright (C) 2004-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_THREADS_CONDITIONVARIABLE_PROTECTED_H
#define OPENXDS_CORE_THREADS_CONDITIONVARIABLE_PROTECTED_H

#include "openxds.core.base.h"
#include "openxds.core.threads.h"
#include "openxds.core.threads/ConditionVariable.h"

#include <pthread.h>

typedef struct _ConditionVariable ConditionVariable;


EXPORT	ConditionVariable* free_ConditionVariable( ConditionVariable* self );
EXPORT	bool               ConditionVariable_wait( ConditionVariable* self, IMutex* aMutex );
EXPORT	bool          ConditionVariable_timedWait( ConditionVariable* self, IMutex* aMutex, int seconds );
EXPORT	bool             ConditionVariable_signal( ConditionVariable* self );
EXPORT	bool          ConditionVariable_broadcast( ConditionVariable* self );

/* EXPORT	IConditionVariable* ConditionVariable_copy( IConditionVariable* self ); */

struct _ConditionVariable
{
	IConditionVariable super;
	bool               valid;
	pthread_cond_t     state;
	pthread_condattr_t attributes;
};

#endif
