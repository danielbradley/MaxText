/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.base/CharString.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/*
 *  The only difference between this and the win32 version
 *  is that the win32 version has an underscore ('_') before
 *  the function name.
 */
char* new_CharString_format_valist( const char* format, va_list args )
{
	int written;
	int size = 10;
	char* self = CRuntime_calloc( size, sizeof( char ) );

	written = vsnprintf( self, size, format, args );
	va_end(args);

	if ( written >= size )
	{
		CRuntime_free( self );
		self = CRuntime_calloc( written + 1, sizeof( char ) );
		written = vsnprintf( self, written + 1, format, args );
	}
	return self;
}
