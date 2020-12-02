#include "maxtext/MarginNote.h"

#include "maxtext/Line.h"
#include <openxds.io/PrintWriter.h>
#include <openxds.adt.std/Sequence.h>
#include <openxds.base/String.h>
#include <openxds.base/StringBuffer.h>

#include <cstdio>

using namespace maxtext;
using namespace openxds::base;
using namespace openxds::io;

MarginNote::MarginNote() : Block( Block::MARGINNOTE )
{
	this->textbuffer = new StringBuffer();
//	this->lines      = new Sequence();
}

MarginNote::~MarginNote()
{
	delete this->textbuffer;
//	delete this->lines;
}

void
MarginNote::add( Line* aLine )
{
	this->textbuffer->append( aLine->getText() );
	this->textbuffer->append( '\n' );
	//this->lines->add( aLine );	
	delete aLine;
}

void
MarginNote::print( PrintWriter& p ) const
{
	p.printf( "<p class='marginnote'>\n" );
	p.printf( "%s\n", this->textbuffer->getChars() );
	p.printf( "</p>\n" );
}

void
MarginNote::printTex( PrintWriter& p ) const
{
	p.printf( "\\marginpar{" );
	p.printf( "%s", this->textbuffer->getChars() );
	p.printf( "}\n" );
}
