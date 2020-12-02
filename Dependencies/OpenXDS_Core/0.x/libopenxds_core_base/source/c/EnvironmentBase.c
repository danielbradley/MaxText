/*
 *  Copyright (c) 2005-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.base/Environment.private.h"

#include "openxds.core.base/CRuntime.h"
#include "openxds.core.base/CharString.h"
#include "openxds.core.base/System.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

struct _Environment
{
	IEnvironment super;
	char*        executableName;
	char*        executableLocation;
	char*        directoryContainingExecutable;
	char*        path;
};

extern bool  Environment_private_CheckExistance( const char* path, const char* filename );

IEnvironment* new_Environment( const char* argv_0 )
{
	return new_Environment_using( argv_0, Environment_getFileSeparator() );
}

IEnvironment* new_Environment_using( const char* argv_0, char fileSeparator )
{
	Environment* self = (Environment*) CRuntime_calloc( 1, sizeof( Environment ) );

	self->super.free                             = (IEnvironment* (*)(       IEnvironment* self )) free_Environment;
	self->super.searchPathFor                    = (        char* (*)( const IEnvironment* self, const char* file )) Environment_searchPathFor;
	self->super.getExecutableName                = (  const char* (*)( const IEnvironment* self )) Environment_getExecutableName;
	self->super.getExecutableLocation            = (  const char* (*)( const IEnvironment* self )) Environment_getExecutableLocation;
	self->super.getDirectoryContainingExecutable = (  const char* (*)( const IEnvironment* self )) Environment_getDirectoryContainingExecutable;
	self->super.getPath                          = (  const char* (*)( const IEnvironment* self )) Environment_getPath;
	self->super.getEnvironmentVariable           = (  const char* (*)( const char* variable ))     Environment_getEnvironmentVariable;
	self->super.setEnvironmentVariable           = (        void  (*)( const char* key, const char* value, bool overwrite )) Environment_setEnvironmentVariable;
	self->super.getFileSeparator                 = (        char  (*)())                                                     Environment_getFileSeparator;
	
	Environment_initialise( self, argv_0, fileSeparator );

	return (IEnvironment*) self;
}

void
Environment_initialise( Environment* self, const char* argv_0, char fileSeparator )
{
	char fs       = fileSeparator;
	char ifs[2]   = { fs, '\0' };
	int  argv_len = CharString_getLength( argv_0 );

	if ( 0 < CharString_getLength( argv_0 ) )
	{
		char* exe_dirname = NULL;

		self->path           = new_CharString( getenv( "PATH" ) );
		self->executableName = CharString_basename_using( argv_0, fs );

		exe_dirname = CharString_dirname_using( argv_0, fs );
		{
			if ( 0 == CharString_compare( exe_dirname, "." ) )
			{
				/*	If dirname( argv[0] ) is . either the executable was run
				//	from the current directory, or via the $PATH.
				*/
				
				if ( CharString_startsWith( argv_0, "." ) )
				{
					self->directoryContainingExecutable = System_CurrentDirectory();
				} else {
					self->directoryContainingExecutable = Environment_searchPathFor( self, self->executableName );
				}
				
				if ( NULL == self->directoryContainingExecutable )
				{
					/*
					//	Could not find executable on path!, assuming it is because program
					*/
					fprintf( stdout, "Could not find executable directory! assuming current directory!\n" );
					self->directoryContainingExecutable = System_CurrentDirectory();
				}
			}
			else if ( fs == argv_0[0] )
			{
				self->directoryContainingExecutable = new_CharString( exe_dirname );
			}
			else if ( (argv_len > 3) && (':' == argv_0[1]) && ('\\' == argv_0[2]) )
			{
				self->directoryContainingExecutable = new_CharString( exe_dirname );
			}
			else if ( exe_dirname )
			{
				char* current = System_CurrentDirectory();
				self->directoryContainingExecutable = CharString_cat3( current, ifs, exe_dirname );
				free_CharString( current );
			}
		}
		free_CharString( exe_dirname );

		self->executableLocation = CharString_cat3( self->directoryContainingExecutable, ifs, self->executableName );

		/*
		//	Now need to determine if exe location is link if so find where it points
		//	and reset
		*/
		
		while ( Environment_isLink( self->executableLocation ) )
		{
			char* link = Environment_readLink( self->executableLocation );
			free_CharString( self->executableLocation );
			if ( fs == link[0] )
			{
				self->executableLocation = new_CharString( link );
			} else {
				self->executableLocation = CharString_cat3( self->directoryContainingExecutable, ifs, link );
			}
			{
				char* tmp = CharString_dirname( self->executableLocation );
				free_CharString( self->directoryContainingExecutable );
				self->directoryContainingExecutable = new_CharString( tmp );
				free_CharString( tmp );
			}
		}

	} else {
		abort();
	}
}

Environment* free_Environment( Environment* self )
{
	if ( self->executableName )                free_CharString( self->executableName );
	if ( self->executableLocation )            free_CharString( self->executableLocation );
	if ( self->directoryContainingExecutable ) free_CharString( self->directoryContainingExecutable );
	if ( self->path )                          free_CharString( self->path );

	return (Environment*) CRuntime_free( self );
}

char*
Environment_searchPathFor( const Environment* self, const char* file )
{
	char* dir    = NULL;
	int   last   = 0;
	int   length = CharString_getLength( self->path );
	
	int i;
	for ( i=0; i <= length; i++ )
	{
		switch ( self->path[i] )
		{
		case ':':
		case '\0':
			if ( (last+1) < i )
			{
				char* p = CharString_substring( self->path, last, i-1 );
				if ( Environment_private_CheckExistance( p, file ) )
				{
					dir = p;
					i = length; /* exit loop */
				} else {
					free_CharString( p );
					last = i+1;
				}
			}
			break;
		}
	}
	return dir;
}

const char*
Environment_getExecutableName( const Environment* self )
{
	return self->executableName;
}

const char*
Environment_getExecutableLocation( const Environment* self )
{
	return self->executableLocation;
}

const char*
Environment_getDirectoryContainingExecutable( const Environment* self )
{
	return self->directoryContainingExecutable;
}

const char*
Environment_getPath( const Environment* self )
{
	return self->path;
}
