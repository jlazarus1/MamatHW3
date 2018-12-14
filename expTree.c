#include <stdlib.h>
#include <assert.h>

#include "defs.h"
#include "expTree.h"

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

	/* *** complete the definition of the tree structure *** */
} Tree;

/* *** complete the interface functions implementation *** */

