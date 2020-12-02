/*
 *  Copyright (C) 2007 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.adt.std/StdSequenceNode.h"
#include "openxds.core.base/CRuntime.h"

StdSequenceNode* new_StdSequenceNode( E* anElement, long index )
{
	StdSequenceNode* self = CRuntime_calloc( 1, sizeof( StdSequenceNode ) );

	self->super.super.free = (void*      (*)( IObject* ))         free_StdSequenceNode;
	self->super.free       = (void*      (*)( IPosition* ))       free_StdSequenceNode;
	self->super.getElement = (const E*   (*)( const IPosition* )) StdSequenceNode_getElement;

	self->e = anElement;
	self->i = index;

	return self;
}

StdSequenceNode*
free_StdSequenceNode( StdSequenceNode* self )
{
	if ( self->e ) CRuntime_free( self->e );
	return CRuntime_free( self );
}

E*
StdSequenceNode_replaceElement( StdSequenceNode* self, E* anElement )
{
	E* tmp = self->e;
	self->e = anElement;
	return tmp;
}

const E*
StdSequenceNode_getElement( const StdSequenceNode* self )
{
	return self->e;
}

long
StdSequenceNode_getIndex( const StdSequenceNode* self )
{
	return self->i;
}

