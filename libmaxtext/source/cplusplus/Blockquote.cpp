#include "maxtext/Blockquote.h"

#include <openxds.base/String.h>
#include <openxds.io/PrintWriter.h>

using namespace maxtext;
using namespace openxds::base;
using namespace openxds::io;

#include <cstdio>
#include <cstdlib>

Blockquote::Blockquote( int aType ) : Block( Block::BLOCKQUOTE ), type( aType )
{}

Blockquote::~Blockquote()
{}

void
Blockquote::print( PrintWriter& p ) const
{
	switch ( this->type )
	{
	case START:
		p.printf( "<blockquote>\n" );
		break;
	case END:
		p.printf( "</blockquote>\n" );
	}
}

void
Blockquote::printTex( PrintWriter& p ) const
{
	switch ( this->type )
	{
	case START:
		p.printf( "\\begin{quote}\n" );
		break;
	case END:
		p.printf( "\\end{quote}\n" );
	}
}
