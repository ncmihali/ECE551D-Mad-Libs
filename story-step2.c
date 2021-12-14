#include <stdio.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "not enough arguments");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("cant open file");
    return EXIT_FAILURE;
  }

  /*
    I create a new catarray_t which stores all the keys
    and their words in a datastrucure.
    I then print those words, and free the catarray_t.
  */

  catarray_t * words = add_words(f);
  printWords(words);
  free_cat(words);

  if (fclose(f) != 0) {
    perror("cant close file!");
    return EXIT_FAILURE;
  }
  return 0;
}
