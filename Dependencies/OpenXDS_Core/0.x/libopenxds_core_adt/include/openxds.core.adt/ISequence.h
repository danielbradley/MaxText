/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_ISEQUENCE_H
#define OPENXDS_CORE_ADT_ISEQUENCE_H

#include "openxds.core.adt.h"

#include <openxds.core/types.h>
#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _ISequence
{
	ISequence*                (*free)(       ISequence* self );
	ISequence*             (*freeAll)(       ISequence* self );

	void           (*setFreeIObjects)(       ISequence* self, bool flag );

	/* Deque */
	void                  (*addFirst)(       ISequence* self, E* e );
	void                   (*addLast)(       ISequence* self, E* e );
	E*                 (*removeFirst)(       ISequence* self );
	E*                  (*removeLast)(       ISequence* self );
	const E*              (*getFirst)( const ISequence* self );
	const E*               (*getLast)( const ISequence* self );

	/* List */
	const IPosition*   (*insertFirst)(       ISequence* self, E* anElement );
	const IPosition*    (*insertLast)(       ISequence* self, E* anElement );

	const IPosition*  (*insertBefore)(       ISequence* self, const IPosition* p, E* anElement );
	const IPosition*   (*insertAfter)(       ISequence* self, const IPosition* p, E* anElement );
	      E*               (*replace)(       ISequence* self, const IPosition* p, E* anElement );
	      E*                (*remove)(       ISequence* self, const IPosition* p );

	const IPosition*         (*first)( const ISequence* self );
	const IPosition*          (*last)( const ISequence* self );

	const IPosition*          (*prev)( const ISequence* self, const IPosition* p );
	const IPosition*      (*previous)( const ISequence* self, const IPosition* p );
	const IPosition*          (*next)( const ISequence* self, const IPosition* p );
	      IPIterator*    (*positions)( const ISequence* self );
	      IIterator*      (*elements)( const ISequence* self );

	/* Vector */
	void                       (*add)(       ISequence* self, long rank, E* anElement );
	E*                         (*set)(       ISequence* self, long rank, E* anElement );
	E*                  (*removeFrom)(       ISequence* self, long rank );
	const E*                   (*get)( const ISequence* self, long rank );

	/* Bridging */
	long                    (*rankOf)( const ISequence* self, const IPosition* p );
	const IPosition*        (*atRank)( const ISequence* self, long rank );

	/* Common */
	long                      (*size)( const ISequence* self );
	bool                   (*isEmpty)( const ISequence* self );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
