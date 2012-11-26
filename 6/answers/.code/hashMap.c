#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashMap.h"

/* Compare function for hash table entries. Limit added for safety,
 * set at longest word in accepted standard dictionaries
 */
#define compare( a, b ) strncmp( ( a ), ( b ), 45 )

/* Desc: Simple string hash, just sums ASCII value of string and returns
 * Pre:  str is not null
 * Post: Hash value of str is calculated
 */
int stringHash1(char * str)
{
    int i;
    int r = 0;
    for (i = 0; str[i] != '\0'; i++)
        r += str[i];
    return r;
}

/* Desc: More complex string hash, offsets ASCII value by position
 * Pre:  str is not null
 * Post: Shifted hash value of str is calculated
 */
int stringHash2(char * str)
{
    int i;
    int r = 0;
    for (i = 0; str[i] != '\0'; i++)
        r += (i+1) * str[i] * 2; /*the difference between 1 and 2 is on this line*/
    return r;
}

/* Desc: Initializes the supplied hashMap structure
 * Pre:  ht is not null (returns if so)
 * Post: ht is initialized to tableSize
 */
void initMap (struct hashMap * ht, int tableSize)
{
    int index;

    if(ht == NULL)
    {
        return;
    }
    ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
    ht->tableSize = tableSize;
    ht->count = 0;
    for(index = 0; index < tableSize; index++)
        ht->table[index] = NULL;
}

/* Desc: Free memory used for the hashMap, but not the pointer to it
 * Pre:  none
 * Post: ht's contents are freed
 */
void freeMap (struct hashMap * ht)
{
    /* free data */
    free( ht->table );
    /* Clear hash table data */
    ht->tableSize = 0;
    ht->count = 0;
}

/* Desc: Helper function for finding the index of a key
 * Pre:  ht is not null
 * Post: index of k returned
 */
int findKeyIndex( struct hashMap * ht, KeyType k )
{
    assert( ht != NULL );
    int key_index;

    /* Run the specified has function */
    if( HASHING_FUNCTION == 1 )
    {
        key_index = stringHash1( k );
    }
    else if( HASHING_FUNCTION == 2 )
    {
        key_index = stringHash2( k );
    }

    /* Reduce index to valid table index */
    key_index %= ht->tableSize;

    /* Ensure the index is positive */
    if( key_index < 0 )
    {
        key_index += ht->tableSize;
    }
    return( key_index );
}

/* Desc: Inserts key, value pair into the hash map
 * Pre:  ht is not null
 * Post: new link with key k and value v added
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{
    assert( ht != NULL );
    int idx = findKeyIndex( ht, k );

    /* Check if key is already in table */
    if( containsKey( ht, k ) )
    {
        /* Replace the hash link as it already exists */
        ht->table[ idx ]->value = v;
    }
    else
    {
        /* Not in table, so create a hashLink */
        struct hashLink *new_lnk = malloc( sizeof( struct hashLink ) );

        /* Fill hashLink with data */
        new_lnk->value = v;
        new_lnk->key = k;
        new_lnk->next = ht->table[ idx ];

        /* Add the new link to the table */
        ht->table[ idx ] = new_lnk;
        ht->count += 1;
    }
}

/* Desc: Returns a pointer to the value stored at key
 * Pre:  ht is not null
 * Post: pointer to value found
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{
    assert( ht != NULL );

    struct hashLink *ptr = ht->table[ findKeyIndex( ht, k ) ];
    while( ptr != NULL )
    {
        if( compare( ptr->key, k ) == 0 )
        {
            return( &( ptr->value ) );
        }
        ptr = ptr->next;
    }

    /* If no value, return null */
    return NULL;
}

/* Desc: "boolean" function answering if k is in ht
 * Pre:  ht is not NULL
 * Post: returns truth status
 */
int containsKey (struct hashMap * ht, KeyType k)
{
    assert( ht != NULL );

    struct hashLink *ptr = ht->table[ findKeyIndex( ht, k ) ];
    while( ptr != NULL )
    {
        if( compare( ptr->key, k ) == 0 )
        {
            return( 1 );
        }
        ptr = ptr->next;
    }

    return( 0 );
}

/* Desc: Removes the hashlink with key k
 * Pre:  ht is not null
 * Post: link freed
 */
void removeKey (struct hashMap * ht, KeyType k)
{
    assert( ht != NULL );

    if( containsKey( ht, k ) )
    {
        free( ht->table[ findKeyIndex( ht, k ) ] );
        ht->count -= 1;
    }
}

/* Desc: Find the number of hashLinks in the table
 * Pre:  ht is not null
 * Post: returns number of hash links
 */
int size (struct hashMap *ht)
{
    assert( ht != NULL );

    return( ht->count );
}

/* Desc: Find the number of buckets in the table
 * Pre:  ht is not null
 * Post: returns number of buckets
 */
int capacity(struct hashMap *ht)
{
    assert( ht != NULL );

    return( ht->tableSize );
}

/* Desc: Returns number of empty buckets
 * Pre:  ht is not null
 * Post: returns number of empty buckets
 */
int emptyBuckets(struct hashMap *ht)
{
    assert( ht != NULL );
    int count = 0;

    for( int i = 0; i < ht->tableSize; ++i )
    {
        if( ht->table[ i ] == NULL )
        {
            ++count;
        }
    }
    return( count );
}

/* Desc: Returns # of hashlinks / # of buckets
 * Pre:  ht is not null
 * Post: returns table load
 */
float tableLoad(struct hashMap *ht)
{
    assert( ht != NULL );

    return( (float)( ht->count ) / (float)( ht->tableSize ) );
}
