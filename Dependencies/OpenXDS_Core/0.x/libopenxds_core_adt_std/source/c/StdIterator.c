#include "openxds.core.adt.std/StdIterator.h"
#include "openxds.core.adt.std/StdADTFactory.h"

#include "openxds.core.adt/IList.h"

#include <openxds.core.base/CRuntime.h>

/*
[Interator]---[List]--[List-IPosition]--[DS-IPosition]


*/

struct _StdIterator
{
	IIterator        super;
	IList*           positions;
	const IPosition* current;
	bool primed;
};

StdIterator* new_StdIterator()
{
	StdIterator* self = CRuntime_calloc( 1, sizeof( StdIterator ) );
	self->super.free    = (IIterator*  (*)(       IIterator*)) free_StdIterator;
	self->super.reset   = (void        (*)(       IIterator*)) StdIterator_reset;
	self->super.next    = (const void* (*)(       IIterator*)) StdIterator_next;
	self->super.hasNext = (bool        (*)( const IIterator*)) StdIterator_hasNext;

	self->positions = StdADTFactory_createList();
	self->primed = FALSE;
	
	return self;
}

StdIterator* free_StdIterator( StdIterator* self )
{
	self->positions->free( self->positions );
	return CRuntime_free( self );
}

void StdIterator_reset( StdIterator* self )
{
	self->current = self->positions->first( self->positions );
	self->primed  = TRUE;
}

const void* StdIterator_next( StdIterator* self )
{
	const void* ret = NULL;

	if ( ! self->primed ) StdIterator_reset( self );

	if ( self->current )
	{
		ret = self->current->getElement( self->current );
		self->current = self->positions->next( self->positions, self->current );
	}
	return ret;
}

bool StdIterator_hasNext( const StdIterator* self )
{
	if ( ! self->primed ) StdIterator_reset( (StdIterator*) self );

	return (NULL != self->current);
}

void StdIterator_addElement( StdIterator* self, const void* p )
{
	self->positions->insertLast( self->positions, p );
}
