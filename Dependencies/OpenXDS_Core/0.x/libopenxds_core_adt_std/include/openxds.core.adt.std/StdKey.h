/*
 *  Copyright (C) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_KEY_H
#define OPENXDS_CORE_ADT_STD_KEY_H

#include "openxds.core.adt.std.h"

#include <openxds.core/export.h>
#include <openxds.core/types.h>
#include <openxds.core.adt.h>
#include <openxds.core.adt/IKey.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif

EXPORT	Key*       new_StdKey( const char* charString );
EXPORT	Key*     free_StdKey( Key* self );

/*	Implements openxds.core.adt/IKey */

EXPORT	int                StdKey_compareTo( const Key* k, const Key* k2 );
EXPORT	int                StdKey_compareToUsing( const Key* k, const Key* k2, const IComparitor* c );
EXPORT	bool               StdKey_contentEquals( const Key* k, const Key* k2 );
EXPORT	bool               StdKey_startsWith( const Key* k, const Key* k2 );
EXPORT	unsigned int       StdKey_getHashValue( const Key* k );
EXPORT	unsigned long long StdKey_getHashValue64( const Key* k );
EXPORT	const char*        StdKey_getChars( const Key* k );
EXPORT	Key*               StdKey_copy( const Key* k );

	#ifdef __cplusplus
		};};};};};
	#endif
#endif
