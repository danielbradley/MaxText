#include "openxds.core.adt.std/StdStack.h"
#include "openxds.core.adt.std/StdListNode.h"

#include <openxds.core.adt/IStack.h>
#include <openxds.core.base/CRuntime.h>

struct _StdStack
{
	IStack    super;
	ListNode* top;
	int       size;
};

StdStack* new_StdStack()
{
	StdStack* self = CRuntime_calloc( 1, sizeof( StdStack ) );
	
	self->super.free    = (IStack*       (*)( IStack* ))             free_StdStack;
	self->super.push    = (void          (*)( IStack*,E* ))          StdStack_push;
	self->super.pop     = (E*            (*)( IStack* ))             StdStack_pop;
	self->super.top     = (const E*      (*)( const IStack* ))       StdStack_top;
	self->super.isEmpty = (bool          (*)( const IStack* ))       StdStack_isEmpty;
	self->super.size    = (int           (*)( const IStack* ))       StdStack_size;
	self->top = new_StdListNode( NULL );
	self->size = 0;
	
	return self;
}

StdStack* free_StdStack( StdStack* self )
{
	self->top = free_StdListNode( self->top );
	return CRuntime_free( self );
}

void StdStack_push( StdStack* self, E* anElement )
{
	ListNode* node = new_StdListNode( anElement );

	StdListNode_setNext( node, StdListNode_getNext( self->top ) );
	StdListNode_setNext( self->top, node );

	self->size++;
}

void StdStack_pushObject( StdStack* self, IObject* anElement )
{
	ListNode* node = new_StdListNode( anElement );

	StdListNode_setNext( node, StdListNode_getNext( self->top ) );
	StdListNode_setNext( self->top, node );

	self->size++;
}

E* StdStack_pop( StdStack* self )
{
	E* ret = NULL;
	if ( 0 < self->size )
	{
		ListNode* node = (ListNode*) StdListNode_getNext( self->top );
		if ( node )
		{
			StdListNode_setNext( self->top, StdListNode_getNext( node ) );
			self->size--;
		
			ret = StdListNode_setElement( node, NULL );

			free_StdListNode( node );
		}
	}
	return ret;
}

const E* StdStack_top( const StdStack* self )
{
	const void* ret = NULL;
	if ( 0 < self->size )
	{
		ret = StdListNode_getElement( StdListNode_getNext( self->top ) );
	}
	return ret;
}

int StdStack_size( const StdStack* self )
{
	return self->size;
}

bool StdStack_isEmpty( const StdStack* self )
{
	return (0 == self->size);
}
