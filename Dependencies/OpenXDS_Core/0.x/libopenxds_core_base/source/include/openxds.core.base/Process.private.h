/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_PROCESS_PRIVATE_H
#define OPENXDS_CORE_BASE_PROCESS_PRIVATE_H

#include "openxds.core.base/Process.h"

	#ifdef __cplusplus
	namespace openxds {
		namespace core {
			namespace base {
	extern "C"
	{
	#endif


typedef struct _Process Process;

	/*
	 *  Lifecycle functions
	 */
EXPORT		Process* free_Process( Process* self );

	/*
	 *  Functions
	 */
EXPORT		int Process_start( Process* self );
EXPORT		int Process_waitFor( Process* self );

	/*
	 *  Mutators
	 */
EXPORT		void Process_setSearchPath( Process* self, const char* aPath );
EXPORT		void Process_setUsePath( Process* self, int aBoolean );
EXPORT		void Process_setStandardIn( Process* self, const char* location );
EXPORT		void Process_setStandardOut( Process* self, const char* location );
EXPORT		void Process_setStandardError( Process* self, const char* location );

	/*
	 *  Accessors
	 */
EXPORT		const char*  Process_getExecutable( const Process* self );
EXPORT		const char** Process_getArguments( const Process* self );
EXPORT		unsigned int Process_getProcessID( const Process* self );
EXPORT		const char*  Process_getSearchPath( const Process* self );
EXPORT		int	     Process_getExitStatus( const Process* self );

EXPORT		bool         Process_hasFinished( const Process* self );
EXPORT		bool         Process_hasExitedNormally( const Process* self );


	#ifdef __cplusplus
	}
	};};};
	#endif
#endif
