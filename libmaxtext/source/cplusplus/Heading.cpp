#include "maxtext/Heading.h"
#include "maxtext/Line.h"

#include <openxds.base/String.h>
#include <openxds.io/PrintWriter.h>

using namespace maxtext;
using namespace openxds::base;
using namespace openxds::io;

#include <cstdio>
#include <cstdlib>

Heading::Heading( const Line& line, const String& documentType ) : Block( Block::HEADING )
{
	const String& line_text = line.getText();
	long end = line_text.getLength() - 1;

	this->documentType = new String( documentType );
	this->level = line.startsWithDots();

	if ( ',' == line_text.charAt( 0 ) )
	{
		this->silent = true;
	} else {
		this->silent = false;
	}

	// |...0|
	// |0123|

	// |...T0|
	// |0123456|

	if ( this->level <= end )
	{
		this->text = line_text.substring( this->level, end );
	} else {
		this->text = line_text.substring( this->level, end );
		//abort();
	}
}

Heading::~Heading()
{
	delete this->text;
}

void
Heading::print( PrintWriter& p ) const
{
	int _level = this->level + 1;

	switch ( this->level )
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		p.printf( "<h%i>%s</h%i>\n", _level, this->text->getChars(), _level );
		break;
	default:
		p.printf( "<p class='h%i'>%s ", _level, this->text->getChars() );
		break;
		p.printf( "<p class='h%i'>%s ", _level, this->text->getChars() );
		break;
	}
}

void
Heading::printTex( PrintWriter& p ) const
{
	const char* c = "";
	if ( this->silent )
	{
		c = "*";
	}

	int context_level = this->level;
	if ( this->documentType->contentEquals( "book" ) || this->documentType->contentEquals( "report" ) )
	{
		context_level--;
	}

	switch ( context_level )
	{
	case 0:
		p.printf( "\\chapter%s{%s}\n", c, this->text->getChars() );
		break;
	case 1:
		p.printf( "\\section%s{%s}\n", c, this->text->getChars() );
		break;
	case 2:
		p.printf( "\\subsection%s{%s}\n", c, this->text->getChars() );
		break;
	case 3:
		p.printf( "\\subsubsection%s{%s}\n", c, this->text->getChars() );
		break;
	case 4:
		p.printf( "\\paragraph%s{%s}\\\n", c, this->text->getChars() );
		break;
	default:
	case 5:
		p.printf( "\\subparagraph%s{%s}\\\n", c, this->text->getChars() );
		break;
	}
}
