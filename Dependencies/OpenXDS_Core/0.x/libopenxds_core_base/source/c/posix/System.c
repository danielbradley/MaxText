/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.base/CharString.h"
#include "openxds.core.base/System.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char*
System_CurrentDirectory()
{
	size_t size = 128;
	char* tmp = CRuntime_calloc( size, sizeof( char ) );

	while ( NULL == getcwd( tmp, size ) )
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
	return new_CharString( "" );
}

char*
System_Hostname()
{
	unsigned int size = 32;
	char* tmp = CRuntime_calloc( size, sizeof( char ) );

	while ( gethostname( tmp, size ) )
	{
		CRuntime_free( tmp );
		size *= 2;
		tmp = CRuntime_calloc( size, sizeof( char ) );
	}
	return tmp;
}
