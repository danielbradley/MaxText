/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

/*	Win32 */

#define _ALL_SOURCE 1
//#include <unistd.h>
#include <stdlib.h>
#include <time.h>				/** time()    **/
#include <sys/types.h>
#include <sys/timeb.h>
#include "openxds/base/psa/Clock.h"

//#include <windows.h>
//#include <sys/times.h>		/** struct tms **/

struct _Clock
{
	unsigned long long start;
	unsigned long long stop;
	unsigned long long interval;
};

IClock* new_Clock()
{
	IClock* self = CRuntime_calloc( 1, sizeof( IClock ) );
	return self;
}

void free_Clock( IClock* self )
{
	CRuntime_free( self );
}

void
Clock_start( IClock* self )
{
	self->start = Clock_GetMicroSecondsSinceEpoch();
}

void
Clock_stop( IClock* self )
{
	self->stop = Clock_GetMicroSecondsSinceEpoch();
	self->interval = self->stop - self->start;
}

unsigned long long
Clock_getInterval( const IClock* self )
{
	unsigned long long ret = 0;
	unsigned long long now = Clock_GetMicroSecondsSinceEpoch();
	if ( self->interval )
	{
		ret = self->interval;
	} else {
		ret = now - self->start;
	}
	return ret;
}

/*
 *  Class Methods
 */

int Clock_GetTimeAsInt()
{
	//__time64_t ltime;
	//_time64( &ltime );
	//return ltime;
	return 0;
}

unsigned long long
Clock_GetMicroSecondsSinceEpoch()
{
	return 0;
}

unsigned long long
Clock_GetSecondsSinceEpoch()
{
	return 0;
}

unsigned long Clock_GetClockCyclesUsed()
{
	return clock();
}

unsigned long Clock_GetUserTime()
{
	return 0;
}

unsigned long Clock_GetSystemTime()
{
	return 0;
}

unsigned long Clock_GetUptime()
{
	return 0;
}
