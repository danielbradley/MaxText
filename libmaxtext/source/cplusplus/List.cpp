#include "maxtext/Line.h"
#include "maxtext/List.h"
#include "maxtext/ListItem.h"

#include <openxds.adt/ISequence.h>
#include <openxds.adt.std/Sequence.h>
#include <openxds.io/PrintWriter.h>
#include <openxds.base/String.h>
#include <openxds.base/StringBuffer.h>

#include <cstdio>

using namespace maxtext;
using namespace openxds::adt;
using namespace openxds::base;
using namespace openxds::io;

using openxds::adt::std::Sequence;

List::List() : Block( Block::LIST )
{
	this->lines = new openxds::adt::std::Sequence<ListItem>();
}

List::List( int type ) : Block( type )
{
	this->lines = new openxds::adt::std::Sequence<ListItem>();
}

List::~List()
{
	delete this->lines;
}

void
List::add( Line* aLine )
{
	//	This function may be called either with a line starting with 'o',
	//	in which case it should add a new ListItem, or with a line starting
	//	with something else, in which case it should append that input to
	//	the previous ListItem.
	//
	//	If the line starts with a 'o', then startsWith will return a non-zero
	//	value.
	
	const String& line_text = aLine->getText();
	long           end       = line_text.getLength() - 1;
	long           start     = aLine->startsWith( 'o' );
	long           max       = this->lines->size();

	if ( (0 == start) && (0 < max) )
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
		while ( (start < end) && (' ' == line_text.charAt( start )) ) start++;
	
		this->lines->addLast( new ListItem( line_text.substring( start, end ) ) );	
	}
	
	delete aLine;
}

void
List::print( PrintWriter& p ) const
{
	p.printf( "<ul>\n" );
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
	p.printf( "</ul>\n" );
}

void
List::printTex( PrintWriter& p ) const
{
	p.printf( "\\begin{itemize}\n" );
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
	p.printf( "\\end{itemize}\n" );
}
