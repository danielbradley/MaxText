/*
 *  Copyright (C) 2011 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_ITREE_H
#define OPENXDS_CORE_ADT_ITREE_H

#include "openxds.core.adt.h"

#include <openxds.core/IObject.h>

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace adt {
	#endif


struct _ITree
{
	      ITree*              (*free)(       ITree* self );
	      ITree*           (*freeAll)(       ITree* self );

	const IPosition*       (*addRoot)(       ITree* self,                     E* value );
	const IPosition*      (*addChild)(       ITree* self, const IPosition* p, E* value );
	const IPosition* (*insertChildAt)(       ITree* self, const IPosition* p, E* value, long index );


	const IPosition*    (*addSubtree)(       ITree* self, const IPosition* p, ITree* t );
	      E*               (*replace)(       ITree* self, const IPosition* p, E* value );
	      E*                (*remove)(       ITree* self, const IPosition* p );
	      ITree*      (*removeAsTree)(       ITree* self, const IPosition* p );
		  void        (*swapSubtrees)(       ITree* self, const IPosition* p1, ITree* subtree, const IPosition* p2 );

	const IPosition*          (*root)( const ITree* self );
	const IPosition*        (*parent)( const ITree* self, const IPosition* p );
	const IPosition*         (*child)( const ITree* self, const IPosition* p, long i );
	      IPIterator*     (*children)( const ITree* self, const IPosition* p );
	      bool              (*isRoot)( const ITree* self, const IPosition* p );
	      bool          (*isInternal)( const ITree* self, const IPosition* p );
	      bool          (*isExternal)( const ITree* self, const IPosition* p );
		  bool           (*hasParent)( const ITree* self, const IPosition* p );
		  bool            (*hasChild)( const ITree* self, const IPosition* p, long i );
	      bool             (*isEmpty)( const ITree* self );
		  long          (*nrChildren)( const ITree* self, const IPosition* p );
		  long           (*nrOfChild)( const ITree* self, const IPosition* p );
	      long                (*size)( const ITree* self );
};


	#ifdef __cplusplus
		};};};
	#endif
#endif
