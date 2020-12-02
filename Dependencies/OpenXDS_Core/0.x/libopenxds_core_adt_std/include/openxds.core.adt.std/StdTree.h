#ifndef OPENXDS_CORE_ADT_STD_STDTREE_H
#define OPENXDS_CORE_ADT_STD_STDTREE_H

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

EXPORT	      StdTree*             new_StdTree(void);

EXPORT	      StdTree*            free_StdTree(       StdTree* self );
EXPORT	      StdTree*         freeAll_StdTree(       StdTree* self );
EXPORT	const IPosition*       StdTree_addRoot(       StdTree* self,                     E* value );
EXPORT	const IPosition*      StdTree_addChild(       StdTree* self, const IPosition* p, E* value );
EXPORT	const IPosition* StdTree_insertChildAt(       StdTree* self, const IPosition* p, E* value, long i );


EXPORT	const IPosition*    StdTree_addSubtree(       StdTree* self, const IPosition* p, ITree* t );
EXPORT	      E*               StdTree_replace(       StdTree* self, const IPosition* p, E* e );
EXPORT	      E*                StdTree_remove(       StdTree* self, const IPosition* p );
EXPORT	      StdTree*    StdTree_removeAsTree(       StdTree* self, const IPosition* p );
EXPORT	      void        StdTree_swapSubtrees(       StdTree* self, const IPosition* p1, StdTree* tree, const IPosition* p2 );

EXPORT	const IPosition*          StdTree_root( const StdTree* self );
EXPORT	const IPosition*        StdTree_parent( const StdTree* self, const IPosition* p );
EXPORT	const IPosition*         StdTree_child( const StdTree* self, const IPosition* p, long i );

EXPORT	bool                    StdTree_isRoot( const StdTree* self, const IPosition* p );
EXPORT	bool                StdTree_isInternal( const StdTree* self, const IPosition* p );
EXPORT	bool                StdTree_isExternal( const StdTree* self, const IPosition* p );
EXPORT	bool                 StdTree_hasParent( const StdTree* self, const IPosition* p );
EXPORT	bool                  StdTree_hasChild( const StdTree* self, const IPosition* p, long i );

EXPORT	      IPIterator*     StdTree_children( const StdTree* self, const IPosition* p );
EXPORT	long                StdTree_nrChildren( const StdTree* self, const IPosition* p );
EXPORT	long                 StdTree_nrOfChild( const StdTree* self, const IPosition* p );

EXPORT  long                      StdTree_size( const StdTree* self );
EXPORT  bool                   StdTree_isEmpty( const StdTree* self );

	#ifdef __cplusplus
		};};};};};
	#endif
#endif
