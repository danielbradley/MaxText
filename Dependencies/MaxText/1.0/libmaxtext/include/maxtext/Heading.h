#ifndef MAXTEXT_HEADING_H
#define MAXTEXT_HEADING_H

#include "maxtext/Block.h"
#include <openxds.io.h>
#include <openxds.base.h>

namespace maxtext {

class Heading : public Block
{
public:
	         Heading( const Line& aLine, const openxds::base::String& documentType );
	virtual ~Heading();

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;

	openxds::base::String* text;
	openxds::base::String* documentType;
	int                    level;
	bool                   silent;
	
	static int min;
};

};

#endif
