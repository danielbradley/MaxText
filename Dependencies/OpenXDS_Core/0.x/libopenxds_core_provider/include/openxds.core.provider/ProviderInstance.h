/*
 *  Copyright (C) 2004 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_PROVIDER_PROVIDERINSTANCE_H
#define OPENXDS_CORE_PROVIDER_PROVIDERINSTANCE_H

#include "openxds.core.provider.h"

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace provider {
		extern "C"
		{
	#endif

struct _ProviderInstance
{
	const char* type;
	const char* info;
	const char* vendor;
	const char* name;
	const char* version;
	void* object;
};

//EXPORT static struct _Provider* GetInstance();
//struct _Provider* GetInstance();

#ifdef __cplusplus
}
};};};
#endif
#endif
