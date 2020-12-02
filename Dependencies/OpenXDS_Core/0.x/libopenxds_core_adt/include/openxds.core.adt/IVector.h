/*
 *  Copyright (C) 2008-2009 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_ADT_IVECTOR_H
#define OPENXDS_CORE_ADT_IVECTOR_H

#include "openxds.core.adt.h"

#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IVector
{
	IObject super;

	IVector*          (*free)( IVector* self );
	void               (*add)( IVector* self, int rank,       E* anElement );
	void            (*addRef)( IVector* self, int rank, const E* anElement );
	void         (*addObject)( IVector* self, int rank, IObject* anElement );

	E*                 (*set)( IVector* self, int rank, const E* anElement );
	E*          (*removeFrom)( IVector* self, int rank );

	const E*           (*get)( const IVector* self, int rank );
	int               (*size)( const IVector* self );
	bool           (*isEmpty)( const IVector* self );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
