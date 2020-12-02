#include "openxds.core.adt.std/StdDictionary.h"

#include <openxds.core.h>
#include <openxds.core.adt.h>
#include <openxds.core.adt/IDictionary.h>
#include <openxds.core.adt/IEntry.h>
#include <openxds.core.adt/IIterator.h>
#include <openxds.core.adt/IPIterator.h>
#include <openxds.core.adt/IKey.h>
#include <openxds.core.adt/IList.h>
#include <openxds.core.adt.std/StdADTFactory.h>
#include <openxds.core.adt.std/StdEntry.h>
#include <openxds.core.adt.std/StdIterator.h>
#include <openxds.core.adt.std/StdEIterator.h>
#include <openxds.core.adt.std/StdValue.h>
#include <openxds.core.base/CRuntime.h>

#include <string.h>

struct _StdDictionary
{
	IDictionary super;
	
	IList* entries;
};

StdDictionary* new_StdDictionary()
{
	StdDictionary* self = CRuntime_calloc( 1, sizeof( StdDictionary ) );
	
	self->super.free              = (      IDictionary* (*) (       IDictionary*                              ))    free_StdDictionary;
	self->super.insert            = (const IEntry*      (*) (       IDictionary*, const IKey*, void*          ))    StdDictionary_insert;
	self->super.insertRef         = (const IEntry*      (*) (       IDictionary*, const IKey*, const void*    ))    StdDictionary_insert_ref;
	self->super.insertObject      = (const IEntry*      (*) (       IDictionary*, const IKey*, IObject*       ))    StdDictionary_insert_IObject;
	self->super.insertObjectRef   = (const IEntry*      (*) (       IDictionary*, const IKey*, const IObject* ))    StdDictionary_insert_IObject_ref;
	self->super.insertValue       = (const IEntry*      (*) (       IDictionary*, const IKey*, IValue*        ))    StdDictionary_insert_IValue;
	self->super.remove            = (      void*        (*) (       IDictionary*, const IEntry*               ))    StdDictionary_remove;
	self->super.find              = (const IEntry*      (*) ( const IDictionary*, const IKey*                 ))    StdDictionary_find;
	self->super.startsWith        = (const IEntry*      (*) ( const IDictionary*, const IKey*                 ))    StdDictionary_startsWith;
	
	self->super.findAll           = (      IEIterator*  (*) ( const IDictionary*, const IKey*                 ))    StdDictionary_findAll;
	self->super.entries           = (      IEIterator*  (*) ( const IDictionary*                              ))    StdDictionary_entries;
	self->super.values            = (       IIterator*  (*) ( const IDictionary*                              ))    StdDictionary_values;

	self->super.containsKey       = (      bool         (*) ( const IDictionary*, const IKey*                 ))    StdDictionary_containsKey;
	self->super.containsKeyPrefix = (      bool         (*) ( const IDictionary*, const IKey*                 ))    StdDictionary_containsKeyPrefix;

	self->super.size              = (      int          (*) ( const IDictionary*                              ))    StdDictionary_size;
	self->super.isEmpty           = (      bool         (*) ( const IDictionary*                              ))    StdDictionary_isEmpty;
	
	self->entries = StdADTFactory_createList();
	
	return self;
}

StdDictionary* new_StdSortedDictionary()
{
	StdDictionary* self = CRuntime_calloc( 1, sizeof( StdDictionary ) );
	
	self->super.free              = (      IDictionary* (*) (       IDictionary*                              ))    free_StdDictionary;
	self->super.insert            = (const IEntry*      (*) (       IDictionary*, const IKey*, void*          ))    StdDictionary_insert;
	self->super.insertRef         = (const IEntry*      (*) (       IDictionary*, const IKey*, const void*    ))    StdDictionary_insert_ref;
	self->super.insertObject      = (const IEntry*      (*) (       IDictionary*, const IKey*, IObject*       ))    StdDictionary_insert_IObject;
	self->super.insertObjectRef   = (const IEntry*      (*) (       IDictionary*, const IKey*, const IObject* ))    StdDictionary_insert_IObject_ref;
	self->super.insertValue       = (const IEntry*      (*) (       IDictionary*, const IKey*, IValue*        ))    StdSortedDictionary_insert_IValue;
	self->super.remove            = (      void*        (*) (       IDictionary*, const IEntry*               ))    StdDictionary_remove;
	self->super.find              = (const IEntry*      (*) ( const IDictionary*, const IKey*                 ))    StdDictionary_find;
	self->super.startsWith        = (const IEntry*      (*) ( const IDictionary*, const IKey*                 ))    StdDictionary_startsWith;
	
	self->super.findAll           = (      IEIterator*  (*) ( const IDictionary*, const IKey*                 ))    StdDictionary_findAll;
	self->super.entries           = (      IEIterator*  (*) ( const IDictionary*                              ))    StdDictionary_entries;
	self->super.values            = (       IIterator*  (*) ( const IDictionary*                              ))    StdDictionary_values;

	self->super.containsKey       = (      bool         (*) ( const IDictionary*, const IKey*                 ))    StdDictionary_containsKey;
	self->super.containsKeyPrefix = (      bool         (*) ( const IDictionary*, const IKey*                 ))    StdDictionary_containsKeyPrefix;

	self->super.size              = (      int          (*) ( const IDictionary*                              ))    StdDictionary_size;
	self->super.isEmpty           = (      bool         (*) ( const IDictionary*                              ))    StdDictionary_isEmpty;
	
	self->entries = StdADTFactory_createList();
	
	return self;
}

StdDictionary* free_StdDictionary( StdDictionary* self )
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

const IEntry* StdDictionary_insert( StdDictionary* self, const IKey* key, void* aValue )
{
	return self->super.insertValue( &self->super, key, (IValue*) new_StdValue( aValue ) );
}

const IEntry* StdDictionary_insert_ref( StdDictionary* self, const IKey* key, const void* aValue )
{
	return self->super.insertValue( &self->super, key, (IValue*) new_StdValue_ref( aValue ) );
}

const IEntry* StdDictionary_insert_IObject( StdDictionary* self, const IKey* key, IObject* aValue )
{
	return self->super.insertValue( &self->super, key, (IValue*) new_StdValue_IObject( aValue ) );
}

const IEntry* StdDictionary_insert_IObject_ref( StdDictionary* self, const IKey* key, const IObject* aValue )
{
	return StdDictionary_insert_IValue( self, key, new_StdValue_IObject_ref( aValue ) );
}

const IEntry* StdDictionary_insert_IValue( StdDictionary* self, const IKey* key, StdValue* aValue )
{
	StdEntry* e = new_StdEntry( key, (IValue*) aValue );
	self->entries->insertLast( self->entries, e );

	return (IEntry*) e;
}

const IEntry* StdSortedDictionary_insert_IValue( StdDictionary* self, const IKey* key, StdValue* aValue )
{
	StdEntry* e = new_StdEntry( key, (IValue*) aValue );

	bool loop = 1;
	IPIterator* it = self->entries->positions( self->entries );
	while ( loop && it->hasNext( it ) )
	{
		const IPosition* p   = it->next( it );
		const IEntry*    e1  = (const IEntry*) p->getElement( p );
		const IKey*      k   = e1->getKey( e1 );
		const char*      k1  = k->getChars( k );
	
		if ( strcmp( key->getChars( key ), k1 ) < 0 )
		{
			self->entries->insertBefore( self->entries, p, e );
			loop = 0;
		}
	}
	it->free( it );

	if ( loop ) self->entries->insertLast( self->entries, e );

	return (IEntry*) e;
}

void* StdDictionary_remove( StdDictionary* self, const IEntry* entry )
{
	void* ret = NULL;

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* e1 = (const IEntry*) p->getElement( p );
		
		if ( entry == e1 )
		{
			StdEntry* e = (StdEntry*) self->entries->remove( self->entries, p );
			StdValue* v = StdEntry_replaceValue( e, NULL );
			free_StdEntry( e );
			ret = StdValue_replaceValue( v, NULL );
			free_StdValue( v );
			break;
		}
	}
	it->free( it );

	return ret;
}

const IEntry* StdDictionary_find( const StdDictionary* self, const IKey* key )
{
	const IEntry* ret = 0;

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* e = (const IEntry*) p->getElement( p );
		const IKey* k = e->getKey( e );
		
		if ( k->contentEquals( k, key ) )
		{
			ret = e;
			break;
		}
	}
	it->free( it );

	return ret;
}

const IEntry* StdDictionary_startsWith( const StdDictionary* self, const IKey* key )
{
	const IEntry* ret = 0;

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* e = (const IEntry*) p->getElement( p );
		const IKey* k = e->getKey( e );
		
		if ( k->startsWith( k, key ) )
		{
			ret = e;
			break;
		}
	}
	it->free( it );

	return ret;
}

IEIterator* StdDictionary_findAll( const StdDictionary* self, const IKey* key )
{
	StdEIterator* entries = new_StdEIterator();

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* e = (IEntry*) p->getElement( p );
		const IKey* k = e->getKey( e );
		
		if ( k->contentEquals( k, key ) )
		{
			StdEIterator_addEntry( entries, e );
		}
	}
	it->free( it );

	return (IEIterator*) entries;
}

IEIterator* StdDictionary_entries( const StdDictionary* self )
{
	StdEIterator* entries = new_StdEIterator();

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* e = (IEntry*) p->getElement( p );
		StdEIterator_addEntry( entries, e );
	}
	it->free( it );

	return (IEIterator*) entries;
}

IIterator* StdDictionary_values( const StdDictionary* self )
{
	StdIterator* values = new_StdIterator();

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* e = (IEntry*) p->getElement( p );
		const void*   v = (void*) e->getValue( e );
		StdIterator_addElement( values, v );
	}
	it->free( it );

	return (IIterator*) values;
}

bool StdDictionary_containsKey( const StdDictionary* self, const IKey* key )
{
	bool ret = 0;

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* e = (const IEntry*) p->getElement( p );
		const IKey* k = e->getKey( e );
		
		if ( k->contentEquals( k, key ) )
		{
			ret = 1;
			break;
		}
	}
	it->free( it );

	return ret;
}

bool StdDictionary_containsKeyPrefix( const StdDictionary* self, const IKey* key )
{
	bool ret = 0;

	IPIterator* it = self->entries->positions( self->entries );
	while ( it->hasNext( it ) )
	{
		const IPosition* p = it->next( it );
		const IEntry* e = (const IEntry*) p->getElement( p );
		const IKey* k = e->getKey( e );
		
		if ( k->startsWith( k, key ) )
		{
			ret = 1;
			break;
		}
	}
	it->free( it );

	return ret;
}

int StdDictionary_size( const StdDictionary* self )
{
	return self->entries->size( self->entries );
}

bool StdDictionary_isEmpty( const StdDictionary* self )
{
	return self->entries->isEmpty( self->entries );
}
