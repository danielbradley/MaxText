#include "maxtext/ListItem.h"

#include <openxds.base/String.h>
#include <openxds.io/PrintWriter.h>
#include <cstdio>

using namespace maxtext;
using namespace openxds::base;
using namespace openxds::io;

ListItem::ListItem( String* aString ) : Line( aString, Block::LISTITEM )
{
//	this->text = aString.asSt;
}

ListItem::~ListItem()
{
//	delete this->text;
}

void
ListItem::print( PrintWriter& p ) const
{
	p.printf( "<li>" );
	Line::print( p );
	p.printf( "</li>" );
	
	//p.printf( "<li>\n%s\n</li>\n", this->getText().getChars() );
}

void
ListItem::printTex( PrintWriter& p ) const
{
	p.printf( "\\item\n%s\n", this->getText().getChars() );
}

const String&
ListItem::getText() const
{
	return Line::getText();// *this->text;
}
