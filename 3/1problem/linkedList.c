#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* Double Link*/
struct DLink
{
    TYPE value;
    struct DLink * next;
    struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */
struct linkedList
{
    int size;
    struct DLink *firstLink;
    struct DLink *lastLink;
};

/*
    initList
    param lst the linkedList
    pre: lst is not null
    post: lst size is 0
*/
void _initList( struct linkedList *lst ) {
    assert( lst != NULL );
    struct DLink *first = malloc(sizeof(struct DLink));
    struct DLink *last = malloc(sizeof(struct DLink));

    /* Initialize the sentinels */
    first->value = 0;
    first->next = last;
    first->prev = NULL;

    last->value = 0;
    last->next = NULL;
    last->prev = first;

    /* List already malloc'ed, so just assign */
    lst->size = 2;
    lst->firstLink = first;
    lst->lastLink = last;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */
struct linkedList *createLinkedList()
{
    struct linkedList *newList = malloc(sizeof(struct linkedList));
    _initList(newList);
    return(newList);
}

/*
    _addLinkBeforeBefore
    param: lst the linkedList
    param: l the  link to add before
    param: v the value to add
    pre: lst is not null
    pre: l is not null
    post: lst is not empty
*/
void _addLinkBefore( struct linkedList *lst, struct DLink *l, TYPE v )
{
    assert( ( lst != NULL ) && ( l != NULL ) );
    struct DLink *newLink = malloc(sizeof(struct DLink));

    /* Assign values for the new link */
    newLink->value = v;
    newLink->next = l;
    newLink->prev = l->prev;

    /* Assign values for surrounding links */
    l->prev->next = newLink;
    l->prev = newLink;

}


/*
    addFrontList
    param: lst the linkedList
    param: e the element to be added
    pre: lst is not null
    post: lst is not empty, increased size by 1
*/
void addFrontList( struct linkedList *lst, TYPE e )
{
    assert( lst != NULL );
    /* Add link at the beginning by adding before first value link */
    _addLinkBefore( lst, lst->firstLink->next, e );
}

/*
    addBackList
    param: lst the linkedList
    pre: lst is not null
    post: lst is not empty
*/
void addBackList( struct linkedList *lst, TYPE e )
{
    assert( lst != NULL );
    /* Add link at the beginning by adding before last link */
    _addLinkBefore( lst, lst->lastLink, e );
}

/*
    frontList
    param: lst the linkedList
    pre: lst is not null
    pre: lst is not empty
    post: none
*/
TYPE frontList( struct linkedList *lst )
{
    assert( ( lst != NULL ) && ( lst->size > 0 ) );

    return( lst->firstLink->next->value );
}

/*
    backList
    param: lst the linkedList
    pre: lst is not null
    pre: lst is not empty
    post: lst is not empty
*/
TYPE backList( struct linkedList *lst )
{
    assert( ( lst != NULL ) && ( lst->size > 0 ) );

    return( lst->lastLink->prev->value );
}

/*
    _removeLink
    param: lst the linkedList
    param: l the link to be removed
    pre: lst is not null
    pre: l is not null
    post: lst size is reduced by 1
*/
void _removeLink( struct linkedList *lst, struct DLink *l )
{
    assert( ( lst != NULL ) && ( l != NULL ) );

    /* Change links around l */
    l->prev->next = l->next;
    l->next->prev = l->prev;

    /* Delete l */
    free( l );

    /* Let list know it is smaller */
    lst->size -= 1;
}

/*
    removeFrontList
    param: lst the linkedList
    pre:lst is not null
    pre: lst is not empty
    post: size is reduced by 1
*/
void removeFrontList( struct linkedList *lst )
{
    assert( ( lst != NULL ) && ( lst->size > 0 ) );
    _removeLink( lst, lst->firstLink->next );
}

/*
    removeBackList
    param: lst the linkedList
    pre: lst is not null
    pre:lst is not empty
    post: size reduced by 1
*/
void removeBackList( struct linkedList *lst )
{
    assert( ( lst != NULL ) && ( lst->size > 0 ) );
    _removeLink( lst, lst->lastLink->prev );
}

/*
    isEmptyList
    param: lst the linkedList
    pre: lst is not null
    post: none
*/
int isEmptyList( struct linkedList *lst )
{
    assert( lst != NULL );

    return( lst->size == 0 );
}


/* Function to print list
 Pre: lst is not null
 */
void _printList( struct linkedList* lst )
{
    struct DLink *tmp_lnk = lst->firstLink;
    assert( lst != NULL );

    printf( "Link ptr | value\n" );
    while( tmp_lnk != lst->lastLink )
        {
        /* This line will need to be replaced for some data type changes */
        printf( "%p\t%d\n ", tmp_lnk, tmp_lnk->value );
        tmp_lnk = tmp_lnk->next;
        }
}

/* Iterative implementation of add()
 Pre: lst is not null
 */
void addList( struct linkedList *lst, TYPE v )
{
    assert( lst != NULL );

    /* As we are adding to a bag, the position is arbitrary */
    _addLinkBefore( lst, lst->firstLink->next, v );
}

/* Iterative implementation of contains()
 Pre: lst is not null
 pre: lst is not empty
 */
int containsList( struct linkedList *lst, TYPE e )
{
    assert( ( lst != NULL ) && ( lst->size != 0 ) );

    /* Skip the sentinel and advance to the first nonzero value link */
    struct DLink *tmp_lnk = lst->firstLink->next;

    while( tmp_lnk != lst->lastLink )
        {
        if( tmp_lnk->value == e )
            {
            return( 1 );
            }
        tmp_lnk = tmp_lnk->next;
        }

    return( 0 );
}

/* Iterative implementation of remove()
 Pre: lst is not null
 pre: lst is not empty
 */
void removeList( struct linkedList *lst, TYPE e )
{
    assert( ( lst != NULL ) && ( lst->size != 0 ) );

    /* Skip the sentinel and advance to the first nonzero value link */
    struct DLink *tmp_lnk = lst->firstLink->next;

    while( tmp_lnk != lst->lastLink )
        {
        if( tmp_lnk-> value == e )
            {
            _removeLink( lst, tmp_lnk );
            }
        tmp_lnk = tmp_lnk->next;
        }
}
