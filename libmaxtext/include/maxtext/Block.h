#ifndef MAXTEXT_BLOCK_H
#define MAXTEXT_BLOCK_H

#include "maxtext.h"

#include <openxds.io.h>
#include <openxds/Object.h>

namespace maxtext {

class Block : public openxds::Object
{
public:
	static const int HEADING      = 1;
	static const int LINE         = 2;
	static const int LIST         = 3;
	static const int LISTITEM     = 4;
	static const int ORDEREDLIST  = 5;
	static const int PARAGRAPH    = 6;
	static const int PREFORMATTED = 7;
	static const int REFERENCE    = 8;
	static const int TITLE        = 9;
	static const int BLOCKQUOTE   = 10;
	static const int MARGINNOTE   = 11;

	         Block( int aType );
	virtual ~Block();
	
	virtual void add( Line* aLine );
	
	virtual void print( openxds::io::PrintWriter& p ) const = 0;
	virtual void printTex( openxds::io::PrintWriter& p ) const = 0;

	int getType() const;

private:
	int type;
};

};

#endif
