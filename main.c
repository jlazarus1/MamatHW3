#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "polishCalc.h"
#include "expTree.h"

#define MAX_LINE_SIZE 255


int main()
{
	Result err = SUCCESS;
	char	stLine[MAX_LINE_SIZE];
	char*	tok = NULL;

	fgets( stLine, MAX_LINE_SIZE, stdin);
	
	while( !feof(stdin) )
	{
		tok = strtok( stLine, " " );

		if( 0 == strncmp( tok, "EXP", 3 ) )
		{
		    printf("enter EXP");
			tok = strtok( NULL, "\n" );

			err = InitExpression( tok );
			if( SUCCESS != err )
			{
				printf("Error while parsing expression\n");
				break;
			}
		}
		else if( 0 == strncmp( tok, "SET", 3 ) )
		{
            printf("enter SET");
			char* stName = strtok( NULL, " \n" );
			char* stVal = strtok( NULL, "\n" );

			float val = (float)atof( stVal );

			err = SetSymbolVal( stName, val );
			if( SUCCESS != err )
			{
				printf("Error while setting symbol val\n");
				break;
			}
		}
		else if( 0 == strncmp( tok, "EVALUATE", 8 ) )
		{
            printf("enter EVALUATE");
			float res = 0.f;

			err = EvaluateExpression( &res );
			if( SUCCESS != err )
			{
				printf("Error while evaluating expression\n");
				break;
			}

			printf( "RES %f\n", res );
		}
		else if( 0 == strncmp( tok, "EXIT", 4 ) )
		{
			break;
		}

		fgets( stLine, MAX_LINE_SIZE, stdin);
	}

	DeleteExpression();

	return 0;
}