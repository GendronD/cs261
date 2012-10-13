/* CS261- Assignment 1 - Q.5*/
/* Name: Jordan Bayles
 * Date: Fri Oct  5 15:51:26 PDT 2012
 * Solution description: A toggle is used to determine
   if the current char *should* be upper or lower case,
   its current case is evaluated and then, if it differs
   from what it should be, is set to the proper case.
   Although it is set to alternate AbCd..., any length
   of alteration, e.g. ABCDefghIJKLmnop... is possible.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_SIZE 80
/*
 * The frequency at which to convert from lower case to upper case letters.
 * ALT_FREQ = 1 implies AbCdEfG, ALT_FREQ = 2 implies ABcdEFg, etc.
 */
#define ALT_FREQ 1

/*
   Function: converts ch to upper case, assuming it is in lower case currently
   Pre-cond: ch must be in lower case.
   Pst-cond: ch is in upper case.
*/
char toUpperCase(char ch)
{
     return ch-'a'+'A';
}

/*
   Function: converts ch to lower case, assuming it is in upper case currently
   Pre-cond: ch must be in upper case.
   Pst-cond: ch is in lower case.
*/
char toLowerCase(char ch)
{
     return ch-'A'+'a';
}

/*
   Function: sticky() converts any valid character string into sticky caps.
   Pre-cond: word must be allocated and null terminated.
   Pst-cond: word is in sticky caps.
*/
void sticky(char* word)
{
    int idx = 0;
    int toggle_low_high = 0;

    while( word[ idx ] != '\0' )
        {
        /* Time to toggle capitalization status */
        if( ( idx % ALT_FREQ ) == 0 )
            {
            toggle_low_high = !toggle_low_high;
            }

        if( toggle_low_high )
            {
            if( islower( word[ idx ] ) )
                {
                word[ idx ] = toUpperCase( word[ idx ] );
                }
            }
        else
            {
            if( isupper( word[ idx ] ) )
                {
                word[ idx ] = toLowerCase( word[ idx ] );
                }
            }

        ++idx;
        }
}

/*
   Function: Main allocates/frees variable user_input, gets
             a word from the user of the program through scanf,
             and calls sticky() to convert to sticky caps.
   Pre-cond: none.
   Pst-cond: none.
*/
int main()
{
    char *user_input = (char *)malloc( MAX_WORD_SIZE * sizeof( char ) );

    /*Read word from the keyboard using scanf*/
    scanf( "%s", user_input );

    /*Call sticky*/
    sticky( user_input );

    /*Print the new word*/
    printf( "%s", user_input );

    free( user_input );
    return 0;
}
