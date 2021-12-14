#include <stdio.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  /*
    Error checking to give people the option of either
    3 OR 4 arguments
  */
  if ((argc > 4) || (argc < 3)) {
    perror("not enough arguments");
    return EXIT_FAILURE;
  }
  int no_repeat = 0;
  if (!strcmp(argv[1], "-n")) {
    no_repeat = 1;
  }
  FILE * f1;
  FILE * f2;
  /*
    If they choose NOT to repeat words, I read from the 3rd and 4th
    input for my files, else, I read from the 2nd and 3rd input.
  */
  if (no_repeat == 1) {
    f1 = fopen(argv[2], "r");
    if (f1 == NULL) {
      perror("file not found");
      return EXIT_FAILURE;
    }
    f2 = fopen(argv[3], "r");
    if (f2 == NULL) {
      perror("file not found");
      return EXIT_FAILURE;
    }
    catarray_t * words = add_words(f1);
    catarray_t * read_temp = read_story(words, f2, no_repeat);
    free_cat(words);
    free_cat(read_temp);
  }
  else {
    f1 = fopen(argv[1], "r");
    if (f1 == NULL) {
      perror("file not found");
      return EXIT_FAILURE;
    }
    f2 = fopen(argv[2], "r");
    if (f2 == NULL) {
      perror("file not found");
      return EXIT_FAILURE;
    }

    catarray_t * words = add_words(f1);
    catarray_t * read_temp = read_story(words, f2, no_repeat);
    free_cat(words);
    free_cat(read_temp);
  }

  /*
    After freeing the created catarray_ts, I then attempt to close both files
  */
  if (fclose(f1) != 0 || fclose(f2) != 0) {
    perror("cant close files");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
