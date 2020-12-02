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

#include <openxds.core.base/CharString.h>
#include <openxds.core.adt/ISequence.h>
#include <openxds.core.adt.std/StdADTFactory.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

static void initialise( Directory* self )
{
	self->super.free              = (      IDirectory* (*)( IDirectory* ))                            free_Directory;
	self->super.subdirectory      = (      IDirectory* (*)( const IDirectory*, const char* name ))    Directory_getPath; 
	self->super.createAll         = (            bool  (*)( const IDirectory* ))                      Directory_createAll; 
	self->super.createDir         = (            bool  (*)( const IDirectory* ))                      Directory_create; 
	self->super.deleteDir         = (            bool  (*)( const IDirectory* ))                      Directory_delete; 
	self->super.isDirectory       = (            bool  (*)( const IDirectory* ))                      Directory_isDirectory; 
	self->super.exists            = (            bool  (*)( const IDirectory* ))                      Directory_exists; 
	self->super.containsDirectory = (            bool  (*)( const IDirectory*, const char* dirname )) Directory_containsDirectory;
	self->super.getPath           = ( const     IPath* (*)( const IDirectory* ))                      Directory_getPath;
	self->super.getFiles          = ( const ISequence* (*)( const IDirectory* ))                      Directory_getFiles;
}

IDirectory*
new_Directory( const char* location )
{
	Directory* self  = CRuntime_calloc( 1, sizeof( Directory ) );
	initialise( self );
	
	self->path      = new_Path( location );
	self->fileList  = StdADTFactory_createSequence();

	if ( Directory_exists( self ) )
	{
		Directory_refresh( self );
	}

	return (IDirectory*) self;
}

IDirectory*
new_Directory_path( const IPath* location )
{
	Directory* self = CRuntime_calloc( 1, sizeof( Directory ) );
	initialise( self );

	self->path      = location->copy( location );
	self->fileList  = StdADTFactory_createSequence();

	if ( Directory_exists( self ) )
	{
		Directory_refresh( self );
	}

	return (IDirectory*) self;
}

Directory*
free_Directory( Directory* self )
{
	if ( self->path )     self->path     = self->path->free( self->path );
	if ( self->fileList ) self->fileList = self->fileList->free( self->fileList );

	return (Directory*) CRuntime_free( self );
}

Directory*
Directory_subdirectory( const Directory* self, const char* name )
{
	const char* path    = self->path->getCommon( self->path );
	char* path_and_name = path_and_name = CharString_cat3( path, "/", name );
	Directory* dir      = (Directory*) new_Directory( path_and_name );
	free_CharString( path_and_name );
	return dir;
}

const ISequence*
Directory_getFiles( const Directory* self )
{
	return self->fileList;
}

const IPath*
Directory_getPath( const Directory* self )
{
	return self->path;
}

bool
Directory_createAll( const Directory* self )
{
	int status = 1;
	if ( !Directory_exists( self ) )
	{
		const IPath* path   = Directory_getPath( self );
		Directory*   parent = (Directory*) new_Directory( path->getDirname( path ) );

		if ( !Directory_exists( parent ) )
		{
			status &= Directory_createAll( parent );
		}
		if ( status )
		{
			status &= Directory_create( self );
			//IDirectory* subdir = Directory_subdirectory( parent, Path_getBasename( Directory_getRealPath( self ) ) );
			//status &= Directory_create( subdir );
		}
	}
	return status;
}

bool
Directory_containsDirectory( const Directory* self, const char* dirname )
{
	int result         = 0;
	const IPath* path  = Directory_getPath( self );
	char* dir_path     = CharString_cat3( path->getCommon( path ), "/", dirname );
	Directory* src_dir = (Directory*) new_Directory( dir_path );

	if ( Directory_exists( src_dir ) )
	{
		result = 1;
	}

	free_Directory( src_dir );
	free_CharString( dir_path );
	return result;
}
