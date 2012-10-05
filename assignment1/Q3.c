/* CS261- Assignment 1 - Q.3*/
/* Name: Jordan Bayles
 * Date:
 * Solution description: After previous experience with
   sorting algorithms, I decided to try a heap sort due
   to (1) the fact it can be used in place on an array,
   and (2) it is reasonably fast.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 20
/* Set a cap on max number (for human readability) */
#define MAX_NUMBER 100

/*
   Function: sort() takes an array of numbers and its size,
             sorts it into ascending order.
   Pre-cond: number must be allocated, filled with values.
   Pst-cond: number is sorted by value.
*/
void sort(int* number, int n)
{
    int tmp_number;
    int minimum;
    int minimum_idx;

     /*Sort the given array number , of length n*/
    for( int i = 0; i < n; ++i )
        {
        minimum = number[ i ];
        minimum_idx = i;

        /* Go through remaining subset of array */
        for( int j = i; j < n; ++j )
            {
                if( number[ j ] < minimum )
                    {
                    minimum = number[ j ];
                    minimum_idx = j;
                    }
            }
        /* Don't swap if indices are the same */
        if( i != minimum_idx )
            {
            /* Swap the values stored at both indices */
            tmp_number = number[ minimum_idx ];
            number[ minimum_idx ] = number[ i ];
            number[ i ] = tmp_number;
            }
        }
}

/*
   Function: Main allocates, calls to fill, sorts, and prints
             the values of an array of numbers before and
             after sorting is completed.
   Pre-cond: none.
   Pst-cond: none.
*/
int main()
{
    /*Declare an integer n and assign it a value of 20.*/
    int n = ARRAY_SIZE;

    /*Allocate memory for an array of n integers using malloc.*/
    int *array = (int *)malloc( n * sizeof( int ) );

    /*Fill this array with random numbers, using rand().*/
    srand( time( NULL ) );
    for( int i = 0; i < n; ++i )
        {
        array[ i ] = rand() % MAX_NUMBER;
        }

    /*Print the contents of the array.*/
    printf( "Before sorting:\n{ " );
    for( int i = 0; i < n; ++i )
        {
        printf( "%d ", array[ i ] );
        }
    printf( "}\n" );

    /*Pass this array along with n to the sort() function of part a.*/
    sort( array, n );

    /*Print the contents of the array.*/
    printf( "After sorting:\n{ " );
    for( int i = 0; i < n; ++i )
        {
        printf( "%d ", array[ i ] );
        }
    printf( "}\n" );

    return 0;
}
