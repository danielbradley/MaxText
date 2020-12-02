/*
 *  Copyright (C) 2004-2005 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_PROVIDER_PROVIDER_PRIVATE_H
#define OPENXDS_CORE_PROVIDER_PROVIDER_PRIVATE_H

#include "openxds.core.provider/Provider.h"
#include "openxds.core.provider/ProviderInstance.h"

typedef struct _Provider Provider;

struct _Provider
{
	IProvider         super;
	ProviderInstance* instance;
};

EXPORT	Provider*         free_Provider(       Provider* self );
EXPORT	const char*    Provider_getType( const Provider* self );
EXPORT	const char*    Provider_getInfo( const Provider* self );
EXPORT	const char*  Provider_getVendor( const Provider* self );
EXPORT	const char*    Provider_getName( const Provider* self );
EXPORT	const char*	Provider_getVersion( const Provider* self );
EXPORT	void*      	 Provider_getObject( const Provider* self );

EXPORT	void		     Provider_print( const Provider* self, void* stream );


#endif
