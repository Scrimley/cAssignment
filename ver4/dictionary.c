#define MAX_WORD_SIZE   40
#define MAX_DESC_SIZE  200
//edited from notes on clist from the module provided by David Smallwood
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dictionary.h"
/**
 * A dictionary is a collection of mappings from WORDs to DESCRIPTIONs
 * A WORD is a sequence of characters up to MAX_WORD_SIZE in length
 * A DESCRIPTION is a sequence of characters (including spaces) up to
 *   MAX_DESC_SIZE in length
 */

//edited from notes on clist from the module provided by David Smallwood
struct entry {
	
	char word[MAX_WORD_SIZE];
   	char meaning[MAX_DESC_SIZE];
	struct entry * next;
    struct entry * prev;
    	
};

//edited from notes on clist from the module provided by David Smallwood
struct dictionary
{
    struct entry * sentinel;
    struct entry * cursor;
    int size;
};


dictionary * d;

/**
 * d_initialise: initialise the dictionary so that it contains no entries
 */
void d_initialise() {

	//edited from notes on clist from the module provided by David Smallwood
	d = (dictionary *)malloc(sizeof(dictionary));
    if (d==NULL) {
        printf("new_clist: malloc failure.\n");
        exit(1);
    }
    d->size = 0;
    d->sentinel = (struct entry *) malloc(sizeof(struct entry));
    if (d->sentinel==NULL) {
        printf("new_clist(sentinel): malloc failure.\n");
        exit(1);
    }
	strcpy(d->sentinel->word, "");
	strcpy(d->sentinel->meaning, "");
    d->sentinel->next = d->sentinel;
    d->sentinel->prev = d->sentinel;
    d->cursor = d->sentinel;
}

//modified from http://stackoverflow.com/questions/10279718/append-char-to-string-in-c User: Lay González
char * append(char * string, char character)
{
    char * result = NULL;
    asprintf(&result, "%s%s", string, character);
    return result;
}

void d_insert(struct entry* input) {
	//edited from notes on clist from the module provided by David Smallwood
    struct entry * e = (struct entry *) malloc(sizeof(struct entry));
    if (e==NULL) {
        printf("clist_ins_after: malloc failure.\n");
        exit(1);
    }
	strcpy(e->word, input->word);
	strcpy(e->meaning, input->meaning);
    e->prev = d->cursor;
    e->next = d->cursor->next;
    d->cursor->next->prev = e;
    d->cursor->next = e;
    d->size++;
}

void inc(int *x) {
	*x = (*x + 1) % 2;
}

int inlist(dictionary *d)
{
	//edited from notes on clist from the module provided by David Smallwood
    assert(d!=NULL);
    return d->cursor != d->sentinel;
}

void goto_head(dictionary *d)
{
	//edited from notes on clist from the module provided by David Smallwood
    assert(d!=NULL);
    d->cursor = d->sentinel->next;
}

void goto_next(dictionary *d)
{
	//edited from notes on clist from the module provided by David Smallwood
    assert(d!=NULL);
    d->cursor = d->cursor->next;
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

int d_read_from_file(const char * filename) {
 	
	// modified from http://www.programmingsimplified.com/c-program-read-file

	char ch;
	char wordbuff[MAX_WORD_SIZE];
	char meanbuff[MAX_DESC_SIZE];
	int control = 0;
   	FILE *fp;
	struct entry input;
 
  	fp = fopen(filename,"r"); // read mode
 
  	if( fp == NULL ) {
  	    perror("Error while opening the file.\n");
      	return 0;
   	}
 
  	printf("The contents of %s file are :\n", filename);
 
   	while( ( ch = fgetc(fp) ) != EOF ) {
      	printf("%c",ch);
	    if (ch == ' ' && control == 0) {
			strcpy(input.word, wordbuff);
			strcpy(wordbuff, "");
			inc(&control);
	    }
	    else if (ch == '\n') {
			strcpy(input.meaning, meanbuff);
			d_insert(&input);
			strcpy(meanbuff, "");
			inc(&control);
	    }
	    else if (ch != '.') {
			if (control = 0) {
	   			append(wordbuff, ch);
			}
			
			else if (control = 1) {
	    		append(meanbuff, ch);
			}
	    }
	}
   	fclose(fp);
   	return 1;
	
}

/*
int search(dictionary *d, struct entry p)
{
	//edited from notes on clist from the module provided by David Smallwood
    assert(d!=NULL);
    goto_head(d);
    while (inlist(d) && (!p(d->cursor->item)))
        goto_next(d);
    return inlist(d);    
}
*/

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

	struct entry input;
	
	strcpy(input.word, word);
	strcpy(input.meaning, meaning);

	strcpy(meaning, "fish");

	struct entry* output;

	return 1;
}
