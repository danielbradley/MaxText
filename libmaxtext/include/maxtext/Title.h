#ifndef MAXTEXT_TITLE_H
#define MAXTEXT_TITLE_H

#include "maxtext/Block.h"

#include <openxds.io.h>
#include <openxds.base.h>

namespace maxtext {

class Title : public Block
{
public:
	         Title( const Line& aLine );
	virtual ~Title();

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;

	openxds::base::String* text;
	int                    level;
};

};

#endif
