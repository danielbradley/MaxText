/*
 *  Copyright (C) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_IKEY_H
#define OPENXDS_CORE_ADT_IKEY_H

#include "openxds.core.adt.h"

#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IKey
{
	IObject super;
	IKey*                        (*free)( IKey* k );
	int                     (*compareTo)( const IKey* k, const IKey* k2 );
	int                (*compareToUsing)( const IKey* k, const IKey* k2, const IComparitor* c );
	bool                (*contentEquals)( const IKey* k, const IKey* k2 );
	bool                   (*startsWith)( const IKey* k, const IKey* k2 );
	unsigned int         (*getHashValue)( const IKey* k );
	unsigned long long (*getHashValue64)( const IKey* k );
	const char*              (*getChars)( const IKey* k );
	IKey*                        (*copy)( const IKey* k );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
