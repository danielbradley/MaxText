#include "maxtext/Code.h"

#include "maxtext/Line.h"
#include <openxds.io/PrintWriter.h>
#include <openxds.base/String.h>
#include <openxds.base/StringBuffer.h>
#include <openxds.base/StringTokenizer.h>

#include <cstring>
#include <cstdio>

using namespace maxtext;
using namespace openxds::adt;
using namespace openxds::base;
using namespace openxds::io;

Code::Code( int codeType ) : Block( Block::CODE )
{
	this->codeType = codeType;
}

Code::~Code()
{}

void
Code::add( Line* aLine )
{}

void
Code::print( PrintWriter& p ) const
{
	switch ( this->codeType )
	{
	case START:
		p.println( "<code>" );
		break;

	case END:
		p.println( "</code>" );
		break;
	}
}

void
Code::printTex( PrintWriter& p ) const
{}
