/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_CHARSTRING_H
#define OPENXDS_CORE_BASE_CHARSTRING_H

#include "openxds.core/export.h"
#include <stdarg.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace base {
					extern "C" {
	#endif

/*
 *  Lifecycle functions
 */
EXPORT char* new_CharString( const char* charString );
EXPORT char* new_CharString_delimiter( const char** tokens, const char delimiter );
EXPORT char* new_CharString_format_args( const char* format, ... );
EXPORT char* free_CharString( char* self );

/*
 *  Internal constructor
 */
       char* new_CharString_format_valist( const char* format, va_list args );

/*
 *  Functions
 */
EXPORT void CharString_replace( char* str, char old, char c );


/*
 *  Const Allocating functions
 */
EXPORT char* CharString_between( const char* self, const char* prefix, const char* suffix );
EXPORT char* CharString_cat2( const char* self, const char* two );
EXPORT char* CharString_cat3( const char* self, const char* two, const char* three );
EXPORT char* CharString_copy( const char* self );
EXPORT char* CharString_removeWhitespace( const char* self );
EXPORT char* CharString_substring( const char* self, int start, int end );
EXPORT int   CharString_skip( const char* self, int start, char delimiter );
EXPORT char* CharString_token( const char* self, int start, char delimiter );

EXPORT char* CharString_basename( const char* path );
EXPORT char* CharString_dirname( const char* path );
EXPORT char* CharString_basename_using( const char* path, char fileSeparator );
EXPORT char* CharString_dirname_using( const char* path, char fileSeparator );

/*
 *  Boolean functions
 */
EXPORT bool CharString_contains( const char* self, const char* token );
EXPORT bool CharString_startsWith( const char* self, const char* token );
EXPORT bool CharString_endsWith( const char* self, const char* token );
EXPORT bool CharString_matches( const char* self, const char* pattern );

/*
 *  Metric functions
 */
EXPORT int CharString_compare( const char* self, const char* other ); 

/*
 *  Information functions
 */
EXPORT unsigned int CharString_getLength( const char* xxx );
EXPORT unsigned int CharString_indexOfNext( const char* self, unsigned int start, char delimiter );

	#ifdef __cplusplus
		};};};};
	#endif
#endif
