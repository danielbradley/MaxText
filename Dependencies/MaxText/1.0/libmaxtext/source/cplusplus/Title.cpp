#include "maxtext/Title.h"
#include "maxtext/Line.h"

#include <openxds.io/PrintWriter.h>
#include <openxds.base/String.h>

using namespace maxtext;
using namespace openxds::base;
using namespace openxds::io;

#include <cstdio>
#include <cstdlib>

Title::Title( const Line& line ) : Block( Block::TITLE )
{
	const String& line_text = line.getText();
	long end = line_text.getLength() - 1;
	while ( '-' == line_text.charAt( end ) )
	{
		end--;
	}

	this->level = line.startsWith( '-' );

	if ( this->level <= end )
	{
		this->text = line_text.substring( this->level, end );
	} else {
		abort();
	}
}

Title::~Title()
{
	delete this->text;
}

void
Title::print( PrintWriter& p ) const
{
	switch ( this->level )
	{
	case 1:
		p.printf( "<header id='title'>%s</header>\n", this->text->getChars() );
		break;
	default:
		p.printf( "<header id='subtitle'>%s</header>\n", this->text->getChars() );
	}
}

void
Title::printTex( PrintWriter& p ) const
{
	switch ( this->level )
	{
	case 1:
		p.printf( "\\title{%s}\n", this->text->getChars() );
		break;
	default:
		p.printf( "\\author{%s}\n", this->text->getChars() );
		p.printf( "\\maketitle\n" );
	}
}
