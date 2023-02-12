#include "maxtext/Line.h"
#include "maxtext/ListItem.h"
#include "maxtext/OrderedList.h"

#include <openxds.io/PrintWriter.h>
#include <openxds.adt/IPIterator.h>
#include <openxds.adt.std/Sequence.h>
#include <openxds.base/String.h>
#include <openxds.base/StringBuffer.h>

#include <cstdio>

using namespace maxtext;
using namespace openxds::adt;
using namespace openxds::adt::std;
using namespace openxds::base;
using namespace openxds::io;

static bool isNumber( char c );

OrderedList::OrderedList() : List( Block::ORDEREDLIST )
{}

OrderedList::~OrderedList()
{}

void
OrderedList::add( Line* aLine )
{
	//	See comment in List::add()

	const String& line_text = aLine->getText();
	long           end       = line_text.getLength() - 1;
	long           start     = 0;
	long           max       = this->lines->size();

	bool append = false;
	if ( 0 < max )
	{
		//	Set append to true if the line:
		//		doesn't start with a number
		//	AND doesn't start with a hash '#'

		append = (!aLine->startsWithListNumber() && !aLine->startsWith( '#' ));
	}

	if ( append )
	{
		ListItem* last = this->lines->removeLast();
		if ( last )
		{
			StringBuffer sb;
			
			sb.append( last->getText() );
			sb.append( "\n" );
			sb.append( line_text );
			this->lines->addLast( new ListItem( sb.asString() ) );
		}
		delete last;
	}
	else
	{
		while ( (start <= end) && isNumber( line_text.charAt( start )) ) start++;
		while ( (start <= end) && (')'   == line_text.charAt( start )) ) start++;
		while ( (start <= end) && ('#'   == line_text.charAt( start )) ) start++;
		while ( (start <= end) && (' '   == line_text.charAt( start )) ) start++;
	
		this->lines->addLast( new ListItem( line_text.substring( start, end ) ) );
	}
	delete aLine;
}

void
OrderedList::print( PrintWriter& p ) const
{
	p.printf( "<ol>\n" );
	IPIterator<ListItem>* it = this->lines->positions();
	while ( it->hasNext() )
	{
		IPosition<ListItem>* pos = it->next();
		{
			const ListItem& line = pos->getElement();
			line.print( p );
		}
		delete pos;
	}
	delete it;
	p.printf( "</ol>\n" );
}

void
OrderedList::printTex( PrintWriter& p ) const
{
	p.printf( "\\begin{enumerate}\n\\itemsep-0.5em\n" );
	IPIterator<ListItem>* it = this->lines->positions();
	while ( it->hasNext() )
	{
		IPosition<ListItem>* pos = it->next();
		{
			const ListItem& line = pos->getElement();
			line.printTex( p );
		}
		delete pos;
	}
	delete it;
	p.printf( "\\end{enumerate}\n" );
}

bool isNumber( char c )
{
	return ( (48 <= c) && (c <= 57) );
}

