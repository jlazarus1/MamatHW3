#ifndef POLISH_CALC_H
#define POLISH_CALC_H

#include "defs.h"

/* Initialization expression */
Result InitExpression( char* exp );

/* Set symbol value */
Result SetSymbolVal( char* symName, float val );

/* Evaluate expression */
Result EvaluateExpression( float *res );

/* Destroy expression */
void DeleteExpression();

#endif	// POLISH_CALC_H

