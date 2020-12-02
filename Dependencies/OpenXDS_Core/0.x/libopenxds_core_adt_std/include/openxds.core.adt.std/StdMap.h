#ifndef OPENXDS_CORE_ADT_STD_STDMAP_H
#define OPENXDS_CORE_ADT_STD_STDMAP_H

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


EXPORT	StdMap*                 new_StdMap(void);
EXPORT	StdMap*                free_StdMap( StdMap* self );

/*	Implements openxds.core.adt/IMap */

EXPORT	void*                   StdMap_put(       StdMap* self, const IKey* key, void*       aValue );
EXPORT	void*           StdMap_put_IObject(       StdMap* self, const IKey* key, IObject*    aValue );
EXPORT	void*               StdMap_put_ref(       StdMap* self, const IKey* key, const void* aValue );
EXPORT	void*            StdMap_put_IValue(       StdMap* self, const IKey* key, StdValue*   aValue );
EXPORT	void*                StdMap_remove(       StdMap* self, const IKey* key );
EXPORT  const E*                StdMap_get( const StdMap* self, const IKey* key );

EXPORT  IIterator*             StdMap_keys( const StdMap* self );
EXPORT  IIterator*           StdMap_values( const StdMap* self );

EXPORT  int                    StdMap_size( const StdMap* self );
EXPORT  bool                StdMap_isEmpty( const StdMap* self );

	#ifdef __cplusplus
		};};};};};
	#endif
#endif
