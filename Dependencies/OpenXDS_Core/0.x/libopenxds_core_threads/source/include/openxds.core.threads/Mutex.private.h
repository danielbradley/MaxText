/*
 *  Copyright (C) 2004-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_THREADS_MUTEX_PROTECTED_H
#define OPENXDS_CORE_THREADS_MUTEX_PROTECTED_H

#include "openxds.core.threads/Mutex.h"

#include <pthread.h>
#include <errno.h>

typedef struct _Mutex Mutex;

EXPORT	Mutex* free_Mutex( Mutex* self );

EXPORT	bool   Mutex_lock( Mutex* self );
EXPORT	bool   Mutex_tryLock( Mutex* self );
EXPORT	bool   Mutex_unlock( Mutex* self );

EXPORT	bool   Mutex_isValid( Mutex* self );

		void*  Mutex_getState( IMutex* self );

struct _Mutex
{
	IMutex              super;
	bool                valid;
	bool                locked;
	pthread_mutex_t     state;
	pthread_mutexattr_t attributes;
};

#endif
