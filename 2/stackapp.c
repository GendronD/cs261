/*
    Jordan Bayles       Sat Oct 13 02:23:03 PDT 2012
    No collaborators
    Assignment #2: Stacks and Parenthesis
    Developed in Arch Linux with the following workflow:
    vim -> make + gcc -> gdb + valgrind
*/

#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"

#define DEFAULT_CAPACITY 4

/****************************************************************
Using stack to check for unbalanced parentheses.
******************************************************************/

/* Returns the next character of the string, once reaches end return '0' (zero)
    param:     s pointer to a string
    pre: s is not null
*/
char nextChar(char* s)
{
    static int i = -1;
    char c;
    ++i;
    c = *(s+i);
    if ( c == '\0' )
        return '\0';
    else
        return c;
}

/* Checks whether the (), {}, and [] are balanced or not
    param:     s pointer to a string
    pre: s is not null
    post:
*/
int isBalanced(char* s)
{
    char c;
    int balanced = 1;
    DynArr *braces = createDynArr( DEFAULT_CAPACITY );

    /* Analysis of what it means to be balanced:
       In the simple case involving only parenthesis, determining if a string
       is balanced is simple, the number of '(' must match the number of ')'.
       However, with all three types of brackets the case of "mismatched scopes'
       needs to be considered. For this function, the following is assumed:
           ( { } ) : BALANCED
           { ( } ) : NOT BALANCED, even though the amount of (,{ and ),} balance.
           ( } { } : NOT BALANCED
    */
    do
        {
        c = nextChar( s );
        switch( c )
            {
            /* Push the element we want to find later, not what we have */
            case '(':
                pushDynArr( braces, ')' );
                break;
            case '{':
                pushDynArr( braces, '}' );
                break;
            case '[':
                pushDynArr( braces, ']' );
                break;

                /* Note deliberate fallthrough */
            case ')':
            case '}':
            case ']':
                /* If the top of the stack doesn't match, by our analysis
                   above for "balanced" definition, the string is unbalanced.
                   First check if empty, then check top to make sure its bal */
                if( !( isEmptyDynArr( braces ) )
                   &&( topDynArr( braces ) == c ) )
                    {
                    popDynArr( braces );
                    }
                else
                    {
                    /* Not balanced */
                    balanced = 0;
                    }
                break;
            default:
                /* Character is not a special character / bracket */
                break;
            }
        }
    while( ( c != '\0' ) && balanced );

    /* Stack should now be empty! */
    if( !isEmptyDynArr( braces ) )
        {
        balanced = 0;
        }

    deleteDynArr( braces );
    return( balanced );
}

int main(int argc, char* argv[]){

    char* s=argv[1];
    int res;

    printf("Assignment 2\n");
    /* Early escape for no input from user. This is done
       in main because "(null)" contains no characters
       and thus doesn't have a valid balanced status */
    if( s == NULL )
        {
        printf("No input detected.\n");
        }
    else
        {
        res = isBalanced(s);

        if (res)
            printf("The string %s is balanced\n",s);
        else
            printf("The string %s is not balanced\n",s);
        }

    return 0;
}

