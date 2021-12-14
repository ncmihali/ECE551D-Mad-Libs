#include <stdio.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  /* 
     error checking if not excactly 3 arguments
  */
  if (argc != 3) {
    perror("not enough arguments");
    return EXIT_FAILURE;
  }
  FILE * f1 = fopen(argv[1], "r");
  if (f1 == NULL) {
    perror("file not found");
    return EXIT_FAILURE;
  }
  FILE * f2 = fopen(argv[2], "r");
  if (f2 == NULL) {
    perror("file not found");
    return EXIT_FAILURE;
  }

  /*
    Here, I read in the words from file f1, select it to 
    repeat randomly chosen words, and then read the story which 
    will return a catarray_t of used words.  
    I then free each of the catarray_ts I created.
  */

  catarray_t * words = add_words(f1);
  int no_repeat = 0;
  catarray_t * temp_words = read_story(words, f2, no_repeat);
  free_cat(words);
  free_cat(temp_words);

  if (fclose(f1) != 0 || fclose(f2) != 0) {
    perror("cant close");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
