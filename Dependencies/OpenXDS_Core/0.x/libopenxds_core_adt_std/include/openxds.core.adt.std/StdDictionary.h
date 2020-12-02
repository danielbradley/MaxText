#ifndef OPENXDS_CORE_ADT_STD_STDDICTIONARY_H
#define OPENXDS_CORE_ADT_STD_STDDICTIONARY_H

#include "openxds.core.adt.std.h"
#include <openxds.core.adt.h>
#include <openxds.core/export.h>
#include <openxds.core/types.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif


EXPORT	StdDictionary*      new_StdDictionary(void);
EXPORT	StdDictionary*      new_StdSortedDictionary(void);
EXPORT	StdDictionary*     free_StdDictionary( StdDictionary* self );

/*	Implements openxds.core.adt/IMap */

EXPORT	const IEntry*                StdDictionary_insert( StdDictionary* self, const IKey* key, void* aValue );
EXPORT	const IEntry*            StdDictionary_insert_ref( StdDictionary* self, const IKey* key, const void* aValue );
EXPORT	const IEntry*        StdDictionary_insert_IObject( StdDictionary* self, const IKey* key, IObject* aValue );
EXPORT	const IEntry*    StdDictionary_insert_IObject_ref( StdDictionary* self, const IKey* key, const IObject* aValue );
EXPORT	const IEntry*         StdDictionary_insert_IValue( StdDictionary* self, const IKey* key, StdValue* aValue );
EXPORT	const IEntry*   StdSortedDictionary_insert_IValue( StdDictionary* self, const IKey* key, StdValue* aValue );
EXPORT	void*                        StdDictionary_remove( StdDictionary* self, const IEntry* entry );

EXPORT  const IEntry*                  StdDictionary_find( const StdDictionary* self, const IKey* key );
EXPORT  const IEntry*            StdDictionary_startsWith( const StdDictionary* self, const IKey* key );
EXPORT  IEIterator*                 StdDictionary_findAll( const StdDictionary* self, const IKey* key );

EXPORT  IEIterator*                 StdDictionary_entries( const StdDictionary* self );
EXPORT   IIterator*                  StdDictionary_values( const StdDictionary* self );

EXPORT	bool                    StdDictionary_containsKey( const StdDictionary* self, const IKey* key );
EXPORT	bool              StdDictionary_containsKeyPrefix( const StdDictionary* self, const IKey* key );

EXPORT  int                            StdDictionary_size( const StdDictionary* self );
EXPORT  bool                        StdDictionary_isEmpty( const StdDictionary* self );

	#ifdef __cplusplus
		};};};};};
	#endif
#endif
