#include <stdlib.h>
#include <assert.h>

#include "defs.h"
#include "expTree.h"
//comment
/* definition of a node in the tree */
typedef struct _node
{
	pElement	elem;

	pNode		leftChild;
	pNode		rightChild;
} Node;

/* definition of the tree structure */   
typedef struct _tree
{
	pNode root;
	int iNum 		/*we might need it for recursivly going through all the elements in the tree */

	/*function pointers*/
	CLONE		CloneFunction;
	DEL_ELEMENT	DelFunction;
	OPERATE		OperateFunction;
	GET_KEY		GetKeyFunction;
	COMPARE_KEYS	CompareKeyFunction;
	
} Tree;

/* *** complete the interface functions implementation *** */

