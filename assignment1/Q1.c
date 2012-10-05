/* CS261- Assignment 1 - Q.1*/
/* Name: Jordan Bayles
 * Date:
 * Solution description:
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_STUDENTS 10
#define MAX_SCORE 100

struct student
{
    int id;
    int score;
};

struct student* allocate()
{
    /*Allocate memory for ten students*/
    struct student *mem_students = (struct student *)malloc(
                                                       10 * sizeof( struct student ) );
    /*return the pointer*/
    return mem_students;
}


void generate(struct student* students)
{
    /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    /* method here: select numbers 1 - 10, and use rand to shuffle them. */
    int ids[ NUM_STUDENTS ];
    int new_slot;
    int temp_id;

    /* put initial values into ids */
    for( int i = 0; i < NUM_STUDENTS; ++i )
        {
        /* Offset by one, as IDs start at 1 but array at 0 */
        ids[ i ] = i + 1;
        }

    /* use rand() to shuffle the numbers */
    for( int i = 0; i < NUM_STUDENTS; ++i )
        {
        /* Get the new position of this slot */
        new_slot = rand() % NUM_STUDENTS;

        /* Swap the value in new_slot with the current slot i */
        temp_id = ids[ new_slot ];
        ids[ new_slot ] = ids[ i ];
        ids[ i ] = temp_id;
        }

    /* Assign IDs, scores */
    for( int i = 0; i < NUM_STUDENTS; ++i )
        {
        students[ i ].id = ids[ i ];
        students[ i ].score = rand() % MAX_SCORE;
        }
}

void output(struct student* students)
{
    /*Output information about the ten students in the format:
             ID1 Score1
             ID2 score2
             ID3 score3
             ...
             ID10 score10*/
    for( int i = 0; i < NUM_STUDENTS; ++i )
        {
        printf( "%d %d\n", students[ i ].id, students[ i ].score );
        }
}

void summary(struct student* students)
{
    /*Compute and print the minimum, maximum and average scores of the ten students*/
    /*Set minimum and maximum values to worst case score*/
    int min = MAX_SCORE;
    int max = 0;
    int average = 0;

    for( int i = 0; i < NUM_STUDENTS; ++i )
        {
        if( students[ i ].score < min )
            {
            min = students[ i ].score;
            }
        else if( students[ i ].score > max )
            {
            max = students[ i ].score;
            }
        average += students[ i ].score;
        }

    average = average / NUM_STUDENTS;
    printf( "min: %d, max: %d, average: %d\n", min, max, average );
}

void deallocate(struct student* stud)
{
    /*Deallocate memory from stud*/
    free( stud );
}

int main()
{
    struct student* stud = NULL;

    /* seed random function (should only be done 1x per program, so in main) */
    srand( time( NULL ) );

    /*call allocate*/
    stud = allocate();

    /*call generate*/
    generate( stud );

    /*call output*/
    output( stud );

    /*call summary*/
    summary( stud );

    /*call deallocate*/
    deallocate( stud );

    return 0;
}
