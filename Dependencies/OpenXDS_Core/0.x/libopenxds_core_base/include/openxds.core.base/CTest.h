/*
 *  Copyright (c) 2008-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_CTEST_H
#define OPENXDS_CORE_BASE_CTEST_H

#include "openxds.core/export.h"
#include "openxds.core/types.h"

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace base {
					extern "C" {
	#endif

EXPORT	void CTest_PrintResult( const char* id, bool result );
EXPORT	int  CTest_TestFunction( const char* id, bool(*function)() );
EXPORT	int  CTest_SkipFunction( const char* id, bool(*function)(), const char* reason );

	#ifdef __cplusplus
		};};};};
	#endif
#endif
