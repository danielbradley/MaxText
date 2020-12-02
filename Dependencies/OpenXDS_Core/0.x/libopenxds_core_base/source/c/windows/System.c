/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#include <windows.h>
#include <direct.h>
#include "openxds/base/psa/CRuntime.h"
#include "openxds/base/psa/CharString.h"
#include "openxds/base/psa/System.h"

char*
System_CurrentDirectory()
{
	int   size = 128;
	char* tmp = (char*) CRuntime_calloc( size, sizeof( char ) );

	while ( !_getcwd( tmp, size ) )
	{
		CRuntime_free( tmp );
		size *= 2;
		tmp = CRuntime_calloc( size, sizeof( char ) );
	}
	return tmp;
}

char*
System_CurrentVolume()
{
	char* current_directory = System_CurrentDirectory();
	char* volume = CharString_token( current_directory, 0, ':' );
	free_CharString( current_directory );
	return volume;
}

char*
System_Hostname()
{
	DWORD max = MAX_COMPUTERNAME_LENGTH + 1;
	char* hostname = (char*) CRuntime_calloc( max, sizeof( char ) );
	GetComputerName( hostname, &max );
	return hostname;
}
