/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_STDTREENODE_H
#define OPENXDS_CORE_ADT_STD_STDTREENODE_H

#include <openxds.core.adt/IPosition.h>

	#ifdef __cplusplus
		using namespace openxds::core;

		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif

typedef struct _TreeNode TreeNode;

TreeNode*              new_StdTreeNode(       TreeNode* parent, IObject* anElement );
void*                 free_StdTreeNode(       TreeNode* self );
void*              freeAll_StdTreeNode(       TreeNode* self );

void                  StdTreeNode_swap( TreeNode* self, TreeNode* other );

/*	Implements openxds/core/adt/Position */
const IObject*  StdTreeNode_getElement( const TreeNode* self );

/*	Methods */

TreeNode*           StdTreeNode_getParent(       TreeNode* self );
TreeNode*            StdTreeNode_getChild(       TreeNode* self, long i );
IObject*           StdTreeNode_setElement(       TreeNode* self, IObject* anElement );
TreeNode*            StdTreeNode_addChild(       TreeNode* self, IObject* anElement );
TreeNode*          StdTreeNode_addChildAt(       TreeNode* self, IObject* anElement, long i );
TreeNode*             StdTreeNode_addNode(       TreeNode* self, TreeNode* child );
E*                    StdTreeNode_replace(       TreeNode* self, E* e );
E*                    StdTreeNode_extract(       TreeNode* self );
TreeNode* StdTreeNode_extractWithChildren(       TreeNode* self );
bool               StdTreeNode_isExternal( const TreeNode* self );
bool                StdTreeNode_hasParent( const TreeNode* self );
bool                 StdTreeNode_hasChild( const TreeNode* self, long i );
IPIterator*          StdTreeNode_children( const TreeNode* self );
long               StdTreeNode_nrChildren( const TreeNode* self );
long                StdTreeNode_nrOfChild( const TreeNode* self );
int          StdTreeNode_countDescendents( const TreeNode* self );

	#ifdef __cplusplus
		};};};};};
	#endif

#endif
