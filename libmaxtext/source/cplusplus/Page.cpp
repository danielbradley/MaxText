#include "maxtext/Page.h"

#include "maxtext/Blockquote.h"
#include "maxtext/Heading.h"
#include "maxtext/Line.h"
#include "maxtext/List.h"
#include "maxtext/MarginNote.h"
#include "maxtext/OrderedList.h"
#include "maxtext/Paragraph.h"
#include "maxtext/Preformatted.h"
#include "maxtext/Reference.h"
#include "maxtext/Title.h"

#include <openxds.base/String.h>
#include <openxds.base/StringBuffer.h>
#include <openxds.base/StringTokenizer.h>
#include <openxds.io/File.h>
#include <openxds.io/FileOutputStream.h>
#include <openxds.io/InputStream.h>
#include <openxds.io/LineParser.h>
#include <openxds.io/Printer.h>
#include <openxds.io/PrintWriter.h>
#include <openxds.io.exceptions/IOException.h>
#include <openxds.adt.std/Sequence.h>
#include <openxds.adt/IPIterator.h>
#include <openxds.adt/IPosition.h>

#include <cstdio>

using namespace maxtext;
using namespace openxds::adt;
using namespace openxds::adt::std;
using namespace openxds::base;
using namespace openxds::io;
using namespace openxds::io::exceptions;

Page::Page( const String& classType, const String& parameters, const String& packages, bool contentOnly )
{
	this->classType  = new String( classType );
	this->parameters = new String( parameters );
	this->packages   = new String( packages );
	this->stylesheet = new String();
	this->blocks     = new openxds::adt::std::Sequence<Block>();

	this->newlineMarksParagraph = false;
	this->contentOnly = contentOnly;
}

Page::~Page()
{
	delete this->classType;
	delete this->parameters;
	delete this->packages;
	delete this->stylesheet;
	delete this->blocks;
}

void
Page::parse( InputStream& in )
throw (IOException*)
{
	LineParser parser( in );
	
	Block* block = new Paragraph();

	bool in_skip       = false;
	bool in_blockquote = false;
	//bool in_marginnote = false;
	
	while ( !parser.hasFinished() )
	{
		Line* line = new Line( parser.readLine() );
		{
			if ( in_skip )
			{
				if ( line->startsWith( '!' ) ) in_skip = false;
			}
			else
			{
				if ( line->isLongLine() )
				{
					this->newlineMarksParagraph = true;
				}
				
				if ( line->isWhitespace() )
				{
					this->add( block );
					block = new Paragraph();
				}
				else if ( line->startsWithDots() )
				{
					this->add( block );
					this->add( new Heading( *line, *this->classType ) );
					delete line;
					block = new Paragraph();	
				}
				//else if ( line->startsWithSquareBrackets() )
				else if ( line->startsWith( '[' ) )
				{
					fprintf( stderr, "Page::parseReference\n" );
					this->add( block );
					{
						Reference* ref = this->parseReference( *line, parser );
						delete line;
						
						bool loop = true;
						while ( loop && !parser.hasFinished() )
						{
							line = new Line( parser.readLine() );
							if ( line->isWhitespace() )
							{
								loop = false;
							}
							else if ( line->startsWithSquareBrackets() )
							{
								this->add(ref);
								ref = this->parseReference( *line, parser );
							}
							else
							{
								ref->appendLine( *line );
							}
							delete line;
						}
						
						this->add( ref );
					}
					block = new Paragraph();	
				}
				else if ( line->startsWith( '-' ) )
				{
					this->add( block );
					this->add( new Title( *line ) );
					delete line;
					block = new Paragraph();	
				}
				else if ( line->startsWithListCharacter() )
				{
					if ( Block::LIST != block->getType() )
					{
						this->add( block );
						block = new List();
					}
					block->add( line );
				}
				else if ( line->startsWithListNumber() )
				{
					if ( Block::ORDEREDLIST != block->getType() )
					{
						this->add( block );
						block = new OrderedList();
					}
					block->add( line );
				}
				else if ( line->startsWith( '~' ) )
				{
					const char* _line = line->getText().getChars();
					this->add( block );
					block = new Preformatted( *line );
					delete line;

					bool loop = true;
					while ( loop && !parser.hasFinished() )
					{
						line = new Line( parser.readLine() );
						const char* _line = line->getText().getChars();
						if ( line->startsWith( '~' ) )
						{
							delete line;
							loop = false;
						} else {
							block->add( line );
						}
					}
					this->add( block );
					block = new Paragraph();
				}
				else if ( line->startsWith( '@' ) )
				{
					delete line;
					this->add( block );
					block = new MarginNote();
					bool loop = true;
					while ( loop && !parser.hasFinished() )
					{
						line = new Line( parser.readLine() );
						if ( line->startsWith( '@' ) )
						{
							delete line;
							loop = false;
						} else {
							block->add( line );
						}
					}
					this->add( block );
					block = new Paragraph();
				}
				else if ( line->startsWith( '!' ) )
				{
					if ( !in_skip )
					{
						this->add( block );
						block = new Paragraph();
						in_skip = true;
					}
					else
					{
						delete block;
						block = new Paragraph();
						in_skip = false;
					}
				}
				else if ( line->startsWith( '|' ) )
				{
					this->add( block );
					
					if ( !in_blockquote )
					{
						this->add( new Blockquote( Blockquote::START ) );
						block = new Paragraph();
						in_blockquote = true;
					} else {
						this->add( new Blockquote( Blockquote::END ) );
						block = new Paragraph();
						in_blockquote = false;
					}
				}
				else if ( line->startsWithTab() )
				{
					if ( Block::PARAGRAPH == block->getType() )
					{
						this->add( block );
						block = new Paragraph();
					}
					block->add( line );				
				}
				else
				{
					block->add( line );
				}
			}
		}
	}
	
	if ( block ) this->add( block );
}

void
Page::parseStyleSheet( InputStream& in )
throw (IOException*)
{
	delete this->stylesheet;
	StringBuffer sb;
	LineParser parser( in );

	while ( !parser.hasFinished() )
	{
		String* str = parser.readLine();
		sb.append( *str );
		delete str;
	}

	this->stylesheet = sb.asString();
}

void
Page::add( Block* aBlock )
{
	if ( Block::PARAGRAPH == aBlock->getType() )
	{
		if ( dynamic_cast<const Paragraph*>( aBlock )->isEmpty() )
		{
			delete aBlock;
		} else {
			this->blocks->addLast( aBlock );
		}
	} else {
		this->blocks->addLast( aBlock );	
	}
}

void
Page::print( void* stream ) const
{
	FILE* f = (FILE*) stream;

	File             file( f );
	FileOutputStream   os( file );
	PrintWriter       out( os );

	this->print( out );
}

void
Page::print( PrintWriter& p ) const
{
	if ( ! this->contentOnly )
	{
		p.printf( "<html>\n" );
		p.printf( "<head>\n" );
		p.printf( "<meta name='viewport' content='width=device-width'>\n" );
		if ( this->stylesheet->getLength() )
		{
			p.printf( "<style type='text/css'>\n" );
			p.println( this->stylesheet->getChars() );
			p.printf( "</style>\n" );
		}
		p.printf( "</head>\n" );
		p.printf( "<body class='maxtext'>\n" );
	}
	//p.printf( "<div class='maxtext'>\n" );
	
	IPIterator<Block>* it = this->blocks->positions();
	while ( it->hasNext() )
	{
		IPosition<Block>* pos = it->next();
		{
			pos->getElement().print( p );
		}
		delete pos;
	}
	delete it;
	//p.printf( "</div>\n" );

	if ( ! this->contentOnly )
	{
		p.printf( "</body>\n" );
		p.printf( "</html>\n" );
	}
}

void
Page::printTex( PrintWriter& p ) const
{
	p.printf( "\\documentclass[%s]{%s}\n", this->parameters->getChars(), this->classType->getChars() );
	//p.printf( "\\usepackage{fullpage}\n" );
	p.printf( "\\usepackage{moreverb}\n" );
	p.printf( "\\usepackage{verbatim}\n" );
	p.printf( "\\usepackage{graphicx}\n" );
	p.printf( "\\usepackage{epstopdf}\n" );
	p.printf( "\\usepackage{float}\n" );
	p.printf( "\\usepackage{textcomp}\n" );
	//p.printf( "\\usepackage[utf8]{inputenc}\n" );

	openxds::base::StringTokenizer st( *this->packages );
	st.setDelimiter( ',' );
	while ( st.hasMoreTokens() )
	{
		String* token = st.nextToken();
		p.printf( "\\usepackage{%s}\n", token->getChars() );
		delete token;
	}
	p.printf( "\\makeindex\n" );
	p.printf( "\\makeglossaries\n" );

	p.printf( "\\begin{document}\n" );
	
	IPIterator<Block>* it = this->blocks->positions();
	while ( it->hasNext() )
	{
		IPosition<Block>* pos = it->next();
		{
			pos->getElement().printTex( p );
		}
		delete pos;
	}
	delete it;

	p.printf( "\\end{document}\n" );
}

Reference*
Page::parseReference( Line& line, LineParser& parser )
{
	Reference* ref = new Reference();
	ref->append( line );
	
	return ref;
}
