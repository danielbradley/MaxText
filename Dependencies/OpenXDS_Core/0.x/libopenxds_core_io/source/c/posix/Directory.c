/*
 *  Copyright (C) 2004 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#include "openxds.core.io/Directory.private.h"
#include "openxds.core.io/Path.h"

#include <openxds.core.adt/ISequence.h>
#include <openxds.core.adt.std/StdADTFactory.h>
#include <openxds.core.base/CharString.h>

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int Directory_refresh( Directory* self )
{
	int status = 0;
	struct dirent* entry;
	DIR* dir;
	
	self->fileList->free( self->fileList );
	self->fileList = StdADTFactory_createSequence();

	dir = opendir( self->path->getNativeFormat( self->path ) );

	if ( dir )
	{
		while ( (entry = readdir( dir )) )
		{
			self->fileList->insertLast( self->fileList, new_CharString( entry->d_name ) );
		}
		closedir( dir );
		status = 1;
	}
	return status;
}

/*
const char** Directory_getContents( const IDirectory* self )
{
	return (const char**) self->contents;
}
*/

int Directory_create( const Directory* self )
{
	int status = 0;
	mode_t mode = S_IRWXU | S_IRWXG | S_IRWXO;
	if ( 0 == mkdir( self->path->getNativeFormat( self->path ), mode ) )
	{
		status = 1;
	}
	return status;
}

int Directory_delete( const Directory* self )
{
	int status = 0;
	if ( 0 == rmdir( self->path->getNativeFormat( self->path ) ) )
	{
		status = 1;
	}
	return status;
}

bool Directory_isDirectory( const Directory* self )
{
	int status = 0;
	DIR* dir = opendir( self->path->getNativeFormat( self->path ) );
	if ( dir )
	{
		closedir( dir );
		status = 1;
	}
	return status;
}	

bool Directory_exists( const Directory* self )
{
	int status = 0;
	DIR* dir = opendir( self->path->getNativeFormat( self->path ) );
	if ( dir )
	{
		closedir( dir );
		status = 1;
	}
	return status;
}
