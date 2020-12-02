#ifndef MAXTEXT_MARGINNOTE_H
#define MAXTEXT_MARGINNOTE_H

#include "maxtext/Block.h"
#include <openxds.io.h>
#include <openxds.adt.h>
#include <openxds.base.h>

namespace maxtext {

class MarginNote : public Block
{
public:
	         MarginNote();
	virtual ~MarginNote();

	virtual void add( Line* aLine );

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;

	void print2( void* stream ) const;
//	openxds::adt::ISequence<>* lines;
	openxds::base::StringBuffer* textbuffer;
};

};

#endif
