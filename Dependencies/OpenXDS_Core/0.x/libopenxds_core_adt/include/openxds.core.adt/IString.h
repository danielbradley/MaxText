/*
 *  Copyright (C) 2007-2009 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_ISTRING_H
#define OPENXDS_CORE_ADT_ISTRING_H

#include "openxds.core.adt.h"

	#ifdef __cplusplus
	namespace openxds {
		namespace core {
			namespace adt {
	#endif


struct _IString
{
	IString*             (*free)( IString* self );

	/*	Allocating functions */
	IString*             (*copy)( const IString* self );
	IString*        (*substring)( const IString* self, int start, int length );
	IString* (*removeWhitespace)( const IString* self );
	IString*             (*trim)( const IString* self );
	IString*          (*between)( const IString* self, const char* prefix, const char* postfix );
	IString*            (*token)( const IString* self, int start, const char* delimiter );

	/*	Path related helper allocation fuctions */
	IString*         (*basename)( const IString* self, char ifs );
	IString*          (*dirname)( const IString* self, char ifs );

	/*	Accessor functions */
	char            (*charAt)( const IString* self, int i );
	const char*   (*getChars)( const IString* self );
	
	/*	Boolean functions */
	bool          (*contains)( const IString* self, const char* str );
	bool        (*startsWith)( const IString* self, const char* str );
	bool          (*endsWith)( const IString* self, const char* str );
	bool           (*matches)( const IString* self, const char* str );

	int            (*compare)( const IString* self, const char* str );
	int          (*getLength)( const IString* self );
	int        (*indexOfNext)( const IString* self, int start, const char* delimiter );
};


	#ifdef __cplusplus
	};};};
	#endif
#endif
