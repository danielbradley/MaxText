/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_BASE_CHARSTRINGLIST_H
#define OPENXDS_CORE_BASE_CHARSTRINGLIST_H

#include "openxds.core/export.h"

	#ifdef __cplusplus
		namespace openxds {
			namespace core {
				namespace base {
					extern "C" {
	#endif

/*
 *  Lifecycle functions
 */
EXPORT char** new_CharStringList( void );
EXPORT char** new_CharStringList_from( const char** list );
EXPORT char** new_CharStringList_size( int size );
EXPORT char** free_CharStringList( char** self );

EXPORT int CharStringList_copyItem( char** self, const char* item );

/*
 *  Allocating const functions
 */
EXPORT char* CharStringList_toCharString( const char** self );

/*
 *  Information functions
 */
EXPORT unsigned int CharStringList_getLength( const char** self );

	#ifdef __cplusplus
		};};};};
	#endif
#endif
