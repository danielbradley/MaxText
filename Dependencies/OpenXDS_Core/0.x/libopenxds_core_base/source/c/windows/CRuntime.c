/*
 *  Copyright (c) 2005-2010 Daniel Robert Bradley. All rights reserved.
 */

#include <windows.h>
#include "openxds.core.base/CRuntime.h"

void CRuntime_SleepForSeconds( unsigned int seconds )
{
	unsigned int milliseconds = seconds * 1000;
	Sleep( milliseconds );
} 

void CRuntime_SleepForMicroseconds( unsigned int microseconds )
{
	unsigned int milliseconds = microseconds / 1000;
	Sleep( milliseconds );
} 
