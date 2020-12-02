#include "openxds.core.base/Math.h"
#include <math.h>

long
Math_constrainBetween( long aNumber, long lower, long upper )
{
	if ( aNumber < lower )
	{
		aNumber = lower;
	}
	else if ( upper < aNumber )
	{
		aNumber = upper;
	}
	return aNumber;
}

bool
Math_isAlmostEqual( double a, double b )
{
	return ( (a == b) || (0.00001 > fabs( a - b )) );
}

bool Math_isBetween( long aNumber, long lower, long upper )
{
	return ((lower < aNumber) && (aNumber < upper ));
}

double
Math_floor( double aValue )
{
	int anInteger = (int) aValue;
	double aDouble = (double) anInteger;
	if ( aDouble > aValue )
	{
		anInteger -= 1;
		aDouble = (double) anInteger;
	}
	return aDouble;
}

long
Math_max( long a, long b )
{
	return (a > b) ? a : b;
}

long
Math_min( long a, long b )
{
	return (a < b) ? a : b;
}

double
Math_pi()
{
	return 3.14159265;
}

long
Math_sizeOfRange( double first, double last, double increment )
{
	int size = 0;
	double i;

	if ( Math_isAlmostEqual( first, last ) )
	{
		size++;
	}
	else
	{
		for ( i=first; i < last; i += increment )
		{
			size++;
		}
		if ( Math_isAlmostEqual( i, last ) )
		{
			size++;
		}
	}
	return size;
}

double
Math_squareroot( double aValue )
{
	return sqrt( aValue );
}

double
Math_toPower( double base, double power )
{
	return pow( base, power );
}

long double
Math_toPower_long_double( long double base, long double power )
{
	return powl( base, power );
}

float
Math_toPower_float( float base, float power )
{
	return powf( base, power );
}

