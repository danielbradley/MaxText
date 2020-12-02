/*
 *  Copyright (c) 2005-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.base/CRuntime.h"

#include <unistd.h>

void CRuntime_SleepForSeconds( unsigned int seconds )
{
	sleep( seconds );
} 

void CRuntime_SleepForMicroseconds( unsigned int microseconds )
{
	usleep( microseconds );
} 
