/*
 *  Copyright (c) 2005-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.base/CharString.h"
#include "openxds.core.base/Environment.h"
#include "openxds.core.base/Environment.private.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

static const char* EMPTY_STRING = "";

void
Environment_setEnvironmentVariable( const char* key, const char* value, bool overwrite )
{
	setenv( key, value, overwrite );
}

const char* Environment_getEnvironmentVariable( const char* variable )
{
	const char* value = getenv( variable );
	if ( !value )
	{
		value = EMPTY_STRING;
	}
	return value;
}

/*----------------------------------------------------------------------------
//	private functions
//--------------------------------------------------------------------------*/

bool
Environment_private_CheckExistance( const char* path, const char* filename )
{
	bool result = 0;
	struct stat buf;
	char* full_path = CharString_cat3( path, "/", filename );

	if ( 0 == stat( full_path, &buf ) )
	{
		result = 1;
	}
	free_CharString( full_path );
	return result;
}

bool Environment_isLink( const char* path )
{
	int type = 0;
	bool link = 0;
	struct stat info;
	lstat( path, &info );
	type = info.st_mode & S_IFMT;
	if ( S_IFLNK == type )
	{
		link = 1;
	}
	return link;
}

char* Environment_readLink( const char* path )
{
	unsigned long read = 0;
	int size = 512; /* Increased to 512 as OS X 10.5 does not seem to correctly error. */
	char* ret = NULL;
	char* tmp = calloc( size, sizeof(char) );
	while ( -1 == (read = readlink( path, tmp, size - 1 )) )
	{
		size *= 2;
		free( tmp );
		tmp = calloc( size, sizeof(char) );
	}
	tmp[read] = '\0';
	ret = new_CharString( tmp );
	free( tmp );

	return ret;
}

char Environment_getFileSeparator()
{
	return '/';
}

