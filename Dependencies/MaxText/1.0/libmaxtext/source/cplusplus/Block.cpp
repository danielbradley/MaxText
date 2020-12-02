#include "maxtext/Block.h"

#include <cstdio>
#include <cstdlib>

using namespace maxtext;

Block::Block( int aType )
{
	this->type = aType;
}

Block::~Block()
{}

void
Block::add( Line* aLine )
{
	fprintf( stderr, "Adding Line to non-container Block, aborting!\n" );
	abort();
}

int
Block::getType() const
{
	return this->type;	
}
