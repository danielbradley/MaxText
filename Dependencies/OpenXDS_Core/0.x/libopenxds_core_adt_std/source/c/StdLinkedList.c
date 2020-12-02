#include "openxds.core.adt.std/StdLinkedList.h"

#include "openxds.core.adt.std/StdListNode.h"
#include <openxds.core.base/CRuntime.h>

#include <stdlib.h>

struct _LinkedList
{
	ListNode* head;
	ListNode* tail;

	int size;
};

LinkedList* new_StdLinkedList()
{
	LinkedList* self = (LinkedList*) CRuntime_calloc( 1, sizeof( LinkedList ) );
	
	self->head = new_StdListNode( NULL );
	self->tail = new_StdListNode( NULL );
	self->size = 0;
	
	StdListNode_setNext( self->head, self->tail );
	StdListNode_setPrev( self->tail, self->head );

	return self;
}

void* free_StdLinkedList( LinkedList* self )
{
	if ( self )
	{
		const ListNode* const_node = NULL;
		while ( NULL != (const_node = StdLinkedList_getFirst( self )) )
		{
			ListNode* node = StdLinkedList_remove( self, const_node );
			free_StdListNode( node );
		}

		free_StdListNode( self->head );
		free_StdListNode( self->tail );
		self = (LinkedList*) CRuntime_free( self );
	}
	return self;
}

const ListNode* StdLinkedList_addFirst( LinkedList* self, ListNode* aListNode )
{
	StdLinkedList_addAfter( self, self->head, aListNode );
	return aListNode;
}

const ListNode* StdLinkedList_addLast( LinkedList* self, ListNode* aListNode )
{
	StdLinkedList_addBefore( self, self->tail, aListNode );
	return aListNode;
}

const ListNode* StdLinkedList_addBefore( LinkedList* self, const ListNode* next, ListNode* aNode )
{
	const ListNode* prev = StdListNode_getPrev( next );
	
	StdListNode_setNext( (ListNode*) prev, aNode );
	StdListNode_setPrev( (ListNode*) next, aNode );
	
	StdListNode_setNext( aNode, next );
	StdListNode_setPrev( aNode, prev );
	
	self->size++;
	return aNode;
}

const ListNode* StdLinkedList_addAfter( LinkedList* self, const ListNode* prev, ListNode* aNode )
{
	const ListNode* next = StdListNode_getNext( prev );
	
	StdListNode_setNext( (ListNode*) prev, aNode );
	StdListNode_setPrev( (ListNode*) next, aNode );
	
	StdListNode_setNext( aNode, next );
	StdListNode_setPrev( aNode, prev );

	self->size++;
	return aNode;
}

ListNode* StdLinkedList_remove( LinkedList* self, const ListNode* node )
{
	const ListNode* prev = StdListNode_getPrev( node );
	const ListNode* next = StdListNode_getNext( node );

	if ( prev && next )
	{
		StdListNode_setPrev( (ListNode*) next, prev );
		StdListNode_setNext( (ListNode*) prev, next );
		StdListNode_setPrev( (ListNode*) node, NULL );
		StdListNode_setNext( (ListNode*) node, NULL );
		self->size--;
	} else {
		node = NULL;
	}
	return (ListNode*) node;
}

const ListNode* StdLinkedList_getFirst( LinkedList* self )
{
	return StdLinkedList_getAfter( self, self->head );
}

const ListNode* StdLinkedList_getLast( LinkedList* self )
{
	return StdLinkedList_getBefore( self, self->tail );
}

const ListNode* StdLinkedList_getBefore( LinkedList* self, const ListNode* aNode )
{
	const ListNode* node = StdListNode_getPrev( aNode );
	if ( node == self->head )
	{
		node = NULL;
	}
	return node;
}

const ListNode* StdLinkedList_getAfter( LinkedList* self, const ListNode* aNode )
{
	const ListNode* node = StdListNode_getNext( aNode );
	if ( node == self->tail )
	{
		node = NULL;
	}
	return node;
}

int StdLinkedList_getSize( LinkedList* self )
{
	return self->size;
}

bool StdLinkedList_isEmpty( LinkedList* self )
{
	return (0 == self->size);
}
