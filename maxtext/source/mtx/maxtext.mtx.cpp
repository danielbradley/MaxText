-	MaxText - tools for manipulating the processing mtx files
-	D. Bradley

,	License

This software is distributed under the terms of the GPLv3.

.	About

MaxText is a simple text format similar to the wikipedia format.

.	Implementation

..		Includes

...			Local includes

~source/cplusplus/main.cpp~
#include "maxtext/Page.h"
~

...			Third-party includes

~source/cplusplus/main.cpp~
#include <openxds.util/Arguments.h>
#include <openxds.io/File.h>
#include <openxds.io/FileInputStream.h>
#include <openxds.io/FileOutputStream.h>
#include <openxds.io/IO.h>
#include <openxds.io/Path.h>
#include <openxds.io/PrintWriter.h>
#include <openxds.adt.std/Sequence.h>
#include <openxds.base/Environment.h>
#include <openxds.base/FormattedString.h>
#include <openxds.base/String.h>
~

...			System

~source/cplusplus/main.cpp~
#include <cstdio>
#include <libgen>
~

