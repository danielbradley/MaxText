/*
 *  Copyright (c) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_ILIST_H
#define OPENXDS_CORE_ADT_ILIST_H

#include "openxds.core.adt.h"
#include "openxds.core.adt/IPosition.h"

#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IList
{
	IList*                    (*free)( IList* l );
	
	const IPosition*   (*insertFirst)( IList* self, const E* anElement );
	const IPosition*    (*insertLast)( IList* self, const E* anElement );

	const E*               (*replace)( IList* self, const IPosition* p, const E* anElement );
	const IPosition*  (*insertBefore)( IList* self, const IPosition* p, const E* anElement );
	const IPosition*   (*insertAfter)( IList* self, const IPosition* p, const E* anElement );

	const E*                (*remove)( IList* self, const IPosition* p );

	const IPosition*         (*first)( const IList* self );
	const IPosition*          (*last)( const IList* self );

	const IPosition*          (*prev)( const IList* self, const IPosition* p );
	const IPosition*      (*previous)( const IList* self, const IPosition* p );
	const IPosition*          (*next)( const IList* self, const IPosition* p );
	
	int                       (*size)( const IList* self );
	bool                   (*isEmpty)( const IList* self );

	IPIterator*          (*positions)( const IList* self );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
