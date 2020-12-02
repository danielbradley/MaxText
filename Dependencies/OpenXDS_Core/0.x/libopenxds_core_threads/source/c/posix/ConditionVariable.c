/*
 *  Copyright (C) 2004-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#include "openxds.core.threads/ConditionVariable.private.h"
#include "openxds.core.threads/Mutex.private.h"

#include <openxds.core.base.h>

#include <pthread.h>
#include <sys/time.h>


IConditionVariable* new_ConditionVariable()
{
	ConditionVariable* self = CRuntime_calloc( 1, sizeof( ConditionVariable          ));
	self->super.free        = (IConditionVariable* (*)( IConditionVariable*          )) free_ConditionVariable;
	self->super.signal      = (              bool  (*)( IConditionVariable*          )) ConditionVariable_signal;
	self->super.broadcast   = (              bool  (*)( IConditionVariable*          )) ConditionVariable_broadcast; 
	self->super.wait        = (              bool  (*)( IConditionVariable*, IMutex* )) ConditionVariable_wait;
	self->super.timedWait   = (              bool  (*)( IConditionVariable*, IMutex* )) ConditionVariable_timedWait;
	
	self->valid = !pthread_cond_init( &self->state, &self->attributes );

	return (IConditionVariable*) self;
}

ConditionVariable* free_ConditionVariable( ConditionVariable* self )
{
	pthread_cond_destroy( &self->state );
	return (ConditionVariable*) CRuntime_free( self );
}

bool ConditionVariable_signal( ConditionVariable* self )
{
	return !pthread_cond_signal( &self->state );
}

bool ConditionVariable_broadcast( ConditionVariable* self )
{
	return !pthread_cond_broadcast( &self->state );
}

bool ConditionVariable_wait( ConditionVariable* self, IMutex* aMutex )
{
	pthread_mutex_t* mutex_state = (pthread_mutex_t*) Mutex_getState( aMutex );
	return !pthread_cond_wait( &self->state, mutex_state );
}

bool ConditionVariable_timedWait( ConditionVariable* self, IMutex* aMutex, int seconds )
{
	struct timeval now;
	struct timespec timeout;
	struct timezone* tz = NULL;
	gettimeofday( &now, tz );
	
	timeout.tv_sec = now.tv_sec + seconds;
	timeout.tv_nsec = now.tv_usec * 1000;
	
	pthread_mutex_t* mutex_state = (pthread_mutex_t*) Mutex_getState( aMutex );
	return !pthread_cond_timedwait( &self->state, mutex_state, &timeout );
}
