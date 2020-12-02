/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.base/CRuntime.h"
#include "openxds.core.base/CharString.h"
#include "openxds.core.base/CharStringList.h"

#include <stdlib.h>

static const unsigned int DEFAULT_LIST_SIZE = 512;

char** new_CharStringList()
{
	char** self = CRuntime_calloc( DEFAULT_LIST_SIZE + 1, sizeof( char* ) );
	return self;
}

char** new_CharStringList_from( const char** list )
{
	unsigned int required_list_length = CharStringList_getLength( list ) + 1;
	char** self = CRuntime_calloc( required_list_length, sizeof( char* ) );
	char** tmp = self;

	const char** tmp_list = list;
	while( NULL != *tmp_list )
	{
		*tmp = new_CharString( *tmp_list );
		tmp++;
		tmp_list++;
	}
	tmp = NULL;
	return self;
}

char** new_CharStringList_size( int size )
{
	char** self = CRuntime_calloc( size + 1, sizeof( char* ) );
	return self;
}

char** free_CharStringList( char** self )
{
	char** tmp = self;
	while ( NULL != *tmp )
	{
		free_CharString( *tmp );
		tmp++;
	}
	return (char**) CRuntime_free( self );
}

int CharStringList_copyItem( char** self, const char* item )
{
	int status = 0;
	unsigned int i;
	for ( i=0; i < DEFAULT_LIST_SIZE; i++ )
	{
		if ( NULL == self[i] )
		{
			self[i] = CharString_copy( item );
			status = 1;
			break;
		}
	}
	return status;
}

unsigned int CharStringList_getLength( const char** self )
{
	unsigned int count = 0;
	const char** tmp = self;
	while ( NULL != *tmp )
	{
		tmp++;
		count++;
	}
	return count;
}

char* CharStringList_toCharString( const char** self )
{
	char* str = CharString_copy( "" );
	char* tmp = CharString_copy( "" );

	unsigned int i=0;
	while ( self[i] )
	{
		CRuntime_free( tmp );
		tmp = str;
		str = CharString_cat2( tmp, self[i] );
		CRuntime_free( tmp );
		tmp = str;
		str = CharString_cat2( tmp, " " );
		i++;
	}
	CRuntime_free( tmp );
	return str;
}
