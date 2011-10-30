#ifndef MAXTEXT_LINE_H
#define MAXTEXT_LINE_H

#include "maxtext/Block.h"
#include <openxds.io.h>
#include <openxds.base.h>

namespace maxtext {

class Line : public Block
{
public:
	static const int NORMAL            = 0;
	static const int INDOUBLEQUOTE     = 1;
//	public static int INQUOTETHENDOUBLE = 2;
//	public static int INDOUBLE          = 4;
//	public static int INDOUBLETHENQUOTE = 8;

	         Line();
	         Line( openxds::base::String* aString );
			 Line( openxds::base::String* aString, int aType );
	virtual ~Line();

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;

	bool isLongLine() const;
	bool isWhitespace() const;
	bool startsWithListNumber() const;
	bool startsWithListCharacter() const;
	bool startsWithSquareBrackets() const;
	bool startsWithTab() const;
	int  startsWithDots() const;
	int  startsWith( char c ) const;
	
	const openxds::base::String& getText() const;

private:	
	openxds::base::String* line;
};

};

#endif
