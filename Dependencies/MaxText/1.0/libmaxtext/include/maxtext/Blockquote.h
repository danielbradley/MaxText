#ifndef MAXTEXT_BLOCKQUOTE_H
#define MAXTEXT_BLOCKQUOTE_H

#include "maxtext/Block.h"
#include <openxds.io.h>

namespace maxtext {

class Blockquote : public Block
{
public:
	static const int START = 1;
	static const int END   = 2;

	         Blockquote( int aType );
	virtual ~Blockquote();

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;

	int                    type;
};

};

#endif
