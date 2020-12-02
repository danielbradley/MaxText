#include "openxds.core.adt.std/StdPIterator.h"
#include "openxds.core.adt.std/StdList.h"

#include <openxds.core.base/CRuntime.h>

/*
[Interator]---[List]--[List-IPosition]--[DS-IPosition]


*/


struct _StdPIterator
{
	IPIterator        super;
	IList*           positions;
	const IPosition* current;
	bool primed;
};

StdPIterator* new_StdPIterator()
{
	StdPIterator* self = CRuntime_calloc( 1, sizeof( StdPIterator ) );
	self->super.free    = (IPIterator*      (*)(       IPIterator*)) free_StdPIterator;
	self->super.reset   = (void             (*)(       IPIterator*)) StdPIterator_reset;
	self->super.next    = (const IPosition* (*)(       IPIterator*)) StdPIterator_next;
	self->super.hasNext = (bool             (*)( const IPIterator*)) StdPIterator_hasNext;

	self->positions = (IList*) new_StdList();
	self->primed = FALSE;
	
	return self;
}

StdPIterator* free_StdPIterator( StdPIterator* self )
{
	self->positions->free( self->positions );
	return CRuntime_free( self );
}

void StdPIterator_reset( StdPIterator* self )
{
	self->current = self->positions->first( self->positions );
	self->primed  = TRUE;
}

const IPosition* StdPIterator_next( StdPIterator* self )
{
	const IPosition* ret = NULL;

	if ( ! self->primed ) StdPIterator_reset( self );

	if ( self->current )
	{
		ret = self->current->getElement( self->current );
		self->current = self->positions->next( self->positions, self->current );
	}
	return ret;
}

bool StdPIterator_hasNext( const StdPIterator* self )
{
	if ( ! self->primed ) StdPIterator_reset( (StdPIterator*) self );

	return (NULL != self->current);
}

void StdPIterator_addPosition( StdPIterator* self, const IPosition* p )
{
	self->positions->insertLast( self->positions, p );
}
