/*
 *  Copyright (C) 2004-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_THREADS_THREAD_PROTECTED_H
#define OPENXDS_CORE_THREADS_THREAD_PROTECTED_H

#include "openxds.core.threads/Thread.h"

#include <pthread.h>
#include <errno.h>

typedef struct _Thread Thread;

EXPORT	Thread* free_Thread( Thread* self );
EXPORT	bool    Thread_run(  Thread* self );
EXPORT	bool    Thread_wait( Thread* self );

struct _Thread
{
	IThread super;
	void*(*callback)(void*);
	void* arg;
	pthread_t      state;
	pthread_attr_t attributes;
	void*          ret;
};

#endif
