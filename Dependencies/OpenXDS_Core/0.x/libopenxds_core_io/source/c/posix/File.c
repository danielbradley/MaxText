/*
 *  Copyright (C) 2004-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#include "openxds.core.io/File.private.h"
#include "openxds.core.io/Directory.h"
#include "openxds.core.io/Path.h"

#include <openxds.core.base/CharString.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int File_create( const File* self )
{
	int status;
	if ( -1 != (status = creat( self->path->getNativeFormat( self->path ), S_IRWXU | S_IRWXG | S_IRWXO )) )
	{
		close( status );
		status = 1;
	} else {
		status = 0;
	}
	return status;	
}

int File_delete( const File* self )
{
	int status = 0;

	if ( 0 == unlink( self->path->getNativeFormat( self->path ) ) )
	{
		status = 1;
	}
		
	return status;
}

int File_remove( const File* self )
{
	int status = 0;

	if ( 0 == unlink( self->path->getNativeFormat( self->path ) ) )
	{
		status = 1;
	}
		
	return status;
}

int File_copyTo( const File* self, const IPath* targetPath, int force )
{
	bool status = 0;

/*
	char*  target = NULL;
	IFile* target_file = NULL;
	IDirectory* target_dir = new_Directory_path( targetPath );
	if ( target_dir->exists( target_dir ) )
	{
		target = CharString_cat3( targetPath->getCommon( targetPath ), "/", self->path->getBasename( self->path ) );
	} else {
		target = CharString_copy( targetPath->getCommon( targetPath ) );
	}

	target_file = (IFile*) new_File( target );
	if ( !File_exists( target_file ) || force )
	{
		if ( File_open( target_file, "w" ) )
		{
			byte buffer[256];
			unsigned long read;
		
			while ( (read = File_read( self, buffer, 256 )) )
			{
				File_write( target_file, buffer, read );
				status = 1;
			}
			if ( !status )
			{
				fprintf( stdout, "File.c::copyTo: could not copy data\n" );
			}
		}
		File_close( target_file );
	}
	target_dir->free( target_dir );
	target_file->free( target_file );
	free_CharString( target );	
*/
	return status;
}
