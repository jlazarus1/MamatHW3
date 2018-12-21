#include <stdlib.h>
#include <assert.h>

#include <string.h>
#include "polishCalc.h"
#include "polishCalcTypes.h"
#include "expTree.h"


// Defines:
typedef CalcElement* pCalcElement;

int tree_exist = 0;
int root_exist = 0;
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


/*------------------------------------------------------------------------------*/
// Expression functions:

Result InitExpression( char* exp )
{
    char* tok = strtok( exp, " " );
    pCalcElement e = (pCalcElement)malloc(sizeof(CalcElement)); //TODO remember to free
    pTree pT;
    pNode pN;

    pT = TreeCreate(CloneF,DelF,OperateF, // TODO: add condition for deleting existing tree
               GetKeyF,CompareKeyF);

    while (tok != NULL)
    {
        create_element(e , tok);
        if (root_exist)
        {
            
        }
    }
}