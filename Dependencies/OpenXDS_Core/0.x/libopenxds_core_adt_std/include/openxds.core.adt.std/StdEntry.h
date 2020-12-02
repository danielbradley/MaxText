/*
 *  Copyright (C) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_ENTRY_H
#define OPENXDS_CORE_ADT_STD_ENTRY_H

#include "openxds.core.adt.h"
#include "openxds.core.adt.std.h"
#include <openxds.core/export.h>
#include <openxds.core/types.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif


EXPORT	      StdEntry*          new_StdEntry( const IKey* key, IValue* value );
EXPORT	      StdEntry*         free_StdEntry( StdEntry* self );

EXPORT	const IKey*           StdEntry_getKey( const StdEntry* self );
EXPORT	const void*         StdEntry_getValue( const StdEntry* self );

		      StdValue* StdEntry_replaceValue( StdEntry* self, StdValue* value );


	#ifdef __cplusplus
		};};};};};
	#endif
#endif
