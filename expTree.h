#ifndef EXP_TREE_H
#define EXP_TREE_H

#include "defs.h"

/*typdefs of the structs and pointers */

typedef struct _node *pNode;
typedef struct _tree *pTree;

typedef void* pElement;
typedef void* pKey;


/*function types*/
typedef pElement	(*CloneFunction)(pElement e);
typedef void		(*DelFunction)(pElement e);
typedef pElement	(*OperateFunction)(pElement op, 
									   pElement left, 
									   pElement right);
typedef pKey		(*GetKeyFunction)(pElement elem);
typedef Bool		(*CompareKeyFunction)(const pKey key1, 
										  const pKey key2);


/* Interface functions */

pTree		TreeCreate(CloneFunction,DelFunction,OperateFunction,
		GetKeyFunction,CompareKeyFunction);

void		TreeDestroy(pTree);

pNode		TreeAddRoot(pTree,pElement);

pNode		TreeAddLeftChild(pTree,pNode,pElement);

pNode		TreeAddRightChild(pTree,pNode, pElement);

pElement	TreeFindElement(pTree,pKey);

pElement	TreeEvaluate(pTree);


#endif	// EXP_TREE_H
