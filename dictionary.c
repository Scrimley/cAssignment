#define MAX_WORD_SIZE   40
#define MAX_DESC_SIZE  200
#include "avl_any.h"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
/**
 * A dictionary is a collection of mappings from WORDs to DESCRIPTIONs
 * A WORD is a sequence of characters up to MAX_WORD_SIZE in length
 * A DESCRIPTION is a sequence of characters (including spaces) up to
 *   MAX_DESC_SIZE in length
 */

typedef struct entrystruct {
	
	char word[MAX_WORD_SIZE];
    	char meaning[MAX_DESC_SIZE];
    	
} entry;

/**
 * d_initialise: initialise the dictionary so that it contains no entries
 */
void d_initialise() {

	int smaller(entry *A, entry *B) {
	
		int ret = strcmp(A->word,B->word);
	
		if (ret > 0) {
		
			return 0;
		
		} else {
		
			return 1;
		
		}
	}

	avl_any *t = new_avl_any(smaller);
}

/**
 * d_read_from_file:
 *              Reads a textfile of words and their descriptions and
 *              adds these to the dictionary.  NB: If a word is
 *              encountered that is already in the dictionary then the
 *              new description replaces the existing one.  Reading
 *              stops when a line is read from the file that contains
 *              a single dot "." character in the first position.
 *
 * filename:    a string representing the filename for the dictionary
 *              entries.  The file is a text file with one entry per
 *              line.  An entry consists of a word followed by some
 *              whitespace followed by a description.  The data in the
 *              file are not necessarily ordered.  An example entry
 *              could be:
 *
 *              aardvark Burrowing, nocturnal mammal native to Africa
 *
 * Returns:     true (1) if the file was successfully imported into the
 *              dictionary;
 *              false (0) if the file was not successfully imported.
 */
int d_read_from_file(const char ** filename) {
 	
	char ch;
   	FILE *fp;
 
  	fp = fopen(*filename,"r"); // read mode
 
  	if( fp == NULL ) {
  	    perror("Error while opening the file.\n");
      	    exit(EXIT_FAILURE);
   	}
 
  	printf("The contents of %s file are :\n", filename);
 
   	while( ( ch = fgetc(fp) ) != EOF )
      	    printf("%c",ch);
 
   	fclose(fp);
   	return 0;
	
}


/**
 * d_lookup:    Looks up a word in the dictionary and returns the
 *              description in the user-supplied character buffer.
 *
 * word:        the word the user is searching for in the dictionary.
 *
 * meaning:     the description is copied into this buffer which the
 *              user supplies and guarantees to be at least
 *              MAX_DESC_SIZE+1 characters.
 *
 * Returns:     true (1) if the word was found in the dictionary;
 *              false (0) if the word was not found in the dictionary.
 */
int d_lookup(const char * word, char * meaning) {
 	
	return 1;
	 
}
