
#include "openxds.core.adt.std.h"
#include "openxds.core.adt/IValue.h"
#include "openxds.core.adt.std/StdValue.h"

#include <openxds.core.base/CRuntime.h>
#include <openxds.core/IObject.h>

#include <stdio.h>

struct _StdValue
{
	IValue super;

	void* val;
	bool freeWithCRuntime;
	bool freeAsIObject;
};

static StdValue* createStdValue()
{
	StdValue* self = CRuntime_calloc( 1, sizeof( StdValue ) );

	self->super.super.free   = (void*       (*)( IObject*       )) free_StdValue;
	self->super.free         = (void*       (*)( IValue*        )) free_StdValue;
	self->super.replaceValue = (void*       (*)( IValue*, void* )) StdValue_replaceValue;
	self->super.getValue     = (const void* (*)( const IValue*  )) StdValue_getValue;

	return self;
}

StdValue* new_StdValue( void* value )
{
	StdValue* self = createStdValue();

	self->val = value;
	self->freeWithCRuntime = 1; /* true */
	self->freeAsIObject    = 0; /* false */

	return self;
}

StdValue* new_StdValue_ref( const void* value )
{
	StdValue* self = createStdValue();

	self->val = (void*) value;
	self->freeWithCRuntime = 0; /* false */
	self->freeAsIObject    = 0; /* false */
	
	return self;
}

StdValue* new_StdValue_IObject( IObject* object )
{
	StdValue* self = createStdValue();

	self->val = (void*) object;
	self->freeWithCRuntime = 0; /* true */
	self->freeAsIObject    = 1; /* false */

	return self;
}

StdValue* new_StdValue_IObject_ref( const IObject* object )
{
	StdValue* self = createStdValue();

	self->val = (void*) object;
	self->freeWithCRuntime = 0; /* true */
	self->freeAsIObject    = 0; /* false */

	return self;
}

StdValue* free_StdValue( StdValue* self )
{
	if ( NULL != self->val )
	{
		if ( self->freeWithCRuntime )
		{
			CRuntime_free( self->val );
		}
		else if ( self->freeAsIObject )
		{
			IObject* obj = (IObject*) self->val;
			obj->free( obj );
		}
	}
	
	return CRuntime_free( self );
}

void* StdValue_replaceValue( StdValue* self, void* newValue )
{
	void* ret = self->val;
	self->val = newValue;
	return ret;
}

const void* StdValue_getValue( const StdValue* self )
{
	return self->val;
}
