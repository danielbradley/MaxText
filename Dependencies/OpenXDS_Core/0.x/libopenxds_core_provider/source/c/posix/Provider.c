/*
 *  Copyright (C) 2004 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#include "openxds.core.provider/Provider.private.h"
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

static void initialise( Provider* self );

IProvider*
Provider_Load( const char* location )
{
	Provider* self = (Provider*) calloc( 1, sizeof( Provider ) );
	initialise( self );

	void* handle;
	ProviderInstance* (*GetInstance)();
	
	handle = dlopen( location, RTLD_LAZY );
	if ( handle )
	{
		GetInstance = dlsym( handle, "GetInstance" );
		if ( GetInstance )
		{
			self->instance = GetInstance();
		} else {
			fprintf( stdout, "could not retrieve sym: %s\n", dlerror() );
		}
	} else {
		fprintf( stdout, "could not open provider: %s\n", dlerror() );
	}

	return (IProvider*) self;
}

void
initialise( Provider* self )
{
	self->super.free       = (IProvider*  (*)(       IProvider* self )) free_Provider;
	self->super.getType    = (const char* (*)( const IProvider* self )) Provider_getType;
	self->super.getInfo    = (const char* (*)( const IProvider* self )) Provider_getInfo;
	self->super.getVendor  = (const char* (*)( const IProvider* self )) Provider_getVendor;
	self->super.getName    = (const char* (*)( const IProvider* self )) Provider_getName;
	self->super.getVersion = (const char* (*)( const IProvider* self )) Provider_getVersion;
	self->super.getObject  = (      void* (*)( const IProvider* self )) Provider_getObject;
	self->super.print      = (      void  (*)( const IProvider* self )) Provider_print;
}

Provider* free_Provider( Provider* self )
{
	free( self );
	return NULL;
}

const char* Provider_getType( const Provider* self )
{
	return self->instance->type;
}

const char* Provider_getInfo( const Provider* self )
{
	return self->instance->info;
}

const char* Provider_getVendor( const Provider* self )
{
	return self->instance->vendor;
}

const char* Provider_getName( const Provider* self )
{
	return self->instance->name;
}

const char* Provider_getVersion( const Provider* self )
{
	return self->instance->version;
}

void* Provider_getObject( const Provider* self )
{
	return self->instance->object;
}

void Provider_print( const Provider* self, void* stream )
{
	FILE* out = (FILE*) stream;

	fprintf( out, "%-9s%s\n", "Type:",    Provider_getType( self ) );
	fprintf( out, "%-9s%s\n", "Info:",    Provider_getInfo( self ) );
	fprintf( out, "%-9s%s\n", "Vendor:",  Provider_getVendor( self ) );
	fprintf( out, "%-9s%s\n", "Name:",    Provider_getName( self ) );
	fprintf( out, "%-9s%s\n", "Version:", Provider_getVersion( self ) );
	fprintf( out, "\n" );
}

