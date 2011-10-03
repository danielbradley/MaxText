#include "maxtext/Line.h"
#include "maxtext/Reference.h"

#include <openxds.io/PrintWriter.h>
#include <openxds.adt.std/Dictionary.h>
#include <openxds.base/String.h>
#include <openxds.base/StringBuffer.h>

#include <cstdio>

using namespace maxtext;
using namespace openxds::adt;
using namespace openxds::adt::std;
using namespace openxds::base;
using namespace openxds::io;

int Reference::number = 0;
int Reference::printed = 0;
openxds::adt::IDictionary<Reference>* Reference::keys = new Dictionary<Reference>();

static bool isWhitespace( char c )
{
	switch ( c )
	{
		case ' ':
		case '\t':
			return true;
		default:
			return false;
	};
}

Reference::Reference() : Block( Block::REFERENCE )
{
	this->text = new StringBuffer();
	this->id   = this->number++ + 1;
}

Reference::~Reference()
{
	delete this->text;
}

void
Reference::append( const Line& aLine )
{
	const String& line_text = aLine.getText();
	long end   = line_text.getLength() - 1; 
	long start = 1;
	
	while ( (start <= end) && (']' != line_text.charAt( start )) )
	{
		start++;
	}

	this->key = line_text.substring( 1, start - 1 );

	String* str = line_text.substring( start + 1, end );
	this->text->append( *str );
	delete str;
	
	delete keys->insert( this->key->getChars(), this );
}

void
Reference::appendLine( const Line& aLine )
{
	const String& line_text = aLine.getText();
	long end   = line_text.getLength() - 1; 
	long start = 0;
	
	while ( (start <= end) && ( isWhitespace( line_text.charAt( start )) ) )
	{
		start++;
	}

	String* str = line_text.substring( start, end );
	this->text->append( " " );
	this->text->append( *str );
	delete str;
}

void
Reference::print( PrintWriter& p ) const
{
	if ( 1 == this->id )
	{
		p.printf( "<table class='references'>\n" );
	}
	
	p.printf( "<tr>\n" );
	p.printf( "<td class='bibkey'><a name='%s'>", this->key->getChars() );
	p.printf( "[%i]", this->id );
	//p.printf( "[%s]", this->key->getString().getChars() );
	p.printf( "</a></td>\n" );

	p.printf( "<td class='reference'>" );
	p.printf( "%s", this->text->getChars() );
	p.printf( "</td>\n" );
	
	if ( number == this->id )
	{
		p.printf( "</table>\n" );
	}
}

void
Reference::printTex( PrintWriter& p ) const
{
	if ( 0 == printed ) p.printf( "\\begin{thebibliography}{%i}\n\n", this->number + 1 );

	p.printf( "\\bibitem{%s}\n%s\n\n", this->key->getChars(), this->text->getChars() );
	printed++;

	if ( number == printed ) p.printf( "\\end{thebibliography}\n\n" );
}
