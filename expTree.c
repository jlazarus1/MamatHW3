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

// side functions to assist the task ones:

// Helps TreeDestroy to go recursively in the tree and delete all nodes
void release (pNode node , pTree pT)
{
    if (node -> leftChild != NULL)
    {
        release (node -> leftChild, pT);
    }
    if (node -> rightChild != NULL)
    {
        release (node -> rightChild, pT);
    }
    pT->DelFun(node->elem);
    free(node);
}

// Helps TreeFindElement going recursively to find key
pNode findkey (pTree pT , pNode pN , pKey pK)
{
    pNode pNtmp;
    if ((pT->ComparekeyFun(pK , pT->GetkeyFun(pN)))==TRUE) return pN;

    if (pN->leftChild != NULL)
    {
        if ((pNtmp = findkey(pT,pN->leftChild,pK)) != NULL) return pNtmp;
    }
    if (pN->rightChild != NULL)
    {
        if ((pNtmp = findkey(pT, pN->rightChild,pK)) != NULL) return pNtmp;
    }
    return NULL;
}

// Helps TreeEvaluate function by evaluate the tree's branches
pElement evaluate(pTree pT, pNode pN)
{
    if (pN->leftChild == NULL) return pN->elem;
    pElement value;
    value = pT->OperateFun(pN->elem, evaluate(pT, pN->leftChild), evaluate(pT, pN->rightChild));
    return value;
}

// Tree functions:

// TreeCreate gets all the functions needed from the user to create the Tree-Element

pTree TreeCreate (CloneFunction CloneFun , DelFunction DelFun , OperateFunction OperateFun,
                  GetKeyFunction Get_keyFun , CompareKeyFunction Compare_keysFun)
{
	pTree tree;
	tree = (pTree)malloc(sizeof(Tree));
	if (tree == NULL)
{
	    exit(1);
}
	tree -> root = NULL;
	tree -> CloneFun = CloneFun;
	tree -> DelFun = DelFun;
	tree -> OperateFun = OperateFun;
	tree -> GetkeyFun = Get_keyFun;
	tree -> ComparekeyFun = Compare_keysFun;
}

// TreeDestroy going through all nodes in the tree recursively and free their memory
void TreeDestroy (pTree pT)
{
    if (pT -> root -> leftChild != NULL)
    {
        release (pT -> root -> leftChild , pT);
    }
    if (pT -> root -> rightChild != NULL)
    {
        release (pT -> root -> rightChild , pT);
    }
    pT->DelFun(pT -> root -> elem);
    free(pT->root);
    free(pT);
}

// Create new node and add it as the root of the tree
pNode TreeAddRoot (pTree pT , pElement e)
{
    pElement eC = pT->CloneFun(e);
    pNode pN;
    pN = (pNode)malloc(sizeof(Node));
    if (pN == NULL)
    {
        return NULL;
    }
    pN->elem = eC;
    pN->leftChild = NULL;
    pN->rightChild = NULL;
    pT -> root = pN;
    return pN;
}

// Create new node and add it as a left child of the input node
pNode TreeAddLeftChild (pTree pT , pNode pN , pElement e)
{
    pElement eC = pT->CloneFun(e);
    pNode pLchild;
    pLchild = (pNode)malloc(sizeof(Node));
    if (pLchild == NULL)
    {
        return NULL;
    }
    pLchild->elem = eC;
    pLchild->rightChild = NULL;
    pLchild->leftChild = NULL;
    pN->leftChild = pLchild;
    return pLchild;
}

// Create new node and add it as a right child of the input node
pNode TreeAddRightChild (pTree pT , pNode pN , pElement e)
{
    pElement eC = pT->CloneFun(e);
    pNode pRchild;
    pRchild = (pNode)malloc(sizeof(Node));
    if (pRchild == NULL)
    {
        return NULL;
    }
    pRchild->elem = eC;
    pRchild->rightChild = NULL;
    pRchild->leftChild = NULL;
    pN->rightChild = pRchild;
    return pRchild;
}

// Go through the tree recursively and looks for the key wanted
pElement TreeFindElement (pTree pT , pKey pK)
{
    pNode pN = pT->root;
    if (pT->ComparekeyFun(pK , pT->GetkeyFun(pN))) return pN->elem;
    if (pN =findkey(pT , pN->leftChild , pK) != NULL) return pN->elem;
    if ((pN = findkey(pT , pN->rightChild , pK) != NULL) != NULL) return pN->elem;
    return NULL;
}

// Go recursively through the tree and calculate its value
pElement TreeEvaluate (pTree pT)
{
    pNode pN = pT->root;
    pElement value;
    if (pN->rightChild == NULL) return NULL;
    value = pT->OperateFun(pN->elem, evaluate(pT, pN->leftChild), evaluate(pT, pN->rightChild));
    return value;
}