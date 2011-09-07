#ifndef MAXTEXT_PREFORMATTED_H
#define MAXTEXT_PREFORMATTED_H

#include "maxtext/Block.h"
#include <openxds.io.h>
#include <openxds.adt.h>
#include <openxds.base.h>

namespace maxtext {

class Preformatted : public Block
{
public:
	         Preformatted();
	virtual ~Preformatted();

	virtual void add( Line* aLine );

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;

	void print2( void* stream ) const;
	openxds::adt::ISequence<Line>* lines;
	openxds::base::StringBuffer* textbuffer;
};

};

#endif
