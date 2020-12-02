#include "openxds.core.adt.std/StdMap.h"

#include <openxds.core.h>
#include <openxds.core.adt.h>
#include <openxds.core.adt/IEntry.h>
#include <openxds.core.adt/IIterator.h>
#include <openxds.core.adt/IPIterator.h>
#include <openxds.core.adt/IKey.h>
#include <openxds.core.adt/IList.h>
#include <openxds.core.adt/IMap.h>
#include <openxds.core.adt.std/StdADTFactory.h>
#include <openxds.core.adt.std/StdEntry.h>
#include <openxds.core.adt.std/StdIterator.h>
#include <openxds.core.adt.std/StdValue.h>
#include <openxds.core.base/CRuntime.h>

#include <stdio.h> //DEBUG

struct _StdMap
{
	IMap super;
	
	IList* entries;
};

StdMap* new_StdMap()
{
	StdMap* self = CRuntime_calloc( 1, sizeof( StdMap ) );
	
	self->super.free       = (IMap*         (*) (       IMap*                        ))    free_StdMap;
	self->super.put        = (E*            (*) (       IMap*, const IKey*, E*       ))    StdMap_put;
	self->super.putObject  = (E*            (*) (       IMap*, const IKey*, IObject* ))    StdMap_put_IObject;
	self->super.putRef     = (E*            (*) (       IMap*, const IKey*, const E* ))    StdMap_put_ref;
	self->super.remove     = (E*            (*) (       IMap*, const IKey*           ))    StdMap_remove;
	self->super.get        = (const E*      (*) ( const IMap*, const IKey*           ))    StdMap_get;

	self->super.keys       = (IIterator*    (*) ( const IMap*                        ))    StdMap_keys;
	self->super.values     = (IIterator*    (*) ( const IMap*                        ))    StdMap_values;

	self->super.size       = (int           (*) ( const IMap*                        ))    StdMap_size;
	self->super.isEmpty    = (bool          (*) ( const IMap*                        ))    StdMap_isEmpty;
	
	self->entries = StdADTFactory_createList();
	
	return self;
}

StdMap* free_StdMap( StdMap* self )
{
	while ( 0 == self->entries->isEmpty( self->entries ) )
	{
		const IPosition* p = self->entries->first( self->entries );
		IEntry* entry = (IEntry*) self->entries->remove( self->entries, p );
		entry->free( entry );
	}
	self->entries = self->entries->free( self->entries );
	return CRuntime_free( self );
}

void* StdMap_put( StdMap* self, const IKey* key, void* value )
{
	return StdMap_put_IValue( self, key, new_StdValue( value ) );
}

void* StdMap_put_IObject( StdMap* self, const IKey* key, IObject* value )
{
	return StdMap_put_IValue( self, key, new_StdValue_IObject( value ) );
}

void* StdMap_put_ref( StdMap* self, const IKey* key, const void* value )
{
	return StdMap_put_IValue( self, key, new_StdValue_ref( value ) );
}

void* StdMap_put_IValue( StdMap* self, const IKey* key, StdValue* aValue )
{
	void* ret = 0;
	
	int inserted = 0;

	IPIterator* it = self->entries->positions( self->entries );
	bool loop = TRUE;
	while ( loop && it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* entry = p->getElement( p );
		const IKey* e_key = entry->getKey( entry );
		
		if ( e_key->contentEquals( e_key, key ) )
		{
			IValue* value = (IValue*) StdEntry_replaceValue( (StdEntry*) entry, aValue );
			ret = value->replaceValue( value, NULL );
			value->free( value );
			inserted = 1;
			break;
		}
		else if ( 0 < e_key->compareTo( e_key, key ) )
		{
			IEntry* entry = (IEntry*) new_StdEntry( key, (IValue*) aValue );
			self->entries->insertBefore( self->entries, p, entry );
			inserted = 1;
			loop = FALSE;
		}
		//int x = e_key->compareTo( e_key, key );
		//fprintf( stdout, "%i %s - %s\n", x, e_key->getChars( e_key ), key->getChars( key ) );
	}
	it->free( it );
	
	if ( ! inserted )
	{
		IEntry* entry = (IEntry*) new_StdEntry( key, (IValue*) aValue );
		self->entries->insertLast( self->entries, entry );
	}
	return ret;
}

void* StdMap_remove( StdMap* self, const IKey* key )
{
	void* ret = 0;

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const StdEntry* entry = (StdEntry*) p->getElement( p );
		const IKey* e_key = (const IKey*) StdEntry_getKey( entry );
		
		if ( e_key->contentEquals( e_key, key ) )
		{
			StdEntry* removed_entry = (StdEntry*) self->entries->remove( self->entries, p );
			IValue* v = (IValue*) StdEntry_replaceValue( removed_entry, NULL );
			ret = v->replaceValue( v, NULL );
			
			free_StdEntry( removed_entry );
			v->free( v );
			break;
		}
	}
	it->free( it );

	return ret;
}

const E* StdMap_get( const StdMap* self, const IKey* key )
{
	const E* ret = 0;

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* entry = (IEntry*) p->getElement( p );
		const IKey* e_key = entry->getKey( entry );
		
		if ( e_key->contentEquals( e_key, key ) )
		{
			ret = entry->getValue( entry );
			break;
		}
	}
	it->free( it );

	return ret;
}

IIterator* StdMap_keys( const StdMap* self )
{
	StdIterator* ret = new_StdIterator();

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* entry = (IEntry*) p->getElement( p );
		const IKey* e_key = entry->getKey( entry );
		
		StdIterator_addElement( ret, e_key );
	}
	it->free( it );

	return (IIterator*) ret;
}

IIterator* StdMap_values( const StdMap* self )
{
	StdIterator* ret = new_StdIterator();

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* entry = (IEntry*) p->getElement( p );
		const IValue* e_value = entry->getValue( entry );
		
		StdIterator_addElement( ret, e_value );
	}
	it->free( it );

	return (IIterator*) ret;
}

int StdMap_size( const StdMap* self )
{
	return self->entries->size( self->entries );
}

bool StdMap_isEmpty( const StdMap* self )
{
	return self->entries->isEmpty( self->entries );
}











