/* CS261- Assignment 1 - Q.4*/
/* Name: Jordan Bayles
 * Date: Fri Oct  5 15:51:15 PDT 2012
 * Solution description: Students are allocated, filled,
   and then sorted through the use of a heap sort, similar
   to previous question Q3.
 */
 
#include <stdio.h>
#include <stdlib.h>

#define MAX_SCORE 100
#define NUM_STUDENTS 20

struct student
{
    int id;
    int score;
};

/*
   Function: sort() sorts a pre-filled struct array of students in ascending order.
   Pre-cond: students should be allocated and filled with generated data.
   Pst-cond: students is sorted by test score in ascending order.
*/
void sort(struct student* students, int n)
{
    /*Sort the n students based on their score*/
    struct student tmp_student;
    int minimum;
    int minimum_idx;

    for( int i = 0; i < n; ++i )
        {
        minimum = students[ i ].score;
        minimum_idx = i;

        for( int j = i; j < n; ++j )
            {
                /* Check for new minimum */
                if( students[ j ].score < minimum )
                    {
                    minimum = students[ j ].score;
                    minimum_idx = j;
                    }
            }

        /* Only swap if indices are different */
        if( i != minimum_idx )
            {
            /* Swap values of current minimum with new one */
            tmp_student = students[ minimum_idx ];
            students[ minimum_idx ] = students[ i ];
            students[ i ] = tmp_student;
            }
        }
}

/*
   Function: generate() fills a passed in struct array with valid data.
   Pre-cond: Students must be allocated.
   Pst-cond: Students struct array is filled with valid data.
*/
void generate(struct student* students, int n)
{
    /* method here: select numbers 1 - n, and use rand to shuffle them. */
    int *ids = (int *)malloc( n * sizeof( int ) );
    int new_slot;
    int temp_id;

    /* put initial values into ids */
    for( int i = 0; i < n; ++i )
        {
        /* Offset by one, as IDs start at 1 but array at 0 */
        ids[ i ] = i + 1;
        }

    /* use rand() to shuffle the numbers */
    for( int i = 0; i < n; ++i )
        {
        /* Get the new position of this slot */
        new_slot = rand() % n;

        /* Swap the value in new_slot with the current slot i */
        temp_id = ids[ new_slot ];
        ids[ new_slot ] = ids[ i ];
        ids[ i ] = temp_id;
        }

    /* Assign IDs, scores */
    for( int i = 0; i < n; ++i )
        {
        students[ i ].id = ids[ i ];
        students[ i ].score = rand() % MAX_SCORE;
        }
}

/*
   Function: print_students() prints the id, score of all students.
   Pre-cond: students must be allocated with valid size n.
   Pst-cond: none. Data is piped through stdout.
*/
void print_students( struct student* students, int n )
{
    for( int i = 0; i < n; ++i )
        {
        printf( "%d\t%d\n", students[ i ].id, students[ i ].score );
        }
}

/*
   Function: main() declares a student struct array of size n, sorts it,
             and displays its values before and after sorting
   Pre-cond: none.
   Pst-cond: none.
*/
int main()
{
    /*Declare an integer n and assign it a value.*/
    int n = NUM_STUDENTS;

    /*Allocate memory for n students using malloc.*/
    struct student *students = (struct student *)malloc( n * sizeof( struct student ) );

    /*Generate random IDs and scores for the n students, using rand().*/
    generate( students, n );

    /*Print the contents of the array of n students.*/
    printf( "Before sorting:\nID\tScore\n" );
    print_students( students, n );

    /*Pass this array along with n to the sort() function*/
    sort( students, n );

    /*Print the contents of the array of n students.*/
    printf( "After sorting:\nID\tScore\n" );
    print_students( students, n );

    return 0;
}
