/*
 *  Copyright (c) 2007-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_LIST_H
#define OPENXDS_CORE_ADT_STD_LIST_H

#include "openxds.core.adt.std.h"

#include <openxds.core/export.h>
#include <openxds.core.adt/IList.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif

EXPORT	StdList*                     new_StdList(void);
EXPORT	StdList*                    free_StdList( StdList* self );

EXPORT	const IPosition*     StdList_insertFirst( StdList* self, const void* anElement );
EXPORT	const IPosition*      StdList_insertLast( StdList* self, const void* anElement );

EXPORT	const void*              StdList_replace( StdList* self, const IPosition* p, const void* anElement );
EXPORT	const IPosition*    StdList_insertBefore( StdList* self, const IPosition* p, const void* anElement );
EXPORT	const IPosition*     StdList_insertAfter( StdList* self, const IPosition* p, const void* anElement );

EXPORT	const void*               StdList_remove( StdList* self, const IPosition* p );

EXPORT	const IPosition*        StdList_getFirst( const StdList* self );
EXPORT	const IPosition*         StdList_getLast( const StdList* self );

EXPORT	const IPosition*         StdList_getPrev( const StdList* self, const IPosition* p );
EXPORT	const IPosition*         StdList_getNext( const StdList* self, const IPosition* p );

EXPORT	int                      StdList_getSize( const StdList* self );
EXPORT	bool                     StdList_isEmpty( const StdList* self );

EXPORT	IPIterator*              StdList_positions( const StdList* self );

	#ifdef __cplusplus
		};};};};};
	#endif
#endif
