#include "openxds.core.adt.std/StdEIterator.h"

#include "openxds.core.adt/IList.h"
#include "openxds.core.adt.std/StdADTFactory.h"
#include <openxds.core.base/CRuntime.h>

/*
[Interator]---[List]--[List-IPosition]--[DS-IPosition]


*/

struct _StdEIterator
{
	IEIterator        super;
	IList*            entries;
	const IPosition*  current;
	bool primed;
};

StdEIterator* new_StdEIterator()
{
	StdEIterator* self = CRuntime_calloc( 1, sizeof( StdEIterator ) );
	self->super.free    = (IEIterator*   (*)(       IEIterator*)) free_StdEIterator;
	self->super.reset   = (void          (*)(       IEIterator*)) StdEIterator_reset;
	self->super.next    = (const IEntry* (*)(       IEIterator*)) StdEIterator_next;
	self->super.hasNext = (bool          (*)( const IEIterator*)) StdEIterator_hasNext;

	self->entries = StdADTFactory_createList();
	self->primed = FALSE;
	
	return self;
}

StdEIterator* free_StdEIterator( StdEIterator* self )
{
	self->entries->free( self->entries );
	return CRuntime_free( self );
}

void StdEIterator_reset( StdEIterator* self )
{
	self->current = self->entries->first( self->entries );
	self->primed  = TRUE;
}

const IEntry* StdEIterator_next( StdEIterator* self )
{
	const IEntry* ret = NULL;

	if ( ! self->primed ) StdEIterator_reset( self );

	if ( self->current )
	{
		ret = self->current->getElement( self->current );
		self->current = self->entries->next( self->entries, self->current );
	}
	return ret;
}

bool StdEIterator_hasNext( const StdEIterator* self )
{
	if ( ! self->primed ) StdEIterator_reset( (StdEIterator*) self );

	return (NULL != self->current);
}

void StdEIterator_addEntry( StdEIterator* self, const IEntry* e )
{
	self->entries->insertLast( self->entries, e );
}
