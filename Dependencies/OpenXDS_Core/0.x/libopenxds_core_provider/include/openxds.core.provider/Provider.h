/*
 *  Copyright (C) 2004 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_PROVIDER_PROVIDER_H
#define OPENXDS_CORE_PROVIDER_PROVIDER_H

#include "openxds.core.provider.h"
#include "openxds.core.provider/exportlite.h"

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace provider {
		extern "C"
		{
	#endif


struct _IProvider
{
	IProvider*           (*free)(       IProvider* self );
	const char*       (*getType)( const IProvider* self );
	const char*       (*getInfo)( const IProvider* self );
	const char*     (*getVendor)( const IProvider* self );
	const char*       (*getName)( const IProvider* self );
	const char*    (*getVersion)( const IProvider* self );
	      void*     (*getObject)( const IProvider* self );
	      void          (*print)( const IProvider* self );
};

EXPORT	IProvider* Provider_Load( const char* provider );


	#ifdef __cplusplus
		}
		};};};
	#endif
#endif
