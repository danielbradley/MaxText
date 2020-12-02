/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_STD_LISTNODE_H
#define OPENXDS_CORE_ADT_STD_LISTNODE_H

#include <openxds.core.adt/IPosition.h>

/**
 *  A ListNode is used to store some data item pointed to by a
 *  void pointer (void*).
 *
 *  The ListNode owns the element passed into it, and will try
 *  to deallocate it using CRuntime_free when the node is freed.
 *
 *  If this is not desired the item may be removed prior to the node
 *  being freed by calling:
 *
 *  node->setElement( node, NULL );
 */

	#ifdef __cplusplus
		using namespace openxds::core;

		namespace openxds {
			namespace core {
				namespace adt {
					namespace std {
						extern "C" {
	#endif

typedef struct _ListNode ListNode;

ListNode*       new_StdListNode( IObject* anElement );
void*           free_StdListNode( ListNode* self );

/*	Implements openxds/core/adt/Position */
const IObject*  StdListNode_getElement( const ListNode* self );

/*	Class methods */

IObject*        StdListNode_setElement( ListNode* self, IObject* anElement );

void            StdListNode_setNext( ListNode* self, const ListNode* aNode );
void            StdListNode_setPrev( ListNode* self, const ListNode* aNode );

const ListNode* StdListNode_getNext( const ListNode* self );
const ListNode* StdListNode_getPrev( const ListNode* self );

	#ifdef __cplusplus
		};};};};};
	#endif

#endif
