/* CS261- Assignment 1 - Q. 0*/
/* Name: Jordan Bayles
 * Date:
 * Solution description: The values of an integer variable's address and contents
 * are shown using the "printf" function with void (%p) and integer (%d) print
 * formats with combinations of * (dereference) and & (address of) operators.
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr)
{

    /*Print the value pointed to by iptr*/
    printf( "%d\n", *iptr );

     /*Print the address pointed to by iptr*/
    printf( "%p\n", iptr );

    /*Print the address of iptr itself*/
    printf( "%p\n", &iptr );
}

int main()
{

    /*declare an integer x*/
    int x;

    /*print the address of x*/
    printf( "%p\n", &x );

    /*Call fooA() with the address of x*/
    fooA( &x );

    /*print the value of x*/
    printf( "%d\n", x );

    return 0;
}
