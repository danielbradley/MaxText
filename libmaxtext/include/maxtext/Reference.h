#ifndef MAXTEXT_REFERENCE_H
#define MAXTEXT_REFERENCE_H

#include "maxtext/Block.h"

#include <openxds.util.h>
#include <openxds.io.h>
#include <openxds.adt/IDictionary.h>
#include <openxds.base.h>

namespace maxtext {

class Reference : public Block
{
public:
	         Reference();
	virtual ~Reference();

	virtual void append( const Line& aLine );
	virtual void appendLine( const Line& aLine );

	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;
	
	openxds::base::String*       key;
	openxds::base::StringBuffer* text;
	int                          id;
	
	static int number;
	static int printed;
	static openxds::adt::IDictionary<Reference>* keys;
};

};

#endif
