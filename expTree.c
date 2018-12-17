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
	pKey key; 		/*we might need it for recursivly going through all the elements in the tree */

	/*function pointers*/
	CloneFunction		CloneFun;
	DelFunction			DelFun;
	OperateFunction		OperateFun;
	GetKeyFunction		GetkeyFun;
	CompareKeyFunction	ComparekeyFun;
	
} Tree;

/* *** complete the interface functions implementation *** */

/* functions implementation :
*/

// side functions to assist the tast ones:

void release (pNode node)
{
    if (node -> leftChild != NULL)
    {
        release (node -> leftChild);
    }
    if (node -> rightChild != NULL)
    {
        release (node -> rightChild);
    }
    free (node);
}

// Tree functions:

// TreeCreate gets all the functions needed from the user to create the Tree-Element

pTree TreeCreate (CloneFunction CloneFun , DelFunction DelFun , OperateFunction OperateFun ,
					 GetKeyFunction Get_keyFun , CompareKeyFunction Compare_keysFun);
{
	pTree tree;
	tree = (pTree)malloc(sizeof(Tree));
	if (tree == NULL)
{
	    exit(1);
}
	tree -> root = NULL;
	tree -> key =NULL;
	tree -> CloneFun = CloneFun;
	tree -> DelFun = DelFun;
	tree -> OperateFun = OperateFun;
	tree -> Get_keyFun = Get_keyFun;
	tree -> Compare_keysFun = Compare_keysFun;
}

// TreeDestroy going through all nodes in the tree recursively and free their memory
void TreeDestroy (pTree pT)
{
    if (pT -> root -> leftChild != NULL)
    {
        release (pT -> root -> leftChild);
    }
    if (pT -> root -> rightChild != NULL)
    {
        release (pT -> root -> rightChild);
    }
    free(pT -> root);
    free(pT);
}

//
pNode TreeAddRoot (pTree pT pElement e)
{
    pNode pN;
    pN = (pNode)malloc(sizeof(Node));
    if (pN == NULL)
    {
        return NULL;
    }
    pT -> root = pN;
    pT -> root -> elem = e;
    return pN;
}