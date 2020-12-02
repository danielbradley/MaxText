#ifndef OPENXDS_CORE_ADT_STD_STDSTRING_H
#define OPENXDS_CORE_ADT_STD_STDSTRING_H

#include <openxds.core.adt/IString.h>
#include <openxds.core.adt.std.h>
#include <openxds.core/types.h>
#include <openxds.core/export.h>
#include <openxds.core/IObject.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif

EXPORT	StdString*              new_StdString( const char* str );
EXPORT	StdString* new_StdString_start_length( const char* str, long start, long length );

EXPORT	StdString*             free_StdString( StdString* self );

EXPORT	StdString*             StdString_copy( const StdString* self );
EXPORT	StdString*        StdString_substring( const StdString* self, int start, int length );
EXPORT	StdString* StdString_removeWhitespace( const StdString* self );
EXPORT	StdString*             StdString_trim( const StdString* self );
EXPORT	StdString*          StdString_between( const StdString* self, const char* prefix, const char* postfix );
EXPORT	StdString*            StdString_token( const StdString* self, int start, const char* delimiter );

EXPORT	StdString*         StdString_basename( const StdString* self, char ifs );
EXPORT	StdString*          StdString_dirname( const StdString* self, char ifs );

EXPORT	char                 StdString_charAt( const StdString* self, int i );
EXPORT	const char*        StdString_getChars( const StdString* self );

EXPORT	bool               StdString_contains( const StdString* self, const char* str );
EXPORT	bool             StdString_startsWith( const StdString* self, const char* str );
EXPORT	bool               StdString_endsWith( const StdString* self, const char* str );
EXPORT	bool                StdString_matches( const StdString* self, const char* str );

EXPORT	int                 StdString_compare( const StdString* self, const char* str );
EXPORT	long              StdString_getLength( const StdString* self );
EXPORT	int             StdString_indexOfNext( const StdString* self, int start, const char* delimiter );

	#ifdef __cplusplus
		};};};};};
	#endif
#endif
