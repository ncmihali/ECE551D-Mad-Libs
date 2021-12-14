#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void free_cat(catarray_t * c) {
  /* This function frees all the memory allocatedto a catarray_t.
   */
  for (size_t i = 0; i < c->n; i++) {
    free(c->arr[i].name);
    for (size_t k = 0; k < c->arr[i].n_words; k++) {
      free(c->arr[i].words[k]);
    }
    free(c->arr[i].words);
  }
  free(c->arr);
  free(c);
}

catarray_t * allocate_cat(void) {
  /* This function allocates memory to create a new
     catarray_t. Note how I only allocate memory for
     cats->arr, and cats. The rest of memory is allocated
     when adding new members.
  */
  catarray_t * cats = malloc(sizeof(*cats));
  cats->n = 0;
  cats->arr = malloc((cats->n + 1) * sizeof(*cats->arr));
  cats->arr[0].n_words = 0;
  return cats;
}

void new_string(char * s) {
  /* This function will overwrite the previous string with '\0' to
     essentially reset the string, char * s.
  */
  for (size_t i = 0; i < 1000; i++) {
    s[i] = '\0';
  }
}

char * keyword(char * s) {
  /* This function finds the keyword in a valid madlib format (with underscores).
   */
  char * keyword_new = malloc(1000 * sizeof(*keyword_new));
  new_string(keyword_new);  // reset string
  char * ptr = s;
  size_t index = 0;
  int count = 0;
  for (size_t i = 0; i < 100; i++) {
    /* loops through the string and finds a corresponding underscore to stop
       reading.
    */
    if (count == 2)
      break;
    if (s[i] == '_') {
      count += 1;
      continue;
    }
    ptr += 1;
    keyword_new[index] = s[i];
    index += 1;
  }
  return keyword_new;
}

int check_word(char * s) {
  /* This function is for error checking, to see if the madlib input string
     is actually valid. It checks that an underscore is before and after the
     keyword.
  */
  size_t len = strlen(s);
  if ((s[0] == '_' && s[len - 1] == '_') || (s[0] == '_' && s[len - 2] == '_'))
    return 1;
  else if ((s[0] == '_' && s[len - 1] != '_') || (s[0] != '_' && s[len - 1] == '_') ||
           (s[0] != '_' && s[len - 2] == '_')) {
    perror("wrong format of blank\n");  // exit() if the underscore is missing,
    exit(1);                            // or not valid.
  }
  return 0;
}

char * reuse(size_t i, catarray_t * c) {
  /* For keywords that are NUMBERS, this function searches the reused catarray_t
     to find the "number back from the last used word".
  */
  size_t counter = 0;
  char * reuse_char = malloc(1000 * sizeof(*reuse_char));
  for (size_t k = c->arr[0].n_words - 1; k >= 0; k--) {
    // starting from the lst index, counting backwards
    if (counter == i - 1) {
      strcpy(reuse_char, c->arr[0].words[k]);
      return reuse_char;
    }
    counter += 1;
  }
  return "";  // return blank if nothing
}

char * choose_unique_word(catarray_t * c1, char * key, catarray_t * reuse) {
  /* This function was created for step4: which checks if the randomly selected
     word was NOT chosen previously from the reuse catarray_t list.
  */
  char * ans = malloc(1000 * sizeof(*ans));
  int same = 0;  // checks if the random word was found in the list
  int flag = 1;
  char * choose_word = malloc(1000 * sizeof(*choose_word));
  for (size_t i = 0; i < c1->n; i++) {  // first search through the keys to choose from
    if (!(strcmp(c1->arr[i].name, key))) {  // verify word list to traverse through
      while (flag == 1) {
        same = 0;  // set same to unique
        strcpy(choose_word, chooseWord(key, c1));
        for (size_t n = 0; n < reuse->arr[0].n_words; n++) {
          /* Traverse through the reuse list given a random word in the official word
	     selection list. If that randomly selected word is in the reuse list
	     we set same to 1.
	  */
          if (!strcmp(reuse->arr[0].words[n], choose_word)) {
            same = 1;
          }
        }
        if (same == 0) {
          flag = 0;
          strcpy(ans, choose_word);
          free(choose_word);
          return ans;
        }
      }
    }
  }
  free(choose_word);
  free(ans);
  return "";
}

int check_if_int(char * s) {
  size_t len = strlen(s);
  for (size_t i = 0; i < len; i++) {
    if (isdigit(s[i]))
      continue;
    else
      return 0;
  }
  return 1;
}

catarray_t * read_story(catarray_t * c, FILE * fp, int no_repeat) {
  /* This function will call other functions and read the story given its inputs
     and return a catarray_t of used words.
  */
  char buffer[100000] = "";  // holds the line
  char word[100000] = "";
  int p = 0;
  int period_check = 0;

  catarray_t * record_of_words = allocate_cat();
  add_name(record_of_words, "reuse");  // create the reuse list

  while (fgets(buffer, 100000, fp)) {
    /* cycles through the file putting each line in buffer */
    int underscore_count = 0;
    for (size_t x = 0; x < strlen(buffer); x++) {
      if (buffer[x] == '_')
        underscore_count += 1;
    }
    if (underscore_count % 2 != 0) {
      // exit() if keyword is not right format
      perror("not enough underscores\n");
      exit(1);
    }
    underscore_count = 0;  // reset my underscore count
    for (size_t j = 0; j < strlen(buffer); j++) {
      if (buffer[j] == '.')
        period_check = 1;  // checks for a period
      if (buffer[j] == '_') {
        underscore_count += 1;
        if (underscore_count == 1) {
          printf("%s", word);
          p = 0;
          new_string(word);
          word[p] = buffer[j];
          p += 1;
          continue;
        }
        word[p] = buffer[j];
      }
      if (underscore_count == 2 || buffer[j] == '\n' || buffer[j] == '\0') {
        underscore_count = 0;
        /* checks for the end of a word */
        if (check_word(word) == 1) {
          char * key = keyword(word);  // place keyword in var key
          new_string(word);
          if (check_if_int(key)) {     // checks if key is a integer
            size_t index = atoi(key);  //key[0] - '0';
            char * reuse_word = reuse(index, record_of_words);
            strcpy(word, reuse_word);
            new_string(reuse_word);
            free(reuse_word);
            // place reused word in the word to print, as well as in the reuse list
            add_word(record_of_words, "reuse", word);
          }
          else {
            char * random_word = malloc(1000 * sizeof(*random_word));
            strcpy(random_word, key);
            if (no_repeat == 0) {
              strcpy(word, chooseWord(random_word, c));
            }
            else {
              /* else if the -n was chosen, we dont want to repeat chooseWord() */
              char * unique = choose_unique_word(c, random_word, record_of_words);
              strcpy(word, unique);
              free(unique);
            }
            free(random_word);
            add_word(record_of_words, "reuse", word);
          }
          free(key);
        }
        /* officially print out the word after modification to stdout */
        printf("%s", word);
        if (period_check == 1) {
          //printf(".");
          period_check = 0;
        }

        new_string(word);
        p = 0;
        if (buffer[j] == '\n') {
          printf("\n");
          continue;
        }
        //printf(" ");
        continue;
      }
      word[p] = buffer[j];  //place chars from buffer into our word variable
      p += 1;
    }
    p = 0;
  }
  return record_of_words;
}

int checkerror(char * s) {
  /* This function will check for error in the keywork input file.
     If working, return 0, else return 1
  */
  int check_for_colon = 0;
  size_t len = strlen(s);
  for (size_t i = 0; i < len; i++) {
    if (s[i] == '\n')
      continue;
    if (s[i] == ':') {
      check_for_colon = 1;
      continue;
    }
    if (s[i] == ' ')
      continue;
  }
  if (check_for_colon == 0) {
    return 1;
  }
  return 0;
}

void add_name(catarray_t * c, char * name) {
  /* Allocate memory for a new name/cat node
   */
  for (size_t i = 0; i < c->n; i++) {
    // if the name already exists, we dont need to add another one
    if (!(strcmp(c->arr[i].name, name))) {
      return;
    }
  }
  c->n += 1;
  c->arr = realloc(c->arr, (c->n) * sizeof(*c->arr));
  c->arr[c->n - 1].n_words = 0;
  c->arr[c->n - 1].name = malloc(1000 * sizeof(char));
  c->arr[c->n - 1].words =
      malloc((c->arr[c->n - 1].n_words + 1) * sizeof(*c->arr[c->n - 1].words));
  /*c->arr[c->n - 1].words[0] = malloc(1000*sizeof(*c->arr[c->n - 1].words[0]));
  strcpy(c->arr[c->n - 1].words[0], "");*/
  strcpy(c->arr[c->n - 1].name, "");
  strcpy(c->arr[c->n - 1].name, name);
  return;
}

void add_word(catarray_t * c, char * key, char * word) {
  // Creates memory for a word in a category given a key and catarray_t
  for (size_t i = 0; i < c->n; i++) {
    if (!(strcmp(c->arr[i].name, key))) {
      c->arr[i].n_words += 1;
      c->arr[i].words =
          realloc(c->arr[i].words, (c->arr[i].n_words) * sizeof(*c->arr[i].words));
      c->arr[i].words[c->arr[i].n_words - 1] = malloc(100 * sizeof(char));
      strcpy(c->arr[i].words[c->arr[i].n_words - 1], "");
      strcpy(c->arr[i].words[c->arr[i].n_words - 1], word);
      return;
    }
  }
}

catarray_t * add_words(FILE * fp) {
  /* This function is called in Step1, which will read the file of keywords
     and place them into a data structure.
  */
  char buffer[10000] = "";
  char word[10000] = "";
  char key[10000] = "";
  catarray_t * new_array = allocate_cat();
  int check_if_second = 0;  // checks if we are done reading key and then now read word
  size_t index = 0;
  while (fgets(buffer, sizeof(buffer), fp)) {
    /* Reads the file and buffer and places data into data structure */
    if (checkerror(buffer) == 1) {  // error checking
      fprintf(stderr, "error in words file\n");
      exit(1);
    }
    for (size_t k = 0; k < strlen(buffer); k++) {
      if (check_if_second == 0) {
        if (buffer[k] == ':') {
          add_name(new_array, key);
          check_if_second = 1;
          index = 0;
          continue;
        }
        key[index] = buffer[k];
        index += 1;
      }
      if (check_if_second == 1) {  // done reading keyword, now read word
        if (buffer[k] == '\n' || buffer[k] == '\0') {
          index = 0;
          check_if_second = 0;
          add_word(new_array, key, word);
          new_string(word);
          new_string(key);
          continue;
        }
        word[index] = buffer[k];
        index += 1;
      }
    }
  }
  return new_array;  // return catarray_t pointer which will be freed immediatly
}
