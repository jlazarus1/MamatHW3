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

    res->opType=NULL;
    res->type=OPERAND;
    res->key=NULL;
    switch (op -> opType)
    {
        case ('ADD') :
            res->val = left->val + right->val;
            break;
        case ('SUB') :
            res->val = left->val - right->val;
            break;
        case ('MUL') :
            res->val = left->val * right->val;
            break;
        case ('DIV') :
            res->val = left->val / right->val;
            break;
        default      :
            return (NULL);
    }
    return res;
}

char* GetKeyF (pCalcElement elem)
{
    return (elem->key);
}

Bool CompareKeyF (const char* key1 , const char* key2)
{
    if (strcmp(key1,key2) == 0)
    {
        return TRUE;
    }
    return FALSE;
}
/*------------------------------------------------------------------------------*/
// Side functions:

// creating the element in the math tree:
void create_element (pCalcElement elem , char* str)
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
            elem->val = atof(*str);
            elem->key = NULL;
            break;

        default :
            elem->type = SYMBOL;
            strcpy(elem->key , str);
            break;
    }

}

// Adding left branch in expression tree:
Result addleft (char* exp , pNode pN)
{

}

/*------------------------------------------------------------------------------*/
// Expression functions:

// Build the math expression tree
Result InitExpression( char* exp )
{
    char* math = exp;
    char* tok = strtok_r( math, " " , &math);
    if (tok == NULL) return FAILURE;

    pCalcElement e = (pCalcElement)malloc(sizeof(CalcElement));//TODO remember to free
    if (e == NULL) return FAILURE;

    create_element(e , tok);
    pNode pN;

    if (pTG != NULL) TreeDestroy(pTG);

    pTG = TreeCreate(CloneF , DelF , OperateF,
               GetKeyF , CompareKeyF);

    pN = TreeAddRoot(pTG, e);

    if (e->type != OPERATOR) // if the tree is only one number then finish
    {
        return SUCCESS;
    }

    addleft(math , pN);
    addright(math , pN);
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
    e->opType = NULL;
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