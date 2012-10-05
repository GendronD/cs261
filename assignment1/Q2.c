/* CS261- Assignment 1 - Q.2*/
/* Name: Jordan Bayles
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){

    /*Set a to double its original value*/
    *a *= 2;

    /*Set b to half its original value*/
    *b /= 2;

    /*Assign a+b to c*/
    c = *a + *b;

    /*Return c*/
    return( c );
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    int foo_return;

    /*Print the values of x, y and z*/
    printf( "%d %d %d\n", x, y, z );

    /*Call foo() appropriately, passing x,y,z as parameters*/
    foo_return = foo( &x, &y, z );

    /*Print the value returned by foo*/
    printf( "%d\n", foo_return );

    /*Print the values of x, y and z again*/
    printf( "%d %d %d\n", x, y, z );

    /*Is the return value different than the value of z?  Why?*/
    /* Yes there is: as z's value is passed, not a pointer to z,
       after foo() does operations upon the value of z, its value
       in main() is not changed from before the function call */
    return 0;
}
