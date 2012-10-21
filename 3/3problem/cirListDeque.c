#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

# define TYPE_SENTINEL_VALUE DBL_MAX

/* Double Link Structure */
struct DLink
{
    TYPE value;             /* value of the link */
    struct DLink * next;    /* pointer to the next link */
    struct DLink * prev;    /* pointer to the previous link */
};

struct cirListDeque
{
    int size;               /* number of links in the deque */
    struct DLink *Sentinel; /* pointer to the sentinel */
};

/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);

/* ************************************************************************
    Deque Functions
************************************************************************ */

/* Initialize deque.
    param:  q - pointer to the deque
    pre:    q is not null
    post:   q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque( struct cirListDeque *q )
{
    assert( q != NULL );
    q->Sentinel = malloc( sizeof( struct DLink ) );

    /* Circularly link; Sentinel should point to itself */
    q->Sentinel->prev = q->Sentinel->next = q->Sentinel;
    q->size = 0;
}

/* Create a new circular list deque
 */
struct cirListDeque* createCirListDeque( )
{
    struct cirListDeque *newCL = malloc( sizeof( struct cirListDeque ) );
    _initCirListDeque( newCL );
    return( newCL );
}


/* Create a link for a value.
    param:  val the value to create a link for
    pre:    none
    post:   a link to store the value
*/
struct DLink* _createLink( TYPE val )
{
    struct DLink *new_lnk = malloc( sizeof( struct DLink ) );
    new_lnk->value = val;
    return( new_lnk );
}

/* Adds a link after another link
    param: q - pointer to the deque
    param: lnk - pointer to the existing link in the deque
    param: newLnk - pointer to the new link to add after the existing link
    pre:   q is not null
    pre:   lnk and newLnk are not null
    post:  the new link is added into the deque after the existing link
*/
void _addLinkAfter( struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk )
{
    assert( ( q != NULL ) && ( lnk != NULL ) && ( newLnk != NULL ) );

    /* Update information about q itself */
    q->size += 1;

    /* Update pointers of new link */
    newLnk->next = lnk->next;
    newLnk->prev = lnk;

    /* Add new element points to surrounding elements*/
    lnk->next->prev = newLnk;
    lnk->next = newLnk;
}

/* Adds a link to the back of the deque
    param: q - pointer to the deque
    param: val - value for the link to be added
    pre:   q is not null
    post:  a link storing val is added to the back of the deque
*/
void addBackCirListDeque( struct cirListDeque *q, TYPE val )
{
    assert( q != NULL );

    /* Update information about q itself */
    q->size += 1;

    /* Create a new link with the value */
    struct DLink *newLnk = _createLink( val );

    /* Update pointers of new link */
    _addLinkAfter( q, q->Sentinel->prev, newLnk );
}

/* Adds a link to the front of the deque
    param: q - pointer to the deque
    param: val - value for the link to be added
    pre:   q is not null
    post:  a link storing val is added to the front of the deque
*/
void addFrontCirListDeque( struct cirListDeque *q, TYPE val )
{
    /* Update information about q itself */
    q->size += 1;

    /* Create a new link with the value */
    struct DLink *newLnk = _createLink( val );

    /* Update pointers of new link */
    _addLinkAfter( q, q->Sentinel, newLnk );
}

/* Get the value of the front of the deque
    param: q - pointer to the deque
    pre:   q is not null and q is not empty
    post:  none
    ret:   value of the front of the deque
*/
TYPE frontCirListDeque( struct cirListDeque *q )
{
    assert( ( q != NULL ) && ( q->size != 0 ) );
    return( q->Sentinel->next->value );
}

/* Get the value of the back of the deque
    param: q - pointer to the deque
    pre:   q is not null and q is not empty
    post:  none
    ret:   value of the back of the deque
*/
TYPE backCirListDeque( struct cirListDeque *q )
{
    assert( ( q != NULL ) && ( q->size != 0 ) );
    return( q->Sentinel->prev->value );
}

/* Remove a link from the deque
    param: q - pointer to the deque
    param: lnk - pointer to the link to be removed
    pre:   q is not null and q is not empty
    post:  the link is removed from the deque
*/
void _removeLink( struct cirListDeque *q, struct DLink *lnk )
{
    assert( ( q != NULL ) && ( q->size != 0 ) );

    /* Change information about q */
    q->size -= 1;

    /* Update surrounding links */
    lnk->next->prev = lnk->prev;
    lnk->prev->next = lnk->next;

    /* Free removed link */
    free( lnk );
}

/* Remove the front of the deque
    param: q - pointer to the deque
    pre:   q is not null and q is not empty
    post:  the front is removed from the deque
*/
void removeFrontCirListDeque( struct cirListDeque *q )
{
    assert( ( q != NULL ) && ( q->size != 0 ) );
    _removeLink( q, q->Sentinel->next );
}

/* Remove the back of the deque
    param: q - pointer to the deque
    pre:   q is not null and q is not empty
    post:  the back is removed from the deque
*/
void removeBackCirListDeque( struct cirListDeque *q )
{
    assert( ( q != NULL ) && ( q->size != 0 ) );
    _removeLink( q, q->Sentinel->prev );
}

/* De-allocate all links of the deque
    param: q - pointer to the deque
    pre:   none
    post:  All links (including Sentinel) are de-allocated
*/
void freeCirListDeque( struct cirListDeque *q )
{
    /* Only need to free list if we have one */
    if( q != NULL )
        {
        struct DLink *tmp_lnk;
        struct DLink *cur_lnk = q->Sentinel;

        /* Free links */
        if( cur_lnk != NULL )
            {
            do
                {
                /* Advance to next link and remove the current one */
                tmp_lnk = cur_lnk->next;
                free( cur_lnk );
                cur_lnk = tmp_lnk;
                }
            while( cur_lnk != q->Sentinel );
            }

        /* Free list itself */
        free( q );
        }
}

/* Check whether the deque is empty
    param: q - pointer to the deque
    pre:   q is not null
    ret:   1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque( struct cirListDeque *q )
{
    assert( q != NULL );

    return( q->size == 0 );
}

/* Print the links in the deque from front to back
    param: q - pointer to the deque
    pre:   q is not null and q is not empty
    post:  the links in the deque are printed from front to back
*/
void printCirListDeque( struct cirListDeque *q )
{
    assert( ( q != NULL ) && ( q->size != 0 ) );
    struct DLink *tmp_lnk = q->Sentinel->next;

    printf( "\nLink addr | value\n" );
    while( tmp_lnk != q->Sentinel )
        {
        printf( "%p\t%g\n", tmp_lnk, tmp_lnk->value );
        tmp_lnk = tmp_lnk->next;
        }
}

/* Reverse the deque
    param: q - pointer to the deque
    pre:   q is not null and q is not empty
    post:  the deque is reversed
*/
void reverseCirListDeque( struct cirListDeque *q )
{
    assert( ( q != NULL ) && ( q->size != 0 ) );

    struct DLink *cur_lnk = q->Sentinel->next;
    struct DLink *tmp_lnk = q->Sentinel->next;

    /* Swap Sentinel pointers */
    q->Sentinel->next = q->Sentinel->prev;
    q->Sentinel->prev = cur_lnk;

    while( cur_lnk != q->Sentinel )
        {
        /* Swap pointers around */
        tmp_lnk = cur_lnk->prev;
        cur_lnk->prev = cur_lnk->next;
        cur_lnk->next = tmp_lnk;

        /* Advance to next position */
        cur_lnk = cur_lnk->prev;
        }
}
