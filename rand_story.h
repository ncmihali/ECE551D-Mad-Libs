#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdio.h>

#include "provided.h"

catarray_t * add_words(FILE * fp);
catarray_t * read_story(catarray_t * c, FILE * fp, int repeat);
catarray_t * allocate_cat(void);
void new_string(char * s);
char * keyword(char * s);
int check_word(char * s);

void add_word(catarray_t * c, char * key, char * word);
void add_name(catarray_t * c, char * word);
int checkerror(char * s);
//void add_words(FILE * fp);
void free_cat(catarray_t * c);

void replace_story(catarray_t * c, FILE * fp);
char * reuse(size_t i, catarray_t * c);
char * choose_unique_word(catarray_t * c1, char * key, catarray_t * reuse);
int check_if_int(char * s);
//any functions you want your main to use

#endif
