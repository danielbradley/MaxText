
#include <openxds.util/Arguments.h>
#include <openxds.io/File.h>
#include <openxds.io/FileInputStream.h>
#include <openxds.io/FileOutputStream.h>
#include <openxds.io/IO.h>
#include <openxds.io/Path.h>
#include <openxds.io/PrintWriter.h>
#include <openxds.adt.std/Sequence.h>
#include <openxds.base/Environment.h>
#include <openxds.base/FormattedString.h>
#include <openxds.base/String.h>
#include <openxds.core.base/CharString.h>

#include <maxtext/Page.h>

#include <cstdio>
#include <libgen.h>

using namespace maxtext;
using namespace openxds::adt;
using namespace openxds::adt::std;
using namespace openxds::base;
using namespace openxds::core::base;
using namespace openxds::io;
using namespace openxds::util;

class MTArguments
{
public:
	MTArguments()
	{
		this->outfile     = "";
		this->stylesheet  = "";
		this->format      = "";
		this->classType   = "";
		this->parameters  = "";
		this->packages    = "";
		this->contentOnly = "";
	}
	
	~MTArguments()
	{
	}

	const char* outfile;
	const char* stylesheet;
	const char* format;
	const char* classType;
	const char* parameters;
	const char* packages;
	const char* contentOnly;
};

static bool    parseArguments(        int  argc, const char**            argv,               Sequence<String>& fileLocations, MTArguments& arguments );
static bool   parseArgumentsX(        int  argc,       char**            argv,               Sequence<String>& fileLocations, String**     outfile, String** stylesheet, String** format, String** style );
static void parseMaxTextFiles(       Page& page, const Sequence<String>& fileLocations );
static void includeStylesheet(       Page& page, const char*             stylesheet,   const String& exe_dir );
static void       printPageTo( const Page& page, const char*             outlocation,  const char* format );

int main( int argc, const char** argv )
{
	Environment::init( argc, argv );

	Sequence<String>* file_locations = new Sequence<String>();
	String* executable_directory = Environment::executableDirectory();
	{
		MTArguments args;
		
		if ( parseArguments( argc, argv, *file_locations, args ) )
		{
			String contentOnly( args.contentOnly );

			if ( file_locations->size() > 0 )
			{
				Page page( args.classType, args.parameters, args.packages, contentOnly.contentEquals( "--content-only" ) );
				parseMaxTextFiles( page, *file_locations );
				includeStylesheet( page, args.stylesheet, *executable_directory );
				printPageTo( page, args.outfile, args.format );
			}
		}
		else
		{
			fprintf( stdout, "Usage: max2html\n\t [--format \"html\" | \"tex\"]\n\t [--class \"article\" | \"report\"]\n\t [--parameters twocolumn,A4]\n\t [--packages moreverb,graphicx,epstopdf]\n\t [--out OUTPUT_FILE] <Max Text File> ..." );
		}
	}
	delete executable_directory;
	delete file_locations;

	return 0;
}


bool parseArguments( int argc, const char** argv, Sequence<String>& fileLocations, MTArguments& arguments )
{
	if ( argc <= 1 ) return false;
	
	String* executable = new String( basename( (char*) argv[0] ) );
	for ( int i=1; i < argc; i++ )
	{
		String arg( argv[i] );
		if ( arg.equals( "--style" ) )
		{
			i++;

			if ( i < argc )
			{
				arguments.stylesheet = argv[i];
			}
		}
		else if ( arg.equals( "--format" ) )
		{
			i++;

			if ( i < argc )
			{
				arguments.format = argv[i];
			}
		}
		else if ( arg.equals( "--out" ) )
		{
			i++;

			if ( i < argc )
			{
				arguments.outfile = argv[i];
			}
		}
		else if ( arg.equals( "--class" ) )
		{
			i++;

			if ( i < argc )
			{
				arguments.classType = argv[i];
			}
		}
		else if ( arg.equals( "--parameters" ) )
		{
			i++;

			if ( i < argc )
			{
				arguments.parameters = argv[i];
			}
		}
		else if ( arg.equals( "--packages" ) )
		{
			i++;

			if ( i < argc )
			{
				arguments.packages = argv[i];
			}
		}
		else if ( arg.equals( "--content-only" ) )
		{
			if ( i < argc )
			{
				arguments.contentOnly = argv[i];
			}
		}
		else
		{
			fileLocations.addLast( new String( argv[i] ) );
		}
	}

	if ( 0 == CharString_getLength( arguments.format ) )
	{
		if ( executable->contentEquals( "max2tex" ) )
		{
			arguments.format = "tex";
		}
		else
		{
			arguments.format = "html";
		}
	}

	if ( 0 != CharString_compare( arguments.outfile, "" ) )
	{
		if ( ! CharString_endsWith( arguments.outfile, arguments.format ) )
		{
			FormattedString fs( "%s.%s", arguments.outfile, arguments.format );
			arguments.outfile = new_CharString( fs.getChars() );
		}
	}
	
	if ( 0 == CharString_compare( arguments.classType, "" ) )
	{
		arguments.classType = "article";
	}
	
	delete executable;
	
	return true;
}

bool parseArgumentsX( int argc, char** argv, Sequence<String>& fileLocations, String** outfile, String** stylesheet, String** format, String** classType )
{
	if ( argc <= 1 ) return false;
	
	String* executable = new String( (const char*) basename( argv[0] ) );
	for ( int i=1; i < argc; i++ )
	{
		String arg( argv[i] );
		if ( arg.equals( "--style" ) )
		{
			i++;

			if ( i < argc )
			{
				delete *stylesheet;
				*stylesheet = new String( argv[i] );
			}
		}
		else if ( arg.equals( "--format" ) )
		{
			i++;

			if ( i < argc )
			{
				delete *format;
				*format = new String( argv[i] );
			}
		}
		else if ( arg.equals( "--out" ) )
		{
			i++;

			if ( i < argc )
			{
				delete *outfile;
				*outfile = new String( argv[i] );
			}
		}
		else if ( arg.equals( "--class" ) )
		{
			i++;

			if ( i < argc )
			{
				delete *classType;
				*classType = new String( argv[i] );
			}
		}
		else
		{
			fileLocations.addLast( new String( argv[i] ) );
		}
	}

	if ( ! *format )
	{
		if ( executable->contentEquals( "max2tex" ) )
		{
			*format = new String( "tex" );
		}
		else
		{
			*format = new String( "html" );
		}
	}

	if ( *outfile && !(*outfile)->endsWith( **format ) )
	{
		*outfile = new FormattedString( "%s.%s", (*outfile)->getChars(), (*format)->getChars() );
	}
	
	if ( ! *classType )
	{
		*classType = new String( "article" );
	}
	
	delete executable;
	
	return true;
}

void parseMaxTextFiles( Page& page, const Sequence<String>& fileLocations )
{
	IPIterator<String>* it = fileLocations.positions();
	while ( it->hasNext() )
	{
		IPosition<String>* p = it->next();
		{
			const String& location = p->getElement();
			const char* _location = location.getChars();
			File file( _location );
//			const char* _absolute = file.getPath().getAbsolute().getChars();
			if ( file.exists() )
			{
				FileInputStream   in( file );
				page.parse( in );
			}
		}
		delete p;
	}
	delete it;
}

void includeStylesheet( Page& page, const char* stylesheet, const String& exe_dir )
{
	if ( 0 < CharString_getLength( stylesheet ) )
	{
		File cssfile( stylesheet );
		if ( cssfile.exists() )
		{
			FileInputStream cssin( cssfile );
			page.parseStyleSheet( cssin );
		}
	} else {
		FormattedString default_css_location( "%s/../share/css/style.css.txt", exe_dir.getChars() );
		File                         cssfile( default_css_location );

		if ( cssfile.exists() )
		{
			//	style sheet may be in FHS share dir.

			FileInputStream   cssin( cssfile );
		
			page.parseStyleSheet( cssin );
		}
		else
		{
			//	style sheet may be in OpenStep style resources dir.
		
			FormattedString default_css_location( "%s/../../resources/css/style.css.txt", exe_dir.getChars() );
			File                         cssfile( default_css_location );
		
			if ( cssfile.exists() )
			{
				FileInputStream   cssin( cssfile );

				page.parseStyleSheet( cssin );
			}
		}
	}
}

void printPageTo( const Page& page, const char* outlocation, const char* format )
{
	if ( 0 != CharString_compare( outlocation, "" ) )
	{
		File             outfile( outlocation );
		FileOutputStream      os( outfile );
		PrintWriter           out( os );

		if ( 0 == CharString_compare( format, "tex" ) )
		{
			page.printTex( out );
		} else {
			page.print( out );
		}
	} else {
		if ( 0 == CharString_compare( format, "tex" ) )
		{
			page.printTex( IO::out() );
		} else {
			page.print( IO::out() );
		}
	}
}


