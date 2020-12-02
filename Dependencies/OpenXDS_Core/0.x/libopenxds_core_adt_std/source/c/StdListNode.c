/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.adt.std/StdListNode.h"
#include "openxds.core.base/CRuntime.h"

struct _ListNode
{
	IPosition         super;
	const ListNode*   prev;
	const ListNode*   next;
	IObject*          element;
};

ListNode* new_StdListNode( IObject* anElement )
{
	ListNode* self         = CRuntime_calloc( 1, sizeof( ListNode ) );

	self->super.super.free = (void*      (*)( IObject* ))         free_StdListNode;
	self->super.free       = (void*      (*)( IPosition* ))       free_StdListNode;
	self->super.getElement = (const void*(*)( const IPosition* )) StdListNode_getElement;
	self->element          = anElement;

	return self;
}

void* free_StdListNode( ListNode* self )
{
	if ( self )
	{
		if ( self->element ) CRuntime_free( self->element );
		self = (ListNode*) CRuntime_free( self );
	}
	return self;
}

const IObject* StdListNode_getElement( const ListNode* self )
{
	return self->element;
}

IObject* StdListNode_setElement( ListNode* self, IObject* anElement )
{
	IObject* ret  = self->element;
	self->element = anElement;
	return ret;
}

void StdListNode_setNext( ListNode* self, const ListNode* aNode )
{
	self->next = aNode;
}

void StdListNode_setPrev( ListNode* self, const ListNode* aNode )
{
	self->prev = aNode;
}

const ListNode* StdListNode_getNext( const ListNode* self )
{
	return self->next;
}

const ListNode* StdListNode_getPrev( const ListNode* self )
{
	return self->prev;
}
