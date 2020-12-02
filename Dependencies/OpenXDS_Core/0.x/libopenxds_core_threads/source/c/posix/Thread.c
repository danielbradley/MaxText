/*
 *  Copyright (C) 2004-2009 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#include "openxds.core.base.h"
#include "openxds.core.threads/Thread.private.h"

#include <pthread.h>

IThread* new_Thread( void*(*startRoutine)(void*), void* argument )
{
	Thread* self = CRuntime_calloc( 1, sizeof( Thread ) );
	self->super.free = (IThread* (*)( IThread* )) free_Thread;
	self->super.run  = (   bool  (*)( IThread* )) Thread_run;
	self->super.wait = (   bool  (*)( IThread* )) Thread_wait;

	self->callback   = startRoutine;
	self->arg        = argument;
	pthread_attr_init( &self->attributes );

	return (IThread*) self;
}

Thread* free_Thread( Thread* self )
{
	return CRuntime_free( self );
}

bool Thread_run( Thread* self )
{
	return !pthread_create( &self->state, &self->attributes, self->callback, self->arg );
}

bool Thread_wait( Thread* self )
{
	return !pthread_join( self->state, &self->ret );
}

