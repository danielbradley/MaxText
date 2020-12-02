#ifndef MAXTEXT_CODE_H
#define MAXTEXT_CODE_H

#include "maxtext/Block.h"
#include <openxds.io.h>
#include <openxds.adt.h>
#include <openxds.base.h>

namespace maxtext {
class Code : public Block
{
public:
	static const int START = 1;
	static const int END   = 2;

private:
	int codeType;

public:
	         Code( int codeType );
	virtual ~Code();

	virtual void add( Line* aLine );

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;
};

};

#endif
