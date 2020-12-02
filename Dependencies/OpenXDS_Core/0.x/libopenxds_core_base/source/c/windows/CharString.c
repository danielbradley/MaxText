/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds/base/psa/CharString.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

/*
 *  _vsnprintf is detailed at:
 *  http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vclib/html/vclrf_vscprintf_vscwprintf.asp
 */
char* new_CharString_format_valist( const char* format, va_list args )
{
	int written;
	int size = 128;
	char* self = CRuntime_calloc( size, sizeof( char ) );

	while( -1 == (written = _vsnprintf( self, size, format, args )) )
	{
		CRuntime_free( self );
		size *= 2;
		self = CRuntime_calloc( size, sizeof( char ) );
	}
	return self;
}
