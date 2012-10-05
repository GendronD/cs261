/* CS261- Assignment 1 - Q. 0*/
/* Name: Jordan Bayles
 * Date: Fri Oct  5 15:50:26 PDT 2012
 * Solution description: The values of an integer variable's address and contents
 * are shown using the "printf" function with void (%p) and integer (%d) print
 * formats with combinations of * (dereference) and & (address of) operators.
 */

#include <stdio.h>
#include <stdlib.h>

/*
   Function: fooA takes a pointer to an integer and prints related information.
   Pre-cond: As the pointer is dereferenced, it should be passed in as a pointer
             to an already allocated section of memory, otherwise a null pointer
             dereference error will occur.
   Pst-cond: no modification is done to any variables. Information is sent
             through stdout to the terminal.
*/
void fooA(int* iptr)
{
    /*Print the value pointed to by iptr*/
    printf( "%d\n", *iptr );

     /*Print the address pointed to by iptr*/
    printf( "%p\n", iptr );

    /*Print the address of iptr itself*/
    printf( "%p\n", &iptr );
}

/*
   Function: Main instantiates an integer variable, prints its address and value,
             and calls a helper function fooA.
   Pre-cond: None.
   Pst-cond: Nothing modified. Information sent through stdout to terminal.
*/
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
