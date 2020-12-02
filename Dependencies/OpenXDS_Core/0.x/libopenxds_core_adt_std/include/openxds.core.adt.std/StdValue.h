#ifndef OPENXDS_CORE_ADT_STD_VALUE_H
#define OPENXDS_CORE_ADT_STD_VALUE_H

/**
 *  The IValue ADT allows non-IObject objects to be stored in OpenXDS Core
 *  Abstract Data Types that expect IObjects.
 *
 *  If the new_Value allocator is used the VALUE will be deallocatd using
 *  CRuntime_free( VALUE ) when the IValue is freed.
 *
 *  If the new_Value_ref allocator is used, the VALUE will not be deallocated
 *  when the IValue is freed.
 */

#include "openxds.core.adt.std.h"

#include <openxds.core/export.h>
#include <openxds.core/types.h>
#include <openxds.core.adt.h>
#include <openxds.core.adt/IValue.h>


	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif


EXPORT	StdValue*               new_StdValue( void* value );
EXPORT	StdValue*           new_StdValue_ref( const void* value );
EXPORT	StdValue*       new_StdValue_IObject( IObject* value );
EXPORT	StdValue*   new_StdValue_IObject_ref( const IObject* value );
EXPORT	StdValue*              free_StdValue( StdValue* self );

EXPORT	void*       StdValue_replaceValue( StdValue* self, void* newValue );
EXPORT	const void*    StdValue_getValue( const StdValue* self );


	#ifdef __cplusplus
		};};};};};
	#endif

#endif
