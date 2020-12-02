#ifndef MAXTEXT_PARAGRAPH_H
#define MAXTEXT_PARAGRAPH_H

#include "maxtext/Block.h"
#include <openxds.io.h>
#include <openxds.adt.h>

namespace maxtext {

class Paragraph : public Block
{
public:
	         Paragraph();
	virtual ~Paragraph();

	virtual void add( Line* aLine );

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;

	bool isEmpty() const;

private:
	openxds::adt::ISequence<Line>* lines;
};

};

#endif
