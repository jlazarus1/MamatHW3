#include <stdlib.h>
#include <assert.h>

#include <string.h>
#include "polishCalc.h"
#include "polishCalcTypes.h"
#include "expTree.h"


// Defines:
typedef CalcElement* pCalcElement;

// Global variable
pTree pTG = NULL;

// Functions implementation :

Result addleft (pNode pN);
Result addright (pNode pN);

// Tree functions:

pCalcElement CloneF (pCalcElement e)
{
    pCalcElement newE;
    newE = (pCalcElement)malloc(sizeof(CalcElement));
    if (newE == NULL) return NULL;
    newE -> type = e -> type;
    newE -> key = e -> key;
    newE -> opType = e -> opType;
    newE -> val = e -> val;
    return newE;
}

void DelF (pCalcElement e)
{
    free(e);
}

pCalcElement OperateF (pCalcElement op , pCalcElement left , pCalcElement right)
{
    pCalcElement res;
    res = (pCalcElement)malloc(sizeof(CalcElement));
    if (res == NULL) return NULL;

    res->type=OPERAND;
    switch (op -> opType)
    {
        case (ADD) :
            res->val = left->val + right->val;
            break;
        case (SUB) :
            res->val = left->val - right->val;
            break;
        case (MUL) :
            res->val = left->val * right->val;
            break;
        case (DIV) :
            res->val = left->val / right->val;
            break;
        default      :
            return (NULL);
    }
    return res;
}

char* GetKeyF (pCalcElement elem)
{
    char* tmp = elem->key;
    int val = elem->val;
    return (elem->key);
}

Bool CompareKeyF (const char* key1 , const char* key2)
{
    if (key2 == NULL) return FALSE;
    if (strcmp(key1,key2) == 0)
    {
        return TRUE;
    }
    return FALSE;
}
/*------------------------------------------------------------------------------*/
// Side functions:

// creating the element in the math tree:
void create_element (pCalcElement elem , const char* str)
{
    switch (*str)
    {
        case '+' :
            elem->type = OPERATOR;
            elem->opType = ADD;
            elem->key = NULL;
            break;
        case '-' :
            elem->type = OPERATOR;
            elem->opType = SUB;
            elem->key = NULL;
            break;
        case '*' :
            elem->type = OPERATOR;
            elem->opType = MUL;
            elem->key = NULL;
            break;
        case '/' :
            elem->type = OPERATOR;
            elem->opType = DIV;
            elem->key = NULL;
            break;

        case '0' :
        case '1' :
        case '2' :
        case '3' :
        case '4' :
        case '5' :
        case '6' :
        case '7' :
        case '8' :
        case '9' :
            elem->type = OPERAND;
            elem->val = atof(str);
            elem->key = NULL;
            break;

        default :
            elem->type = SYMBOL;
            int len = strlen(str);
            elem->key = (char*)malloc(sizeof(char)*len);
            strcpy(elem->key , str);
            elem->val = 0;
            break;
    }

}

// Adding left branch in expression tree:
Result addleft (pNode pN)
{
    char* tok = strtok(NULL , " ");
    if (tok == NULL) return SUCCESS;

    pCalcElement e = (pCalcElement)malloc(sizeof(CalcElement));
    if (e == NULL) return FAILURE;
    create_element(e , tok);

    pNode left = TreeAddLeftChild(pTG , pN , e);
    if (e->type != OPERATOR) // if the tree is only one number then finish
    {
        return SUCCESS;
    }
    else
    {
        if(addleft(left) == FAILURE) return FAILURE;
        if(addright(left) == FAILURE) return FAILURE;
    }
}


// Adding right branch in expression tree:
Result addright (pNode pN)
{
    char* tok = strtok(NULL , " ");
    if (tok == NULL) return SUCCESS;

    pCalcElement e = (pCalcElement)malloc(sizeof(CalcElement));
    if (e == NULL) return FAILURE;
    create_element(e , tok);

    pNode right = TreeAddRightChild(pTG , pN , e);
    if (e->type != OPERATOR) // recursive operation stops on Symbol or Operands
    {
        return SUCCESS;
    }
    else
    {
        if(addleft(right) == FAILURE) return FAILURE;
        if(addright(right) == FAILURE) return FAILURE;
    }
}

/*------------------------------------------------------------------------------*/
// Expression functions:

// Build the math expression tree
Result InitExpression( char* exp )
{
    char* tok = strtok( exp , " " );
    if (tok == NULL) return FAILURE;

    pCalcElement e = (pCalcElement)malloc(sizeof(CalcElement));
    if (e == NULL) return FAILURE;

    create_element(e , tok);
    pNode pN;

    //if (pTG != NULL) TreeDestroy(pTG);

    pTG = TreeCreate(*CloneF , *DelF , *OperateF,
               *GetKeyF , *CompareKeyF);

    pN = TreeAddRoot(pTG, e);

    if (e->type != OPERATOR) // if the tree is only one number then finish
    {
        return SUCCESS;
    }
    else
    {
        if(addleft(pN) == FAILURE) return FAILURE;
        if(addright(pN) == FAILURE) return FAILURE;
    }
    return SUCCESS;
}


// set symbols in the expression tree
Result SetSymbolVal( char* symName, float val )
{
    pCalcElement e;

    e = TreeFindElement(pTG , symName);

    if (e == NULL) return FAILURE;

    e->key = NULL;
    e->val = val;
    e->type = OPERAND;
    return SUCCESS;
}


// Evaluate the expression in the tree
Result EvaluateExpression( float *res )
{
    pCalcElement sol;

    sol = TreeEvaluate(pTG);
    if (sol == NULL) return FAILURE;

    *res = sol->val;

    return SUCCESS;
}

// Delete expression tree
void DeleteExpression()
{
    TreeDestroy(pTG);
}