/*
 *  Copyright (C) 2004 Daniel Robert Bradley. All rights reserved.
 *
 *  This software is redistributable under the terms of the GNU LGPL
 *  (Lesser General Public License).
 *
 *  I.S.Labs is a registered trademark of Daniel Robert Bradley
 */

#ifndef OPENXDS_CORE_IO_LINK_H
#define OPENXDS_CORE_IO_LINK_H

#include "openxds.core.io.h"

EXPORT	Link*			new_Link();
EXPORT	void			free_Link( Link* self );

EXPORT	void			Link_setTarget( Link* self, const char* aTarget );
EXPORT	int				Link_load( Link* self, const char* location );
EXPORT	void			Link_setAllowDynamic( Link* self, bool value );

EXPORT	int				Link_save( const Link* self, const char* location );
EXPORT	const Path*		Link_getPath( const Link* self );
EXPORT	const char*		Link_getTarget( const Link* self );
EXPORT	const char*		Link_getCanonical( const Link* self );
EXPORT	const char*		Link_getOriginal( const Link* self );

#endif
