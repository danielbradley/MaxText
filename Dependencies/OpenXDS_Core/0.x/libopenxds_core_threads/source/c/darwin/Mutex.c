/*
 *  Copyright (C) 2004-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#include "openxds.core.threads/Mutex.private.h"

#include <openxds.core.base.h>

#include <pthread.h>
#include <errno.h>

IMutex* new_Mutex()
{
	Mutex* self = CRuntime_calloc( 1, sizeof( Mutex ) );
	self->super.free    = (IMutex* (*)( IMutex* self )) free_Mutex;
	self->super.lock    = (bool    (*)( IMutex* self )) Mutex_lock;
	self->super.tryLock = (bool    (*)( IMutex* self )) Mutex_tryLock;
	self->super.unlock  = (bool    (*)( IMutex* self )) Mutex_unlock;
	self->super.isValid = (bool    (*)( IMutex* self )) Mutex_isValid;

	self->valid = !pthread_mutex_init( &self->state, NULL );/* &self->attributes ); */
	self->locked = 0;

	return (IMutex*) self;
}

Mutex* free_Mutex( Mutex* self )
{
	return CRuntime_free( self );
}

bool Mutex_lock( Mutex* self )
{
	if ( !self->locked )
	{
		self->locked = 1;
		return !pthread_mutex_lock( &self->state );
	}
	return 0;
}

bool Mutex_tryLock( Mutex* self )
{
	bool success = 1;
	if ( EBUSY == pthread_mutex_trylock( &self->state ) )
	{
		success = 0;
	}
	return success;
}

bool Mutex_unlock( Mutex* self )
{
	return !pthread_mutex_unlock( &self->state );
}

bool Mutex_isValid( Mutex* self )
{
	return self->valid;
}

void* Mutex_getState( IMutex* self )
{
	Mutex* mutex = (Mutex*) self;
	return &(mutex->state);
}
