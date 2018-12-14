#ifndef EXP_TREE_H
#define EXP_TREE_H

#include "defs.h"

/* complete the definition of the pointers to Tree and Node */

typedef void* pElement;
typedef void* pKey;

typedef pElement	(*CloneFunction)(pElement e);
typedef void		(*DelFunction)(pElement e);
typedef pElement	(*OperateFunction)(pElement op, 
									   pElement left, 
									   pElement right);
typedef pKey		(*GetKeyFunction)(pElement elem);
typedef Bool		(*CompareKeyFunction)(const pKey key1, 
										  const pKey key2);

/* complete the definition of the interface functions */

#endif	// EXP_TREE_H