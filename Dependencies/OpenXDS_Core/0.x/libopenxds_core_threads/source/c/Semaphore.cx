/*
 *  Copyright (C) 2004-2009 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#include "openxds.core.base.h"
#include "openxds.core.threads/ConditionVariable.h"
#include "openxds.core.threads/Mutex.h"
#include "openxds.core.threads/Semaphore.h"

struct _Semaphore
{
	int value;
	Mutex* mutex;
	ConditionVariable* cv;
};

Semaphore* new_Semaphore()
{
	Semaphore* self = CRuntime_calloc( 1, sizeof( Semaphore ) );
	self->mutex = new_Mutex();
	self->cv = new_ConditionVariable();
	self->value = 0;
	return self;
}

Semaphore* new_Semaphore_value( int aValue )
{
	Semaphore* self = CRuntime_calloc( 1, sizeof( Semaphore ) );
	self->mutex = new_Mutex();
	self->cv = new_ConditionVariable();
	self->value = aValue;
	return self;
}

void free_Semaphore( Semaphore* self )
{
	free_Mutex( self->mutex );
	free_ConditionVariable( self->cv );
	CRuntime_free( self );
}

void Semaphore_wait( Semaphore* self )
{
	Mutex_lock( self->mutex );
	{
		while ( self->value <= 0 ) {
			ConditionVariable_wait( self->cv, self->mutex );
		}
		self->value -= 1;
	}
	Mutex_unlock( self->mutex );
}

void Semaphore_signal( Semaphore* self )
{
	Mutex_lock( self->mutex );
	{
		self->value += 1;
		if ( 0 < self->value ) ConditionVariable_signal( self->cv );
	}
	Mutex_unlock( self->mutex );
}
