#define MAX_WORD_SIZE   40
#define MAX_DESC_SIZE  200
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * A dictionary is a collection of mappings from WORDs to DESCRIPTIONs
 * A WORD is a sequence of characters up to MAX_WORD_SIZE in length
 * A DESCRIPTION is a sequence of characters (including spaces) up to
 *   MAX_DESC_SIZE in length
 */

struct tree * t;

//edited from notes on avl binary trees from the module provided by David Smallwood
typedef int (*rel_fun)(struct entry a, struct entry b);

struct entry {	
	char word[MAX_WORD_SIZE];
   	char meaning[MAX_DESC_SIZE];	
};

//edited from notes on avl binary trees from the module provided by David Smallwood
struct node
{
    char height;
    struct entry item;
    struct node * left;
    struct node * right;
};

//edited from notes on avl binary trees from the module provided by David Smallwood
struct tree
{
    struct node * root;
    int size;
    rel_fun lt;
};


//edited from notes on avl binary trees from the module provided by David Smallwood
struct tree * new_avl_any(rel_fun lt)
{
    struct tree * t = (struct tree*)malloc(sizeof(struct tree*));
    t->root = NULL;
    t->size = 0;
    t->lt = lt;
    return t;
}

int smaller(struct entry A, struct entry B) {
		
	int ret = strcmp(A.word, B.word);
	
	if (ret > 0) {
		
		return 0;
		
	} else {
		
		return 1;
		
	}
}

/**
 * d_initialise: initialise the dictionary so that it contains no entries
 */
void d_initialise() {

	t = new_avl_any(smaller);
}

struct node * search(struct tree *t, struct entry search_item, struct node * p)
{
	struct node *q;
	q = p;
	assert(p!=NULL);
	if (LT(search_item,p->item)) {                       // searching left sub-tree
       	search(t, search_item, p->left);
    }   
    else if (LT(p->item, search_item)) {                // searching right sub-tree
        search(t, search_item, p->right);
    }
	else {
		return q;
	}
}

struct node * avl_search(struct tree *t, struct entry x)
{
	return search(t, x, t->root);
}

//edited from notes on avl binary trees from the module provided by David Smallwood
struct node* rotate_left(struct node *p)
{
    struct node *q;
    assert(p!=NULL);
    assert(p->right!=NULL);
    q = p->right;
    p->right = q->left;
    q->left = p;
    p->height = 1 + MAX(HEIGHT(p->left),HEIGHT(p->right));
    q->height = 1 + MAX(HEIGHT(q->left),HEIGHT(q->right));
    return q;
}

//edited from notes on avl binary trees from the module provided by David Smallwood
struct node* rotate_right(struct node *p)
{
    struct node *q;
    assert(p!=NULL);
    assert(p->left!=NULL);
    q = p->left;
    p->left = q->right;
    q->right = p;
    p->height = 1 + MAX(HEIGHT(p->left),HEIGHT(p->right));
    q->height = 1 + MAX(HEIGHT(q->left),HEIGHT(q->right));
    return q;
}

struct node * ensure_balance(struct node *p)
{
    if (p==NULL)
        return p;                                   // trivially balanced - return now

    p->height = 1 + MAX(HEIGHT(p->left),HEIGHT(p->right));
    
    if ( HEIGHT(p->left) - HEIGHT(p->right) > 1) {  // left-heavy  - rebalance needed

       if (HEIGHT(p->left->left) > HEIGHT(p->left->right))
            p = rotate_right(p);
        else {
            p->left = rotate_left(p->left);
            p = rotate_right(p);
        }
    }
    else
    if ( HEIGHT(p->right) - HEIGHT(p->left) > 1) {  // right-heavy - rebalance needed

        if (HEIGHT(p->right->right) > HEIGHT(p->right->left))
           p = rotate_left(p);
        else {
           p->right = rotate_right(p->right);
           p = rotate_left(p);
        }
    }
    else                                            // balanced - no rebalance needed
        ;
        
    return p;
}

struct node * ins(struct tree *t, struct entry x, struct node *p)
{
    if (p==NULL) {
        p = (struct node *)malloc(sizeof(struct node));
        if (p==NULL) {
            printf("avl_anyinsert (ins): failed to allocate memory\n");
            exit(1);
        }
        p->left   = p->right = NULL;
        p->item   = x;
        (t->size)++;
    }
    else if (LT(x,p->item)) {                       // inserting into left sub-tree
        p->left = ins(t, x, p->left);
    }   
    else if (LT(p->item,x)) {                       // inserting into right sub-tree
        p->right = ins(t, x, p->right);
    }

    return ensure_balance(p);
}

//modified from http://stackoverflow.com/questions/10279718/append-char-to-string-in-c User: Lay González
char * append(char * string, char character)
{
    char * result = NULL;
    asprintf(&result, "%s%s", string, character);
    return result;
}

void d_insert(struct entry* input) {
    avl_any_insert(t, input);
}

void inc(int *x) {
	*x = (*x + 1) % 2;
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
 	
	// modified from http://www.programmingsimplified.com/c-program-read-file

	char ch;
	char wordbuff[MAX_WORD_SIZE];
	char meanbuff[MAX_DESC_SIZE];
	int control = 0;
   	FILE *fp;
	struct entry input;
 
  	fp = fopen(*filename,"r"); // read mode
 
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

	struct entry* output;

	output = avl_search(t, input);

	if(strcmp(input.word,output->word)) {
		strcpy(meaning, output->meaning);
		return 1;
	}
	return 0;
}
