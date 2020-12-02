/*
 *  Copyright (C) 2008 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.adt.std/StdKey.h"

#include <openxds.core.adt/IComparitor.h>
#include <openxds.core.base/CharString.h>
#include <openxds.core.base/CRuntime.h>

#include <string.h>
#include <stdio.h>

struct _Key
{
	IKey super;
	
	char* value;
};

Key* new_StdKey( const char* charString )
{
	Key* self = CRuntime_calloc( 1, sizeof( Key ) );

	self->super.super.free     = (void*              (*)( IObject*))                                     free_StdKey;
	self->super.free           = (IKey*              (*)( IKey*))                                        free_StdKey;
	self->super.compareTo      = (int                (*)( const IKey*, const IKey*))                     StdKey_compareTo; 
	self->super.compareToUsing = (int                (*)( const IKey*, const IKey*, const IComparitor*)) StdKey_compareToUsing; 
	self->super.contentEquals  = (int                (*)( const IKey*, const IKey* ))                    StdKey_contentEquals; 
	self->super.startsWith     = (int                (*)( const IKey*, const IKey* ))                    StdKey_startsWith; 
	self->super.getHashValue   = (unsigned int       (*)( const IKey*))                                  StdKey_getHashValue;
	self->super.getHashValue64 = (unsigned long long (*)( const IKey*))                                  StdKey_getHashValue64;
	self->super.getChars       = (const char*        (*)( const IKey*))                                  StdKey_getChars;
	self->super.copy           = (IKey*              (*)( const IKey*))                                  StdKey_copy;

	long len = strlen( charString );
	self->value = CRuntime_calloc( len + 1, sizeof( char ) );
	self->value = strncpy( self->value, charString, len );
	
	return self;
}

Key* free_StdKey( Key* self )
{
	CRuntime_free( self->value );
	CRuntime_free( self );
	return NULL;
}

int StdKey_compareTo( const Key* k, const Key* k2 )
{
	const char* k_str1 = StdKey_getChars( k );
	const char* k_str2 = StdKey_getChars( k2 );
	
	return strcmp( k_str1, k_str2 );
}

int StdKey_compareToUsing( const Key* k, const Key* k2, const IComparitor* comparitor )
{
	return comparitor->compareKeys( (IKey*) k, (IKey*) k2 );
}

bool StdKey_contentEquals( const Key* k, const Key* k2 )
{
	return (0 == StdKey_compareTo( k, k2 ));
}

bool StdKey_startsWith( const Key* k, const Key* k2 )
{
	const char* k_str1 = StdKey_getChars( k );
	const char* k_str2 = StdKey_getChars( k2 );
	
	return CharString_startsWith( k_str1, k_str2 );
}

unsigned int StdKey_getHashValue( const Key* k )
{
	fprintf( stderr, "openxds::core::adt::std::Key_getHashValue not implemented yet!\n" );
	abort();
	return 0;
}

unsigned long long StdKey_getHashValue64( const Key* k )
{
	fprintf( stderr, "openxds::core::adt::std::Key_getHashValue64 not implemented yet!\n" );
	abort();
	return 0;
}

const char* StdKey_getChars( const Key* k )
{
	return k->value;
}

Key* StdKey_copy( const Key* k )
{
	return (Key*) new_StdKey( k->value );
}




