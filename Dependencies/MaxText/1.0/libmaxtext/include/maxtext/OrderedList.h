#ifndef MAXTEXT_ORDEREDLIST_H
#define MAXTEXT_ORDEREDLIST_H

#include "maxtext/List.h"
#include <openxds.util.h>
#include <openxds.io.h>

namespace maxtext {

class OrderedList : public List
{
public:
	         OrderedList();
	virtual ~OrderedList();

	virtual void add( Line* aLine );

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;
};

};

#endif
