/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_PROCESS_H
#define OPENXDS_CORE_BASE_PROCESS_H

#include "openxds.core/export.h"
#include "openxds.core.base.h"

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace base {
					extern "C" {
	#endif


struct _IProcess
{
	             IProcess*                    (*free)(       IProcess* self );
	             int                         (*start)(       IProcess* self );
	             int                       (*waitFor)(       IProcess* self );

	             void                (*setSearchPath)(       IProcess* self, const char* aPath );
	             void                   (*setUsePath)(       IProcess* self, bool aBoolean );
	             void                (*setStandardIn)(       IProcess* self, const char* aPath );
	             void               (*setStandardOut)(       IProcess* self, const char* aPath );
	             void             (*setStandardError)(       IProcess* self, const char* aPath );

	             const char*         (*getExecutable)( const IProcess* self );
	             const char**         (*getArguments)( const IProcess* self );
	             unsigned int         (*getProcessID)( const IProcess* self );
	             const char*         (*getSearchPath)( const IProcess* self );
	             int                 (*getExitStatus)( const IProcess* self );

	             bool                  (*hasFinished)( const IProcess* self );
	             bool            (*hasExitedNormally)( const IProcess* self );

	             unsigned int         (*getCurrentID)( void );
	             unsigned int   (*getCurrentParentID)( void );
};

EXPORT	IProcess* new_Process( const char* executable, const char** arguments );
EXPORT	unsigned int Process_GetCurrentID(void);
EXPORT	unsigned int Process_GetCurrentParentID(void);


	#ifdef __cplusplus
		};};};};
	#endif
#endif
