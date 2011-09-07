#include "maxtext/Paragraph.h"
#include "maxtext/Line.h"

#include <openxds.io/PrintWriter.h>
#include <openxds.adt.std/Sequence.h>
#include <openxds.adt/IPIterator.h>
#include <openxds.adt/IPosition.h>

#include <cstdio>

using namespace maxtext;
using namespace openxds::adt;
using namespace openxds::adt::std;
using namespace openxds::base;
using namespace openxds::io;

Paragraph::Paragraph() : Block( Block::PARAGRAPH )
{
	this->lines = new Sequence<Line>();
}

Paragraph::~Paragraph()
{
	delete this->lines;
}

void
Paragraph::add( Line* aLine )
{
	this->lines->addLast( aLine );	
}

void
Paragraph::print( PrintWriter& p ) const
{
	p.printf( "<p class='paragraph'>\n" );
	IPIterator<Line>* it = this->lines->positions();
	while ( it->hasNext() )
	{
		IPosition<Line>* pos = it->next();
		{
			pos->getElement().print( p );
		}
		delete pos;
	}
	delete it;
	p.printf( "</p>\n" );
}

void
Paragraph::printTex( PrintWriter& p ) const
{
	p.printf( "\n" );
	IPIterator<Line>* it = this->lines->positions();
	while ( it->hasNext() )
	{
		IPosition<Line>* pos = it->next();
		{
			pos->getElement().printTex( p );
		}
		delete pos;
	}
	delete it;
	p.printf( "\n" );
}

bool
Paragraph::isEmpty() const
{
	return (bool) !this->lines->size();	
}
