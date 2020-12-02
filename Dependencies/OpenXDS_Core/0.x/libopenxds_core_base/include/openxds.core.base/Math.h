#ifndef OPENXDS_CORE_BASE_MATH_H
#define OPENXDS_CORE_BASE_MATH_H

#include "openxds.core.h"

EXPORT	long        Math_constrainBetween( long aNumber, long lower, long upper );
EXPORT	bool        Math_isAlmostEqual( double a, double b );
EXPORT	bool        Math_isBetween( long aNumber, long lower, long upper );
EXPORT	double      Math_floor( double aValue );
EXPORT	long        Math_max( long a, long b );
EXPORT	long        Math_min( long a, long b );
EXPORT	double      Math_pi(void);
EXPORT	long        Math_sizeOfRange( double first, double last, double increment );
EXPORT	double      Math_squareroot( double aValue );
EXPORT	double      Math_toPower( double base, double power );
EXPORT	long double Math_toPower_long_double( long double base, long double power );
EXPORT	float       Math_toPower_float( float base, float power );

#endif

