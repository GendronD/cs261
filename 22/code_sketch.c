
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
}

/* The following functions were written in earlier lessons */
void linkedListInit( struct linkedList *lst );
void linkedListFree( struct linkedList *lst );
void _addLink( struct linkedList *lst, struct dlink *lnk, TYPE e);
void _removeLink( struct linkedList *lst, struct dlink *lnk );

void linkedListAdd( struct linkedList *lst, TYPE e )
{
    _addLink( lst, lst->frontSentinel->nest, e );
}

int linkedListContains( struct linkedList *lst, TYPE e )
{

}

int linkedListRemove( struct linkedList *lst, TYPE e )
{

}
