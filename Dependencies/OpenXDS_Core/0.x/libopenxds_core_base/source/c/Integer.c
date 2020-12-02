/*
 *  Copyright (c) 2008-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.base/Integer.private.h"

#include "openxds.core/IObject.h"
#include "openxds.core.base/CRuntime.h"

struct _Integer
{
	IInteger super;
	int      value;
};

IInteger* new_Integer( int aValue )
{
	Integer* self = CRuntime_calloc( 1, sizeof( Integer ) );
	self->super.free       = (IInteger* (*)(       IInteger* ))      free_Integer;
	self->super.setValue   = (    void  (*)(       IInteger*, int )) Integer_setValue;
	self->super.getValue   = (    int   (*)( const IInteger* ))      Integer_getValue;

	self->value = aValue;
	
	return (IInteger*) self;
}

Integer* free_Integer( Integer* self )
{
	return (Integer*) CRuntime_free( self );
}

void Integer_setValue( Integer* self, int aValue )
{
	self->value = aValue;
}

int Integer_getValue( const Integer* self )
{
	return self->value;
}
