#ifndef MAXTEXT_PAGE_H
#define MAXTEXT_PAGE_H

#include "maxtext.h"

#include <openxds.io.exceptions/IOException.h>
#include <openxds.io.h>
#include <openxds.adt.h>
#include <openxds.base.h>

namespace maxtext {

class Page
{
public:
	         Page( const openxds::base::String& classType, const openxds::base::String& parameters, const openxds::base::String& packages );
	virtual ~Page();	

	void parse( openxds::io::InputStream& in )
			throw (openxds::io::exceptions::IOException*);

	void parseStyleSheet( openxds::io::InputStream& in )
			throw (openxds::io::exceptions::IOException*);

	void add( Block* aBlock );

	//	public constant methods
	virtual void print( void* stream ) const;
	virtual void print( openxds::io::PrintWriter& p ) const;
	virtual void printTex( openxds::io::PrintWriter& p ) const;

private:
	//	private class methods
	Reference* parseReference( Line& line, openxds::io::LineParser& parser );

	openxds::base::String*   classType;
	openxds::base::String*   parameters;
	openxds::base::String*   packages;
	openxds::base::String*   stylesheet;
	openxds::adt::ISequence<Block>* blocks;

	bool newlineMarksParagraph;
};

};

#endif
