/*
 *  Copyright (C) 2008 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_IENTRY_H
#define OPENXDS_CORE_ADT_IENTRY_H

#include "openxds.core.adt.h"

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IEntry
{
	IEntry*                                 (*free)(       IEntry* self );
	const IKey*                           (*getKey)( const IEntry* self );
	const E*                            (*getValue)( const IEntry* self );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
