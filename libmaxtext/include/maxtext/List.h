#ifndef MAXTEXT_LIST_H
#define MAXTEXT_LIST_H

#include "maxtext/Block.h"
#include "maxtext.h"
#include <openxds.adt.h>
#include <openxds.io.h>

namespace maxtext {

class List : public Block
{
public:
	         List();
	         List( int type );
	virtual ~List();

	virtual void add( Line* aLine );

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;

	openxds::adt::ISequence<ListItem>* lines;
};

};

#endif
