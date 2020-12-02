#ifndef OPENXDS_CORE_ADT_IVALUE_H
#define OPENXDS_CORE_ADT_IVALUE_H

/**
 *  The IValue ADT allows non-IObject objects to be stored in OpenXDS Core
 *  Abstract Data Types that expect IObjects.
 */

#include "openxds.core.adt.h"

#include <openxds.core/IObject.h>

	#ifdef __cplusplus
namespace openxds {
	namespace core {
		namespace adt {
	#endif


struct _IValue
{
	IObject super;
	void*               (*free)( IValue* v );
	void*       (*replaceValue)( IValue* v, void* newValue );
	const void*     (*getValue)( const IValue* v );
};


	#ifdef __cplusplus
};};};
	#endif
#endif
