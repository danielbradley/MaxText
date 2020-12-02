/*
 *  Copyright (c) 2004-2010 Daniel Robert Bradley. All rights reserved.
 */

#ifndef OPENXDS_CORE_TYPES_H
#define OPENXDS_CORE_TYPES_H

#ifndef __cplusplus
	#ifndef BOOLEAN
	#define BOOLEAN
		typedef int bool;
	#endif
#endif

#ifndef BYTE
#define BYTE
	#ifndef __RPCNDR_H__
		typedef unsigned char byte;
	#endif
#endif

#ifndef FLAGS
#define FLAGS
	typedef unsigned long int flags;
#endif

#ifndef MASK
#define MASK
	typedef unsigned long int mask;
#endif

#ifndef GENERIC_ELEMENT
#define GENERIC_ELEMENT
	typedef void E;
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#endif
