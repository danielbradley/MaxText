/*
 *  Copyright (c) 2007-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.adt.std/StdPIterator.h"
#include "openxds.core.adt.std/StdList.h"
#include "openxds.core.adt.std/StdLinkedList.h"

#include <openxds.core.adt/IList.h>
#include <openxds.core.base/CRuntime.h>

struct _StdList
{
	IList       super;
	LinkedList* list;
};

StdList* new_StdList()
{
	StdList* self = CRuntime_calloc( 1, sizeof( StdList ) );
/*	self->super.super.free   = (void*            (*)( IObject*))                              free_StdList; */
	self->super.free         = (IList*           (*)( IList*))                                free_StdList;
	self->super.insertFirst  = (const IPosition* (*)( IList*, const void* ))                  StdList_insertFirst;
	self->super.insertLast   = (const IPosition* (*)( IList*, const void* ))                  StdList_insertLast;
	self->super.replace      = (const void*      (*)( IList*, const IPosition*,const void* )) StdList_replace;
	self->super.insertBefore = (const IPosition* (*)( IList*, const IPosition*,const void* )) StdList_insertBefore;
	self->super.insertAfter  = (const IPosition* (*)( IList*, const IPosition*,const void* )) StdList_insertAfter;
	self->super.remove       = (const void*      (*)( IList*, const IPosition* ))             StdList_remove;

	self->super.first        = (const IPosition*(*)( const IList* ))                          StdList_getFirst;
	self->super.last         = (const IPosition*(*)( const IList* ))                          StdList_getLast;
	self->super.prev         = (const IPosition*(*)( const IList*, const IPosition* ))        StdList_getPrev;
	self->super.previous     = (const IPosition*(*)( const IList*, const IPosition* ))        StdList_getPrev;
	self->super.next         = (const IPosition*(*)( const IList*, const IPosition* ))        StdList_getNext;
	self->super.size         = (int             (*)( const IList* ))                          StdList_getSize;
	self->super.isEmpty      = (bool            (*)( const IList* ))                          StdList_isEmpty;
	self->super.positions    = (IPIterator*     (*)( const IList* ))                          StdList_positions;

	self->list = new_StdLinkedList();
	
	return self;
}

StdList* free_StdList( StdList* self )
{
	int size = StdLinkedList_getSize( self->list );
	int i;
	for ( i=0; i < size; i++ )
	{
		const IPosition*  p = StdList_getFirst( self );
			StdList_remove( self, p );
		/* element is not deallocated because list is a list of references. */
	}
	free_StdLinkedList( self->list );
	return CRuntime_free( self );
}

const IPosition* StdList_insertFirst( StdList* self, const void* anElement )
{
	ListNode* node = new_StdListNode( (void*) anElement );
	StdLinkedList_addFirst( self->list, node );
	return (const IPosition*) node;
}

const IPosition* StdList_insertLast( StdList* self, const void* anElement )
{
	ListNode* node = new_StdListNode( (void*) anElement );
	StdLinkedList_addLast( self->list, node );
	return (const IPosition*) node;
}

const void* StdList_replace( StdList* self, const IPosition* p, const void* anElement )
{
	return StdListNode_setElement( (ListNode*) p, (void*) anElement );
}

const IPosition* StdList_insertBefore( StdList* self, const IPosition* p, const void* anElement )
{
	ListNode* node = new_StdListNode( (void*) anElement );
	StdLinkedList_addBefore( self->list, (ListNode*) p, node );
	return (const IPosition*) node;
}

const IPosition* StdList_insertAfter( StdList* self, const IPosition* p, const void* anElement )
{
	ListNode* node = new_StdListNode( (void*) anElement );
	StdLinkedList_addAfter( self->list, (ListNode*) p, node );
	return (const IPosition*) node;
}

const void* StdList_remove( StdList* self, const IPosition* p )
{
	ListNode* node = (ListNode*) p;
	StdLinkedList_remove( self->list, node );
	void* ret = StdListNode_setElement( node, NULL );
	free_StdListNode( node );

	return ret;
}

const IPosition* StdList_getFirst( const StdList* self )
{
	return (const IPosition*) StdLinkedList_getFirst( self->list );
}

const IPosition* StdList_getLast( const StdList* self )
{
	return (const IPosition*) StdLinkedList_getLast( self->list );
}

const IPosition* StdList_getPrev( const StdList* self, const IPosition* p )
{
	return (const IPosition*) StdLinkedList_getBefore( self->list, (ListNode*) p );
}

const IPosition* StdList_getNext( const StdList* self, const IPosition* p )
{
	return (const IPosition*) StdLinkedList_getAfter( self->list, (ListNode*) p );
}

int StdList_getSize( const StdList* self )
{
	return StdLinkedList_getSize( self->list );
}

bool StdList_isEmpty( const StdList* self )
{
	return StdLinkedList_isEmpty( self->list );
}

IPIterator* StdList_positions( const StdList* self )
{
	StdPIterator* it = new_StdPIterator();
	
	const IPosition* p = StdList_getFirst( self );
	if ( p )
	{
		StdPIterator_addPosition( it, p );
		while ( (p = StdList_getNext( self, p )) )
		{
			StdPIterator_addPosition( it, p );
		}
	}
	
	return (IPIterator*) it;
}
