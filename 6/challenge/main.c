/*
 * ============================================================================
 *
 *         Author:  Jordan Bayles (baylesj), baylesj@onid.orst.edu
 *        Company:  Oregon State University
 *        Created:  11/24/2012 01:16:15 AM
 *
 *    Environment:  vim + gdb + valgrind, gcc compiler on Arch Linux
 *    Description:  Implementation of hash map functions
 *
 * ============================================================================
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hashMap.h"

#define DICT_NAME "dictionary.txt"
/*
 The getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers separated by periods, spaces, or newlines.

 When there are no more words in the input file this function will return NULL.

 This function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file);

/*
 Load the contents of file into hashmap ht
 */
void loadDictionary(FILE* file, struct hashMap* ht);

int main (int argc, const char * argv[]) {
  clock_t timer;
  struct hashMap* hashTable = malloc( sizeof( struct hashMap ) );
  int tableSize = 1000;
  timer = clock();
  initMap(hashTable, tableSize);

  FILE* dictionary = fopen( DICT_NAME, "r" );

  loadDictionary(dictionary, hashTable);
  timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);

  char* word = (char*)malloc(256*sizeof(char));
  int quit=0;
  while(!quit){
    printf("Enter a word: ");
    scanf("%s",word);

    /* Only spelled correctly if in the dictionary */
    if( containsKey( hashTable, word ) )
    {
        printf( "Word in dictionary\n" );
    }
    else
    {
        printf( "Word not in dictionary\n" );
    }

    /* Don't remove this. It is used for grading*/
    if(strcmp(word,"quit")==0)
      quit=!quit;
  }
  free(word);

  free( hashTable );
  return 0;
}

void loadDictionary(FILE* file, struct hashMap* ht)
{
    char *word = NULL;
    /* Loop through entries */
    while( ( word = getWord( file ) ) )
    {
        /* If already in hash table, throw an error for the user */
        if( containsKey( ht, word ) )
        {
            printf( "Multiple occurrences of a single word detected in dictionary.\n" );
        }
        /* Else insert with occurrence count of 1 */
        else
        {
        insertMap( ht, word, 1 );
        }
    }
}

char* getWord(FILE *file)
{
    int length = 0;
    int maxLength = 16;
    char character;

    char* word = (char*)malloc(sizeof(char) * maxLength);
    assert(word != NULL);

    while( (character = fgetc(file)) != EOF)
    {
        if((length+1) > maxLength)
        {
            maxLength *= 2;
            word = (char*)realloc(word, maxLength);
        }
        if((character >= '0' && character <= '9') || /*is a number*/
           (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
           (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
           (character == 39)) /*or is an apostrophy*/
        {
            word[length] = character;
            length++;
        }
        else if(length > 0)
            break;
    }

    if(length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}
