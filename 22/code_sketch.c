#include <stdlib.h>
#include <assert.h>

#define TYPE int

struct dlink
{
    TYPE value;
    struct dlink *next;
    struct dlink *prev;
};

struct linkedList
{
    struct dlink *frontSentinel;
    struct dlink *backSentinel;
    int size;
};

/* The following functions were written in earlier lessons */
void linkedListInit( struct linkedList *lst );
void linkedListFree( struct linkedList *lst );
void _addLink( struct linkedList *lst, struct dlink *lnk, TYPE e);
void _removeLink( struct linkedList *lst, struct dlink *lnk );

void linkedListAdd( struct linkedList *lst, TYPE e )
{
    _addLink( lst, lst->frontSentinel->next, e );
}

int linkedListContains( struct linkedList *lst, TYPE e )
{
assert( lst != NULL );
struct dlink *tmp_lnk = lst->frontSentinel;

while( tmp_lnk->next != NULL )
    {
    if( tmp_lnk->value == e )
        {
        return( 1 );
        }
    tmp_lnk = tmp_lnk->next;
    }
return( 0 );

}

int linkedListRemove( struct linkedList *lst, TYPE e )
{
assert( lst != NULL );
struct dlink *tmp_lnk = lst->frontSentinel;

while( tmp_lnk->next != NULL )
    {
    /* We have found the link to remove */
    if( tmp_lnk->value == e )
        {
        _removeLink( lst, tmp_lnk );
        }
    tmp_lnk = tmp_lnk->next;
    }
return( 0 );

}
