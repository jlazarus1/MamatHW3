#ifndef POLISH_CALC_TYPES_H
#define POLISH_CALC_TYPES_H

typedef enum
{
	OPERATOR,
	OPERAND,
	SYMBOL
} CalcElementType;

typedef enum
{
	ADD,
	SUB,
	MUL,
	DIV
} CalcOperatorType;

typedef struct
{
	CalcElementType		type;

	// Every element has a key.
	// In some cases the key will be NULL
	char*				key;

	// For operators
	CalcOperatorType	opType;

	// For Operand and symbols
	float				val;

} CalcElement;

#endif	// POLISH_CALC_TYPES_H

