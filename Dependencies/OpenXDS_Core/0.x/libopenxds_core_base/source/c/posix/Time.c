/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.base/Time.private.h"

#include "openxds.core.base/CharString.h"
#include "openxds.core.base/CRuntime.h"

#include <stdlib.h>
#include <time.h>			/** times()    **/
#include <sys/times.h>		/** struct tms **/
#include <sys/time.h>		/** struct timeval timezone **/

#include <stdlib.h>

struct _Time
{
	ITime super;
	size_t    sinceEpoch;
	char*     textual;
};

ITime* Time_Now()
{
	return new_Time( time( NULL ) );
}

Time* Time_copy( const Time* self )
{
	return (Time*) new_Time( Time_getSecondsSinceEpoch( self ) );
}

ITime* new_Time( unsigned long long secondsSinceEpoch )
{
	Time* self = CRuntime_calloc( 1, sizeof( Time ) );
	self->super.free                 = (             ITime* (*)(       ITime* )) free_Time;
	self->super.copy                 = (             ITime* (*)( const ITime* )) Time_copy;
	self->super.now                  = (             ITime* (*)( const ITime* )) Time_Now;
	self->super.getTextual           = (        const char* (*)( const ITime* )) Time_getTextual;
	self->super.getSecondsSinceEpoch = ( unsigned long long (*)( const ITime* )) Time_getSecondsSinceEpoch;

	time_t t = (time_t) secondsSinceEpoch;
	self->sinceEpoch = t;
	self->textual = new_CharString_format_args( "%64s", "" );
	ctime_r( &t, self->textual );

	/*	This gets rid of the annoying newline */
	self->textual[CharString_getLength( self->textual ) - 1] = '\0';
	
	return (ITime*) self;
}

Time* free_Time( Time* self )
{
	free_CharString( self->textual );
	return CRuntime_free( self );
}

const char* Time_getTextual( const Time* self )
{
	return self->textual;
}

unsigned long long Time_getSecondsSinceEpoch( const Time* self )
{
	return self->sinceEpoch;
}
