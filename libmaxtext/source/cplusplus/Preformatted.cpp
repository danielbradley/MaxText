#include "maxtext/Preformatted.h"

#include "maxtext/Line.h"
#include <openxds.io/PrintWriter.h>
#include <openxds.base/String.h>
#include <openxds.base/StringBuffer.h>

#include <cstring>
#include <cstdio>

using namespace maxtext;
using namespace openxds::adt;
using namespace openxds::base;
using namespace openxds::io;

static String* htmlEncode( const char* ch );

Preformatted::Preformatted() : Block( Block::PREFORMATTED )
{
	this->textbuffer = new StringBuffer();
}

Preformatted::~Preformatted()
{
	delete this->textbuffer;
}

void
Preformatted::add( Line* aLine )
{
	this->textbuffer->append( aLine->getText() );
	this->textbuffer->append( '\n' );
	delete aLine;
}

void
Preformatted::print( PrintWriter& p ) const
{
	String* html_encoded = htmlEncode( this->textbuffer->getChars() );
	const char* _html_encoded = html_encoded->getChars();
	{
		p.printf( "<pre>\n" );
		p.print( *html_encoded );
		p.printf( "</pre>\n" );
	}
	delete html_encoded;
}

void
Preformatted::printTex( PrintWriter& p ) const
{
	p.printf( "\\begin{verbatimtab}\n" );
	p.printf( "%s\n", this->textbuffer->getChars() );
	p.printf( "\\end{verbatimtab}\n" );
}

static String* htmlEncode( const char* ch )
{
	StringBuffer sb;
	const char* _sb = sb.getChars();

	long max = strlen( ch );
	for ( long i=0; i < max; i++ )
	{
		switch ( ch[i] )
		{
		case '<':
			sb.append( "&lt;" );
			break;
		case '>':
			sb.append( "&gt;" );
			break;
		default:
			sb.append( ch[i] );
		}
		_sb = sb.getChars();
	}

	return sb.asString();
}
