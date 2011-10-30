#ifndef MAXTEXT_LISTITEM_H
#define MAXTEXT_LISTITEM_H

#include "maxtext/Line.h"
#include <openxds.io.h>
#include <openxds.base.h>

namespace maxtext {

class ListItem : public Line
{
public:
	         //ListItem();
	         ListItem( openxds::base::String* aString );
	virtual ~ListItem();

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;
	
	const openxds::base::String& getText() const;

private:	
	openxds::base::String* text;
};

};

#endif
