/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.base/CharString.h"
#include "openxds.core.base/CharStringList.h"
#include "openxds.core.base/Process.private.h"

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>			/** fork() **/
#include <sys/wait.h>		/** waitpid() **/
#include <sys/stat.h>

typedef struct _ProcessIO
{
	char* in;
	char* out;
	char* error;
} ProcessIO;

struct _Process
{
	IProcess   super;
	char*      executable;
	char**     arguments;
	char*      searchPath;
	int        usePath;
	pid_t      pid;
	ProcessIO  io;
	int        exitStatus;
	bool       finished;
	bool       exitedNormally;
};

/*
 *	Class methods
 */
unsigned int Process_GetCurrentID()
{
	return getpid();
}

unsigned int Process_GetCurrentParentID()
{
	return getppid();
}

/*
 *	Static methods
 */
static char** addExeToArguments( const char* exe, const char** arguments );

IProcess* new_Process( const char* executable, const char** arguments )
{
	Process* self = (Process*) CRuntime_calloc( 1, sizeof( Process ) );
	self->super.free                      = (             IProcess*  (*)(       IProcess* ))              free_Process;
	self->super.start                     = (                   int  (*)(       IProcess* ))              Process_start;
	self->super.waitFor                   = (                   int  (*)(       IProcess* ))              Process_waitFor;
	self->super.setSearchPath             = (                  void  (*)(       IProcess*, const char* )) Process_setSearchPath;
	self->super.setUsePath                = (                  void  (*)(       IProcess*, bool ))        Process_setUsePath;
	self->super.setStandardIn             = (                  void  (*)(       IProcess*, const char* )) Process_setStandardIn;
	self->super.setStandardOut            = (                  void  (*)(       IProcess*, const char* )) Process_setStandardOut;
	self->super.setStandardError          = (                  void  (*)(       IProcess*, const char* )) Process_setStandardError;

	self->super.getExecutable             = (           const char*  (*)( const IProcess* ))              Process_getExecutable;
	self->super.getArguments              = (           const char** (*)( const IProcess* ))              Process_getArguments;
	self->super.getProcessID              = (         unsigned int   (*)( const IProcess* ))              Process_getProcessID;
	self->super.getSearchPath             = (           const char*  (*)( const IProcess* ))              Process_getSearchPath;
	self->super.getExitStatus             = (                  int   (*)( const IProcess* ))              Process_getExitStatus;

	self->super.hasFinished               = (                 bool   (*)( const IProcess* ))              Process_hasFinished;
	self->super.hasExitedNormally         = (                 bool   (*)( const IProcess* ))              Process_hasExitedNormally;

	self->super.getCurrentID              = (         unsigned int   (*)())                               Process_GetCurrentID;
	self->super.getCurrentParentID        = (         unsigned int   (*)())                               Process_GetCurrentParentID;

	self->executable = new_CharString( executable );
	self->arguments  = addExeToArguments( self->executable, arguments );

	return (IProcess*) self;
}

Process* free_Process( Process* self )
{
	free_CharString( self->executable );
	free_CharStringList( self->arguments );
	if ( self->searchPath ) {
		free_CharString( self->searchPath );
	}
	if ( self->io.in ) {
		free_CharString( self->io.in );
	}
	if ( self->io.out ) {
		free_CharString( self->io.out );
	}
	if ( self->io.error ) {
		free_CharString( self->io.error );
	}
	return CRuntime_free( self );
}

int Process_start( Process* self )
{
	int state = 1;
	
	self->pid = fork();
	if ( -1 == self->pid )
	{
		state = 0;
	}
	else if ( 0 == self->pid )
	{
		int in;
		int out;
		int error;
		
		if ( self->io.in )
		{
			in = open( self->io.in, O_RDONLY );
			dup2( in, STDIN_FILENO );
			close( in );
		}
		
		if ( self->io.out )
		{
			if ( -1 == (out = open( self->io.out, O_WRONLY | O_APPEND )) )
			{
				if ( -1 == (out = creat( self->io.out, S_IRWXU )) )
				{
					perror( NULL );
				}
			}
			dup2( out, STDOUT_FILENO );
			close( out );
		}
		
		if ( self->io.error )
		{
			if ( -1 == (error = open( self->io.error, O_WRONLY | O_APPEND )) )
			{
				if ( -1 == (error = creat( self->io.error, S_IRWXU )) )
				{
					perror( NULL );
				}
			}
			dup2( error, STDERR_FILENO );
			close( error );
		}

		if ( self->usePath ) {
			execvp( self->executable, (char*const*) self->arguments );
			printf( "execvp failed\n" );
			exit( -1 );
		} else  {
			execv( self->executable, (char*const*) self->arguments );
			printf( "execv failed\n" );
			exit( -1 );
		}
	}
	return state;
}

int Process_waitFor( Process* self )
{
	if ( !self->finished )
	{
		int status;
		int pid = waitpid( self->pid, &status, 0 );
		if ( self->pid == pid )
		{
			self->finished = 1;
			if ( WIFEXITED( status ) )
			{
				if ( 0 == (self->exitStatus = WEXITSTATUS( status )) )
				{
					self->exitedNormally = 1;
				}
			}
		}
	}
	return self->finished;
}

void Process_setSearchPath( Process* self, const char* aSearchPath )
{
	if ( self->searchPath ) free_CharString( self->searchPath );
	self->searchPath = new_CharString( aSearchPath );
}

void Process_setUsePath( Process* self, int aBoolean )
{
	self->usePath = aBoolean;
}

void Process_setStandardIn( Process* self, const char* location )
{
	self->io.in = CharString_copy( location );
}

void Process_setStandardOut( Process* self, const char* location )
{
	self->io.out = CharString_copy( location );
}

void Process_setStandardError( Process* self, const char* location )
{
	self->io.error = CharString_copy( location );
}

const char* Process_getExecutable( const Process* self )
{
	return self->executable;
}

const char** Process_getArguments( const Process* self )
{
	return (const char**) self->arguments;
}

unsigned int Process_getProcessID( const Process* self )
{
	return self->pid;
}

const char* Process_getSearchPath( const Process* self )
{
	return self->searchPath;
}

int	Process_getExitStatus( const Process* self )
{
	return self->exitStatus;
}

bool	Process_hasFinished( const Process* self )
{
	return self->finished;
}

bool	Process_hasExitedNormally( const Process* self )
{
	return self->exitedNormally;
}

char** addExeToArguments( const char* exe, const char** arguments )
{
	int len = CharStringList_getLength( arguments );

	char** list = new_CharStringList_size( len + 1 );
	{
		int i;

		CharStringList_copyItem( list, exe );
		for ( i = 0; i < len; i++ )
		{
			CharStringList_copyItem( list, arguments[i] );
		}
	}
	return list;
}
