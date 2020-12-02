#include "openxds.core.adt.std/StdEntry.h"

#include <openxds.core.adt/IEntry.h>
#include <openxds.core.adt/IKey.h>
#include <openxds.core.adt/IValue.h>
#include <openxds.core.base/CRuntime.h>

struct _StdEntry
{
	IEntry super;
	
	IKey*    key;
	IValue*  value;
};

StdEntry* new_StdEntry( const IKey* key, IValue* value )
{
	StdEntry* self = CRuntime_calloc( 1, sizeof( StdEntry ) );

	self->super.free             = (IEntry*        (*)( IEntry* ))          free_StdEntry;
	self->super.getKey           = (const IKey*    (*)( const IEntry*))     StdEntry_getKey; 
	self->super.getValue         = (const void*    (*)( const IEntry*))     StdEntry_getValue;

	self->key   = key->copy( key );
	self->value = value;

	return self;
}

StdEntry* free_StdEntry( StdEntry* self )
{
	self->key->free( self->key );
	if ( self->value ) self->value->free( self->value );
	
	return CRuntime_free( self );
}

const IKey* StdEntry_getKey( const StdEntry* self )
{
	return self->key;
}

const void* StdEntry_getValue( const StdEntry* self )
{
	return self->value->getValue( self->value );
}

StdValue* StdEntry_replaceValue( StdEntry* self, StdValue* aValue )
{
	StdValue* ret = (StdValue*) self->value;
	self->value = (IValue*) aValue;
	return ret;
}

