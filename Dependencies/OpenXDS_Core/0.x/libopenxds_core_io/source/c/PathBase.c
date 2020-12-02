/*
 *  Copyright (C) 2004-2011 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#include "openxds.core.io/Path.private.h"

#include <openxds.core.adt/ISequence.h>
#include <openxds.core.adt.std/StdADTFactory.h>
#include <openxds.core.base/CharString.h>
#include <openxds.core.base/CRuntime.h>
#include <openxds.core.base/System.h>

#include <string.h>
#include <unistd.h>
#include <ctype.h>

static void Path_initialise( Path* self, const char* location );
//static void new_Path_UNC( Path* self, const char* location );
static void new_Path_URL( Path* self, const char* location );
//static void new_Path_WinPOSIX_dynamic( Path* self, const char* location );
static void new_Path_WinPOSIX( Path* self, const char* location );

static void  Path_setVolume( Path* self, char* volume );
static char* Path_extractBasename( const char* common );
static char* Path_extractDirname( const char* common );
static char* Path_extractExtension( const char* common );
static char* Path_toNative( const char* common );

static ISequence* collapseIntoSequence( const char* path );

struct _Path
{
	IPath super;
	char* original;
	char* protocol;
	char* hostname;
	char* volume;
	char* common;

	char* condensed;
	char* absolute;
	char* extension;

	char* dirname;
	char* basename;

	char* native;

/*	char* unc;
//	char* url;
*/
	int   type;
};

IPath* Path_GetCurrentDirectory()
{
	IPath* path;
	char* current_dir = (char*) CRuntime_calloc( 1024, sizeof( char ) );
	current_dir       = getcwd( current_dir, 1024 );
	path = new_Path( current_dir );
	CRuntime_free( current_dir );
	return path;
}

IPath* new_Path( const char* location )
{
	Path* self = CRuntime_calloc( 1, sizeof( Path ) );

	self->super.currentDirectory       = (IPath*      (*) ())              Path_GetCurrentDirectory;
	self->super.free                   = (IPath*      (*) (       IPath* )) free_Path;
	self->super.copy                   = (IPath*      (*) ( const IPath* )) Path_copy;
	self->super.getCommon              = (const char* (*) ( const IPath* )) Path_getCommon;
	self->super.getCondensed           = (const char* (*) ( const IPath* )) Path_getCondensed;
	self->super.getProtocol            = (const char* (*) ( const IPath* )) Path_getProtocol;
	self->super.getHostname            = (const char* (*) ( const IPath* )) Path_getHostname;
	self->super.getVolume              = (const char* (*) ( const IPath* )) Path_getVolume;
	self->super.getDirname             = (const char* (*) ( const IPath* )) Path_getDirname;
	self->super.getBasename            = (const char* (*) ( const IPath* )) Path_getBasename;
	self->super.getExtension           = (const char* (*) ( const IPath* )) Path_getExtension;
	self->super.getAbsolute            = (const char* (*) ( const IPath* )) Path_getAbsolute;
	self->super.getNativeFormat        = (const char* (*) ( const IPath* )) Path_getNativeFormat;
	self->super.getType                = (      int   (*) ( const IPath* )) Path_getType;
/*	self->super.getURL                 = (const char* (*) ( const IPath* )) Path_getURL; */

	self->super.hasExtension           = (bool        (*) ( const IPath*, const char* ext )) Path_hasExtension;
	self->super.isAbsolute             = (bool        (*) ( const IPath* )) Path_isAbsolute;

	self->super.getFileSeparator       = (char        (*) ( const IPath* )) Path_GetFileSeparator;
	self->super.condensePath           = (char*       (*) ( const char* location )) Path_condensePath;
	self->super.convertToNative        = (char*       (*) ( const char* location )) Path_convertToNative;
	
	Path_initialise( self, location );
	
	return (IPath*) self;
}

Path* free_Path( Path* self )
{
	self->original  = free_CharString( self->original );
	self->protocol  = free_CharString( self->protocol );
	self->hostname  = free_CharString( self->hostname );
	self->volume    = free_CharString( self->volume );
	self->common    = free_CharString( self->common );
	self->absolute  = free_CharString( self->absolute );
	self->basename  = free_CharString( self->basename );
	self->condensed = free_CharString( self->condensed );
	self->dirname   = free_CharString( self->dirname );
	self->extension = free_CharString( self->extension );
	self->native    = free_CharString( self->native );
/*	self->unc       = free_CharString( self->unc );
//	self->url       = free_CharString( self->url );
*/
	return (Path*) CRuntime_free( self );
}

void
Path_initialise( Path* self, const char* location )
{
	/*
	//	URL		://		file://HOSTNAME/C:/home/Johnny/documents		/HOSTNAME/home/
	//	POSIX			/home/Johnny/documents				Johnny\documents

	//	UNC		\\		\\\C\home\Johnny\documents
	//	WINDOWS	:		C:\home\Johnny\documents			C:Johnny\documents
	*/
	
	if ( CharString_contains( location, "://" ) )
	{
		new_Path_URL( self, location );
	}
/*
//	else if ( CharString_contains( location, "\\\\" ) || CharString_contains( location, "//" ) )
//	{
//		return new_Path_UNC( location );
//	}
*/
	else
	{
		new_Path_WinPOSIX( self, location );
	}

	self->basename  = Path_extractBasename( self->absolute );
	self->dirname   = Path_extractDirname( self->absolute );
	self->extension = Path_extractExtension( self->condensed );
	self->native    = Path_toNative( self->common );
}




//
void
new_Path_URL( Path* self, const char* location )
{
	/*
	//	URL				file://hostname/C:/home/Johnny/documents		/HOSTNAME/home/
	*/
	
	unsigned int pci;
	unsigned int hsi;
	unsigned int vci;
	unsigned int psi;

	self->type = OPENXDS_CORE_IO_TYPE_NONE;

	/*
	//	Here we remove whitespace - removed spaces at start and end,
	//	and replaced newlines with null terminators.
	*/
	{
		self->original = CharString_removeWhitespace( location );						/* 2 */
	}

	/*
	//	Extract protocol from before '://'
	*/
	{
		pci = CharString_indexOfNext( self->original, 0, ':' );
		if ( ('/' == self->original[pci+1]) && ('/' == self->original[pci+2]) )
		{
			self->protocol = CharString_substring( self->original, 0, pci-1 );				/* 3 */
		} else {
			self->protocol = new_CharString("");
		}
		pci += 3;
	}

	/*
	//	Extract the hostname, if specified.
	*/
	{
		hsi = CharString_indexOfNext( self->original, pci, '/' );

		if ( pci < (hsi-1) )
		{
			self->hostname = CharString_substring( self->original, pci, hsi - 1 );				/* 4 */
		} else {
			self->hostname = new_CharString( "" );												/* 4 */
		}
		hsi++;
	}

	/*
	//	Extract windows drive label, if specified.
	*/

	vci = CharString_indexOfNext( self->original, hsi, ':' );
	psi = CharString_indexOfNext( self->original, hsi, '/' );

	if ( vci < psi )
	{
		Path_setVolume( self, CharString_substring( self->original, hsi, vci ) );			/* 5 */
		self->common    = new_CharString( (const char*) &self->original[psi] );
		self->condensed = Path_condensePath( self->common );					/* 6 */
		self->absolute  = CharString_cat2( self->volume, self->condensed );				/* 7 */
	} else {
		Path_setVolume( self, new_CharString( "" ) );							/* 5 */
		self->common    = new_CharString( (const char*) &self->original[hsi-1] );
		self->condensed = Path_condensePath( self->common );					/* 6 */
		if ( CharString_getLength( self->volume ) )
		{
			self->absolute = CharString_cat2( self->volume, self->condensed );			/* 7 */
		} else {
			self->absolute = new_CharString( self->condensed );					/* 7 */
		}
	}
}

void
new_Path_WinPOSIX( Path* self, const char* location )
{
	int vci;
	self->type = OPENXDS_CORE_IO_TYPE_NONE;

	self->original = CharString_removeWhitespace( location );
	self->protocol = new_CharString( "file" );
	self->hostname = new_CharString( "" );

	vci = CharString_indexOfNext( self->original, 0, ':' );

	if ( ':' == self->original[vci] )
	{
		self->volume    = CharString_substring( self->original, 0, vci-1 );
		self->common    = new_CharString( &self->original[vci+1] );
		self->condensed = Path_condensePath( &self->original[vci+1] );
	}
    else
	{
		self->volume    = System_CurrentVolume();
		self->common    = new_CharString( self->original );
		self->condensed = Path_condensePath( self->original );
	}

	CharString_replace( self->common, '\\', '/' );
	if ( '/' == self->common[0] )
	{
		if ( '\0' != self->volume[0] )
		{
			self->absolute = CharString_cat3( self->volume, ":", self->condensed );
		} else {
			self->absolute = new_CharString( self->condensed );
		}
	} else {
		char* tmp = System_CurrentDirectory();
		
		if ( '/' == tmp[CharString_getLength( tmp )-1] )
		{
			self->absolute = CharString_cat2( tmp, self->common );
		} else {
			self->absolute = CharString_cat3( tmp, "/", self->common );
		}		
		free_CharString( tmp );
	}

	/*
	//if ( CharString_contains( self->absolute, "/.." ) )
	//{
	//	self->type = OPENOCL_IO_PSA_TYPE_FS_DIRECTORY_SUPER;
	//}
	*/
}

/*
//IPath* new_Path_UNC( const char* location )
//{
//	//	UNC				\\\C\home\Johnny\documents
//
//	IPath* self = (IPath*) CRuntime_calloc( 1, sizeof( IPath ) );
//	int next_slash;
//
//	self->type = OPENOCL_IO_PSA_TYPE_NONE;
//
//	//	Here we remove whitespace - removed spaces at start and end,
//	//	and replaced newlines with null terminators.
//	self->original = CharString_removeWhitespace( location );
//	self->common = new_CharString( self->original );
//	CharString_replace( self->common, '\\', '/' );
//
//	//	Determine the protocol
//	self->protocol = new_CharString( "unc" );
//
//	next_slash = CharString_indexOfNext( self->common, 2, '/' );
//
//	if ( '/' != self->common[2] )
//	{
//		//	Has host name			"//XXX/c/somedir"
//		self->hostname = CharString_substring( self->common, 2, next_slash - 1 );
//	} else {
//		self->hostname = System_Hostname();
//	}
//	
//	if ( '/' != self->common[next_slash + 1] )
//	{
//		//	Has volume id			"//XXX/c/somedir" or "///c/somedir"
//		int start = next_slash + 1;
//		next_slash = CharString_indexOfNext( self->common, start, '/' );
//		self->volume = CharString_substring( self->common, start, next_slash - 1 );
//	} else {
//		Path_setVolume( self, System_CurrentVolume() );
//	}
//
//	{
//		char* tmp = self->common;
//		self->common = Path_CondensePath( &tmp[next_slash] );
//		self->absolute = CharString_cat3( self->volume, ":", self->common );
//		free_CharString( tmp );
//	}
//
//	return self;
//}
*/

/*
////-----------------------------------------------------------------------------
////	const functions
////-----------------------------------------------------------------------------
*/

/*
//bool Path_isAbsolute( const IPath* self )
//{
//	int absolute = 0;
//	if ( '/' == *self->common )
//	{
//		absolute = 1;
//	} else {
//		const char* name = self->common;
//
//		while ( '\0' != *name )
//		{
//			if ( (':' == *name) && ('/' == *(++name)) )
//			{
//				absolute = 1;
//				break;
//			}
//			name++;
//		}
//	}
//	return absolute;
//}
//
//bool
//Path_exists( const IPath* self )
//{
//	return (bool) Path_getType( self );
//}
//
////--------------------------------------------------------------
////	Allocating const functions
////--------------------------------------------------------------
//
//char* Path_relativeTo( const IPath* self, const char* location )
//{
//	char* relative = new_CharString( "" );
//
//	if ( location && CharString_getLength( location ) )
//	{
//		unsigned int backoff = 0;
//		IPath* other_path = new_Path( location );
//		const char* self_abs = Path_getAbsolute( self );
//		const char* other_abs = Path_getAbsolute( other_path ); 
//
//		const char* s = self_abs;
//		const char* o = other_abs;
//
//		while ( (*s == *o) && ( '\0' != *s ) )
//		{
//			s++;
//			o++;
//		}
//	
//		while ( ('/' == *s) && ('\0' != *s) ) {
//			s++;
//		}
//	
//		while ( ('/' == *o) && ('\0' != *o) ) {
//			o++;
//		}
//	
//		{
//			bool loop = 1;
//			bool text = 0;
//
//			while ( '\0' != *o )
//			{
//				switch( *o )
//				{
//				case '\0':
//					loop = 0;
//					if ( text ) backoff++;
//					break;
//				case '/':
//					text = 0;
//					break;
//				default:
//					if ( 0 == text )
//					{
//						backoff++;
//						text = 1;
//					}
//				}
//				o++;
//			}
//		}
//	
//		{
//			char* tmp;
//			unsigned int i;
//			for ( i=0; i < backoff; i++ )
//			{
//				tmp = CharString_cat2( relative, "../" );
//				free_CharString( relative );
//				relative = tmp;
//			}			
//
//			tmp = CharString_cat2( relative, s );
//			free_CharString( relative );
//			relative = tmp;
//		}
//
//		free_Path( other_path );
//	}
//
//	return relative;
//}
//
//const char* Path_getNativeFormat( const IPath* self )
//{
//	if ( NULL == self->native )
//	{
//		IPath* writeable = (IPath*) self;
//		writeable->native = new_CharString( self->common );
//		CharString_replace( writeable->native, '/', '\\' );
//	}
//	return self->native;
//}
*/


void
Path_setVolume( Path* self, char* volume )
{
	int max = CharString_getLength( volume );
	int i;
	if ( self->volume )
	{
		free_CharString( self->volume );
	}
	for ( i=0; i < max; i++ )
	{
		volume[i] = toupper( volume[i] );
	}
	self->volume = volume;
}

char* Path_condensePath( const char* location )
{
	char* canonical_path = NULL;
	char* path = new_CharString( location );
	{
		CharString_replace( path, '\\', '/' );

		/*
		//	Add each directory onto a stack removing '.' and also
		//	parent if '..' is encountred.
		*/
		
		ISequence* seq = collapseIntoSequence( (const char*) path );
		{
			/*
			//	Extract directories from sequence and form into path
			*/
			
			canonical_path = ( '/' == path[0] ) ? new_CharString( "/" ) : new_CharString( "" );
			
			while ( ! seq->isEmpty( seq ) )
			{
				char* tmp   = canonical_path;
				char* token = (char*) seq->removeFirst( seq );
				if ( seq->isEmpty( seq ) )
				{
					canonical_path = CharString_cat2( canonical_path, token );
				} else {
					canonical_path = CharString_cat3( canonical_path, token, "/" );
				}
				free_CharString( tmp );
				free_CharString( token );
			}
		}
		seq->free( seq );
	}
	free_CharString( path );

	return canonical_path;
}

	ISequence*
	collapseIntoSequence( const char* path )
	{
		ISequence* seq = StdADTFactory_createSequence();
		int now  =  0;
		int last = -1;
		
		bool loop = 1;

		while ( loop )
		{
			switch ( path[now] )
			{
			case '\0':
				loop = 0;
				/* Intentional fall through */
			case '/':
				if ( (now != last) && (now != (last + 1) ) )
				{
					char* token = CharString_substring( path, last + 1, now - 1 );
					if ( 0 == CharString_compare( token, "." ) )
					{
						free_CharString( token );
					}
					else if ( 0 == CharString_compare( token, ".." ) )
					{
						char* popped = (char*) seq->removeLast( seq );
						if ( popped )
						{
							free_CharString( popped );
							free_CharString( token );
						} else {
							seq->addLast( seq, token );
						}
					}
					else
					{
						seq->addLast( seq, token );
					}
				}
				last = now;
				/* Intentional fall through */
			default:
				now++;
			}
		}

		return seq;
	}


Path*
Path_copy( const Path* self )
{
	return (Path*) new_Path( self->original );
}

const char*
Path_getCommon( const Path* self )
{
	return self->common;
}

const char*
Path_getCondensed( const Path* self )
{
	return self->condensed;
}

const char*
Path_getProtocol( const Path* self )
{
	return self->protocol;
}

const char*
Path_getHostname( const Path* self )
{
	return self->hostname;
}

const char*
Path_getVolume( const Path* self )
{
	return self->volume;
}

const char*
Path_getDirname( const Path* self )
{
	return self->dirname;
}

const char*
Path_getBasename( const Path* self )
{
	return self->basename;
}

const char*
Path_getExtension( const Path* self )
{
	return self->extension;
}

const char*
Path_getAbsolute( const Path* self )
{
	return self->absolute;
}

/*
//const char*
//Path_getUNC( const Path* self )
//{
//	return self->unc;
//}
//
//const char*
//Path_getURL( const Path* self )
//{
//	return self->url;
//}
*/

const char*
Path_getNativeFormat( const Path* self )
{
	return self->native;
}

bool
Path_hasExtension( const Path* self, const char* ext )
{
	return (0 == CharString_compare( self->extension, ext ));
}

bool
Path_isAbsolute( const Path* self )
{
	return ('/' == self->original[0]);
}

/*
bool
Path_isLink( const Path* self )
{
	return 0;
}
*/

/*
bool
Path_exists( const Path* self )
{
	return 0;
}
*/

bool
Path_getType( const Path* self )
{
	return self->type;
}

/*
char*
Path_relativeTo( const Path* self, const char* location )
{}

char*
Path_linkTarget( const Path* self )
{}

bool
Path_setCurrentDirectory( const char* location )
{}

bool
Path_changeCurrentDirectory( const char* location )
{}

bool
Path_revertCurrentDirectory( const char* location )
{}

void
Path_clearDirectoryHistory()
{}
*/

char*
Path_convertToNative( const char* location )
{
	return "";
}

char* Path_extractBasename( const char* common )
{
	char* basename = NULL;

	char ifs[2];
	ifs[0] = '/';
	ifs[1] = 0;

	char* tmp = CharString_copy( common );
    char* last = NULL;
    char* token = strtok( tmp, ifs );

	while ( NULL != token )
    {
		//fprintf( stdout, "\t%s\n", token );
		last = token;
		token = strtok( NULL, ifs );
	}
	basename = CharString_copy( last );
	CRuntime_free( tmp );

	return basename;
}

char* Path_extractDirname( const char* common )
{
	char* dirname = NULL;

	char ifs = '/';
	char* tmp = CharString_copy( common );
	{

		/*
		//	First remove any trailing /'s
		*/

		unsigned long length = strlen(tmp);
		while ( (length > 1) && (ifs == tmp[length - 1]) )
		{
			tmp[length - 1] = '\0';
			length--;
		}

		/*
		//	Next remove everything including the / that is reached
		*/
		while ( (length > 1) && (ifs != tmp[length - 1]) )
		{
			tmp[length - 1] = '\0';
			length--;
		}
		tmp[length - 1] = '\0';

		dirname = CharString_copy( tmp );
	}
	free_CharString( tmp );

	return dirname;
}

char* Path_extractExtension( const char* condensed )
{
	char* ext = NULL;

	int len = (int) strlen( condensed );
	int i   = len;

	while ( (i >= 0) && ('.' != condensed[i]) )
	{
		i--;
	}

	if ( i < 0 )
	{
		ext = new_CharString( "" );
	} else {
		ext = CharString_substring( condensed, i, len );
	}
	
	return ext;
}

char* Path_toNative( const char* common )
{
	char c = Path_GetFileSeparator();
	
	char* native = new_CharString( common );
	CharString_replace( native, '/', c );
	
	return native;
};





















