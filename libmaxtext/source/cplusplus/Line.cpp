#include "maxtext/Line.h"
#include "maxtext/Reference.h"

#include <openxds.io/PrintWriter.h>
#include <openxds.adt/IDictionary.h>
#include <openxds.adt.std/Dictionary.h>
#include <openxds.base/FormattedString.h>
#include <openxds.base/String.h>
#include <openxds.base/StringBuffer.h>
#include <openxds/Exception.h>
#include <cstdio>

using namespace maxtext;
using namespace openxds;
using namespace openxds::adt;
using namespace openxds::adt::std;
using namespace openxds::base;
using namespace openxds::io;
using namespace openxds::util;

static bool IsSymbol( const char c );
static bool IsNonBraceSymbol( const char c );
static bool IsWhiteSpace( const char c );
static bool IsAlphabetical( const char c );
static bool IsAlphanumeral( const char c );

Line::Line() : Block( Block::LINE )
{
	this->line  = new String();
}

Line::Line( String* aString ) : Block( Block::LINE )
{
	this->line = aString;
}

Line::~Line()
{
	delete this->line;
}

void
Line::print( PrintWriter& p ) const
{
	bool single_quoted = false;
	bool double_quoted = false;
	
	bool italic    = false;
	bool bold      = false;
	bool underline = false;
	bool brackets  = false;

	StringBuffer sb;
	StringBuffer bibkey;

	const char ws = ' ';
	char last = ws;	
	char next = ws;	
	long max = this->line->getLength();
	for ( long i=0; i < max; i++ )
	{
		char c = this->line->charAt( i );
		if ( (i+1) < max )
		{
			next = this->line->charAt( i+1 );
		} else {
			next = ws;
		}

		if ( single_quoted )
		{
			switch ( c )
			{
			case '\'':
				//sb.append( "</font>" );
				sb.append( c );
				single_quoted = false;
				break;
			default:
				sb.append( c );
			}
		}
		else
		{
			switch ( c )
			{
			case '/':
				if ( !italic && ( IsWhiteSpace( last ) || IsSymbol( last ) ) && !IsWhiteSpace( next ) )
				{
					sb.append( "<i>" );
					italic = true;
				}
				else if ( italic && !IsWhiteSpace( last ) )
				{
					sb.append( "</i>" );
					italic = false;
				}
				else
				{
					sb.append( c );
				}
				break;
			case '_':
				if ( !underline && IsWhiteSpace( last ) && !IsWhiteSpace( next ) )
				{
					sb.append( "<u>" );
					underline = true;
				}
				else if ( underline && !IsWhiteSpace( last ) )
				{
					sb.append( "</u>" );
					underline = false;	
				}
				else
				{
					sb.append( c );
				}
				break;
			case '*':
				if ( !bold && IsWhiteSpace( last ) && !IsWhiteSpace( next ) )
				{
					sb.append( "<b>" );
					bold = true;
				}
				else if ( bold && !IsWhiteSpace( last ) )
				{
					sb.append( "</b>" );
					bold = false;
				}
				else
				{
					sb.append( c );
				}
				break;
			case '\"':
				if ( !double_quoted )
				{
					sb.append( c );
					//sb.append( "<font color='green'>" );
					double_quoted = true;
				} else {
					//sb.append( "</font>" );
					sb.append( c );
					double_quoted = false;
				}
				break;
			case '\'':
				if ( IsAlphanumeral( last ) || double_quoted )
				{
					sb.append( c );
				}
				else
				{
					sb.append( c );
					//sb.append( "<font color='darkgreen'>" );
					single_quoted = true;
				}
				break;
			case '\\':
				if ( IsWhiteSpace( last ) )
				{
					while ( (i < (max-1)) && !IsWhiteSpace( this->line->charAt(i+1) ) )
					{
						i++;

						if ( '{' == this->line->charAt(i) )
						{
							while ( (i < (max-1)) && ('}' != this->line->charAt(i)) ) i++;
						}
					}
				}
				break;
			case '[':
				if ( !brackets && IsWhiteSpace( last ) && !IsWhiteSpace( next ) )
				{
					sb.append( "[" );
					brackets = true;
				}
				break;
			case ']':
			case ',':
				if ( !brackets )
				{
					sb.append( c );
				}
				else if ( brackets && !IsWhiteSpace( last ) )
				{
					//	Myers [2003Myers-57] should be seen for...
					
					String* bibkey_str = bibkey.asString();
					{
						const char* key = bibkey_str->getChars();
						try
						{
							IDictionary<Reference>& keys = *Reference::keys;
							IEntry<Reference>* entry = keys.find( key );
							{
								Reference& ref = entry->getValue();

								sb.append( "<a" );
								sb.append( " href='#" );
								sb.append( *ref.key );
								sb.append( "' title='" );
								
								int max = ref.text->getLength();
								for ( int i=0; i < max; i++ )
								{
									char c = ref.text->charAt( i );
									switch ( c )
									{
									case '\t':
										continue;
									default:
										sb.append( c );
									}
								}
								
								sb.append( "'" );
								sb.append( ">" );

								if ( true )
								{
									sb.append( FormattedString( "%i", ref.id ) );
								} else {
									sb.append( *bibkey_str );
								}
								sb.append( "</a>" );
							}
							delete entry;
						}
						catch ( openxds::Exception* ex )
						{
							delete ex;
							sb.append( *bibkey_str );
						}
					}
					delete bibkey_str;
					bibkey.clear();
					sb.append( c );

					if ( ',' != c ) brackets = false;
				}
				else
				{
					sb.append( c );
				}
				break;
			default:
				if ( brackets )
				{
					bibkey.append( c );
				}
				else
				{
					sb.append( c );
				}
			}
		}
		last = c;
	}

	String* str = sb.asString();
	{
		p.printf( "%s\n", str->getChars() ); 
	}
	delete str;
}

void
Line::printTex( PrintWriter& p ) const
{
	bool single_quoted = false;
	bool double_quoted = false;
	
	bool italic    = false;
	bool bold      = false;
	bool underline = false;
	bool brackets  = false;

	int blevel = 0;

	StringBuffer sb;

	const char ws = ' ';
	char last = ws;	
	char next = ws;	
	long max = this->line->getLength();
	for ( long i=0; i < max; i++ )
	{
		char c = this->line->charAt( i );
		if ( (i+1) < max )
		{
			next = this->line->charAt( i+1 );
		} else {
			next = ws;
		}

		if ( single_quoted )
		{
			switch ( c )
			{
			case '\'':
				//sb.append( "</font>" );
				sb.append( c );
				single_quoted = false;
				break;
			case '%':
				sb.append( "\\%" );
				break;
			case '$':
				sb.append( "\\$" );
				break;
			case '|':
				sb.append( "\\textbar{}" );
				break;
			case '#':
				sb.append( "\\#" );
				break;
			case '&':
				sb.append( "\\&" );
				break;
			case '<':
				sb.append( "\\textless{}" );
				break;
			case '>':
				sb.append( "\\textgreater{}" );
				break;
			case '\\':
				if ( (IsWhiteSpace( last ) || IsSymbol( last )) && !IsWhiteSpace( next ) )
				{
					sb.append( c );
				}
				else if ( ('\\' == last) && IsWhiteSpace( next ) )
				{
					sb.append( c );
				}
				else
				{
					sb.append( "\\textbackslash{}" );
				}
				break;
			default:
				sb.append( c );
			}
		}
		else
		{
			switch ( c )
			{
			case '{':
				blevel++;
				sb.append( c );
				break;
			case '}':
				blevel--;
				sb.append( c );
				break;
			case '/':
				if ( !italic && ( IsWhiteSpace( last ) || IsNonBraceSymbol( last ) ) && !IsWhiteSpace( next ) )
				{
					sb.append( "\\emph{" );
					italic = true;
				}
				else if ( italic && !IsWhiteSpace( last ) )
				{
					sb.append( "}" );
					italic = false;
				}
				else
				{
					sb.append( c );
				}
				break;
			case '_':
				if ( !underline && IsWhiteSpace( last ) && !IsWhiteSpace( next ) )
				{
					sb.append( "\\underline{" );
					underline = true;
				}
				else if ( underline && !IsWhiteSpace( last ) )
				{
					sb.append( "}" );
					underline = false;	
				}
				else
				{
					sb.append( c );
				}
				break;
			case '*':
				if ( !bold && IsWhiteSpace( last ) && !IsWhiteSpace( next ) )
				{
					sb.append( "\\textbf{" );
					bold = true;
				}
				else if ( bold && !IsWhiteSpace( last ) )
				{
					sb.append( "}" );
					bold = false;
				}
				else
				{
					sb.append( c );
				}
				break;
			case '[':
			case ']':
				if ( !brackets && IsWhiteSpace( last ) && !IsWhiteSpace( next ) )
				{
					sb.append( "\\cite{" );
					brackets = true;
				}
				else if ( brackets && !IsWhiteSpace( last ) )
				{
					sb.append( "}" );
					brackets = false;
				}
				else
				{
					sb.append( c );
				}
				break;
			case '\"':
				if ( !double_quoted )
				{
					sb.append( "``" );
					//sb.append( "<font color='green'>" );
					double_quoted = true;
				} else {
					//sb.append( "</font>" );
					sb.append( "''" );
					double_quoted = false;
				}
				break;
			case '\'':
				if ( IsAlphanumeral( last ) || double_quoted )
				{
					sb.append( c );
				}
				else
				{
					sb.append( '`' );
					//sb.append( "<font color='darkgreen'>" );
					single_quoted = true;
				}
				break;
			case '%':
				sb.append( "\\%" );
				break;
			case '$':
				sb.append( "\\$" );
				break;
			case '|':
				if ( blevel )
				{
					sb.append( c );
				} else {
					sb.append( "\\textbar{}" );
				}
				break;
			case '#':
				sb.append( "\\#" );
				break;
			case '&':
				if ( blevel )
				{
					sb.append( c );
				} else {
					sb.append( "\\&" );
				}
				break;
			case '<':
				sb.append( "\\textless{}" );
				break;
			case '>':
				sb.append( "\\textgreater{}" );
				break;
			case '\\':
				if ( IsWhiteSpace( last ) && ('&' == next) )
				{
					sb.append( '&' );
					i++;
					c = next;
				}
				else if ( (IsWhiteSpace( last ) || IsSymbol( last )) && !IsWhiteSpace( next ) )
				{
					sb.append( c );
				}
				else if ( ('\\' == last) && IsWhiteSpace( next ) )
				{
					sb.append( "\\" );
				}
				else
				{
					sb.append( "\\textbackslash{}" );
				}
				break;
			default:
				sb.append( c );
			}
		}
		last = c;
	}

	String* str = sb.asString();
	{
		p.printf( "%s\n", str->getChars() ); 
	}
	delete str;
}

const String&
Line::getText() const
{
	return *this->line;
}

bool
Line::isLongLine() const
{
	return ( 100 < this->line->getLength() )	;
}

bool
Line::isWhitespace() const
{
	long max = this->line->getLength();
	for ( long i=0; i < max; i++ )
	{
		int c = this->line->charAt( i );
		if ( (32 < c) && (c < 127) )
		{
			return false;
		}	
	}
	return true;
}

bool
Line::startsWithListNumber() const
{
	int c;
	bool ret = false;
	long max = this->line->getLength();
	for ( long i=0; i < max; i++ )
	{
		c = this->line->charAt( i );
		
		if ( (48 <= c) && (c <= 57) )
		{
			ret = true;
		}
		else if ( ')' == c )
		{
			break;
		}
		else
		{
			ret = false;
			break;
		}

		if ( i == (max-1)) ret = false;
	}
	return ret;
}

bool
Line::startsWithListCharacter() const
{
	return ( this->startsWith( 'o' ) && ( (1 == this->getText().getLength()) || IsWhiteSpace( this->getText().charAt( 1 )) ) );
}

bool
Line::startsWithSquareBrackets() const
{
	bool ret = false;
	if ( this->line->getLength() >= 2 )
	{
		ret = ( ('[' == this->line->charAt( 0 )) && (']' == this->line->charAt( 1 )) );
	}
	return ret;
}

bool
Line::startsWithTab() const
{
	if ( this->line->getLength() > 0 )
	{
		return ( '\t' == this->line->charAt( 0 ) );
	} else {
		return false;
	}
}

int
Line::startsWithDots() const
{
	int dots = 0;
	long max = this->line->getLength();
	for ( long i=0; i < max; i++ )
	{
		if ( ('.' == this->line->charAt( i )) || (',' == this->line->charAt( i )) )
		{
			dots++;
		} else {
			break;
		}
	}
	return dots;	
}

int
Line::startsWith( char c ) const
{
	int dots = 0;
	long max = this->line->getLength();
	for ( long i=0; i < max; i++ )
	{
		if ( c == this->line->charAt( i ) )
		{
			dots++;
		} else {
			break;
		}
	}
	return dots;	
}

//	Hidden Static Helper Functions

bool IsSymbol( const char c )
{
	bool in_range_one   = ((32 < c) && (c < 48));
	bool in_range_two   = ((57 < c) && (c < 65));
	bool in_range_three = ((90 < c) && (c < 97));
	bool in_range_four  = ((122 < c) && (c < 127));

	return ( in_range_one || in_range_two || in_range_three || in_range_four );
}

bool IsNonBraceSymbol( const char c )
{
	bool in_range_one   = ((32 < c) && (c < 48));
	bool in_range_two   = ((57 < c) && (c < 65));
	bool in_range_three = ((90 < c) && (c < 97));
	bool in_range_four  = (124 == c) || (126 == c);

	return ( in_range_one || in_range_two || in_range_three || in_range_four );
}

bool IsWhiteSpace( const char c )
{
	return !( (32 < c) && (c < 127) );
}

bool IsAlphabetical( const char c )
{
	bool uppercase = ( (64 < c) && (c < 91)  );
	bool lowercase = ( (96 < c) && (c < 123) );
	
	return ( uppercase || lowercase );
}

bool IsAlphanumeral( const char c )
{
	bool uppercase = ( (64 < c) && (c < 91)  );
	bool lowercase = ( (96 < c) && (c < 123) );
	bool	 numeral   = ( (47 < c) && (c < 58)  );
	
	return ( uppercase || lowercase || numeral );
}
