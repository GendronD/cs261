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
