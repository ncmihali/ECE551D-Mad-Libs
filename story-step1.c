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

  /* set repetition of random words to TRUE 
     then call read_story which returns a array of used words.
     I will then free that entire catarray_t.
   */

  int no_repeat = 0;
  catarray_t * new_cats = read_story(NULL, f, no_repeat);
  free_cat(new_cats);

  if (fclose(f) != 0) {
    perror("cant close file!");
    return EXIT_FAILURE;
  }
  return 0;
}
