/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#include "openxds.core.base/CRuntime.h"
#include "openxds.core.base/CTest.h"

#include <stdio.h>

void CTest_PrintResult( const char* id, bool result )
{
	if ( result )
	{
		fprintf( stdout, "%s: PASSED\n", id );
	} else {
		fprintf( stdout, "%s: FAILED\n", id );
	}
}

int CTest_TestFunction( const char* id, bool(*function)() )
{
	int status;
	unsigned long mem = CRuntime_GetAllocationCount();
	status = function();
	mem = CRuntime_GetAllocationCount() - mem;
	
	if ( status )
	{
		fprintf( stdout, "<test result=\"passed\" mem=\"%li\" id=\"%s\"/>\n", mem, id );
	} else {
		fprintf( stdout, "<test result=\"FAILED\" mem=\"%li\" id=\"%s\"/>\n", mem, id );
	}
	return status;
}

int CTest_SkipFunction( const char* id, bool(*function)(), const char* reason )
{
	fprintf( stdout, "<test result=\"SKIPPED\" id=\"%s\">%s</test>\n", id, reason );
	return 0;
}
