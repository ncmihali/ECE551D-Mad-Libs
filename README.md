# Auto-complete Mad Libs Program

Program to tell a random story (kind of like Mad Libs) that generates a story, 
given a story template and a list of words to choose from.

For example, if you had a story like the one in story.txt:

Once upon a time, there was a _animal_ who lived in a very _adjective_
_place_.

And some words to choose from like in words.txt:

animal:dragon
animal:walrus
place:cave
adjective:peculiar
adjective:scary
adjective:peaceful

The program might produce:

Once upon a time, there was a walrus who lived in a very peaceful
cave.

The story template will be provided in an input file, where the "blanks"
are the category name preceded and followed by an underscore
("_"). Eventually, your program should replace this blank with a word from
the word list of the appropriate category. The categories and word choices
are provided in a separate input file with the category name, colon (":"),
then word. Your program should print the story to stdout. 

You will write this program in four steps. The first step focuses on
parsing the story template. The second is reading categories and words,
storing them into an appropriate data structure. Step 3 combines the
functionality of steps 1 and 2 to create a random story program. Step 4
adds the option of not reusing words.

Open provided.h, and you will see two struct definitions, one for a
category_t to store information about a category, such as "animal" or
"verb" with an array of words that will contain possible replacement words
for that category. You will also see a struct catarray_t for an array of
category_t's and the prototypes for two functions, which we provide. 

The function

const char * chooseWord(char * category, catarray_t * cats);

takes a string representing the category name and a catarray_t * "cats",
from which it will select a word in the requested category. If "cats" is
not NULL, this function returns a pointer to the string in "cats"--it does
not allocate new memory. If the requested category does not exist in
"cats", or the category does not have any words, the function will exit the
program with a failure status. If "cats" is NULL, the function will return
the string literal "cat", i.e. chooseWord("verb", NULL) would return
"cat". 

The function

void printWords(catarray_t * cats);

prints out the catarray_t * "cats" for the purpose of testing the contents
of that data structure.

The definitions of these functions are in provided.o, which the Makefile
will link with your code.

# Step 1

Write the program story-step1, which takes one command line argument: the
name of the file to read the story template from. This program should parse
the story template by printing the story and replacing blanks with the word
"cat". Your code should call the provided function chooseWord, for this
step passing in NULL as the second argument to get return value "cat".

For example, for the input in story.txt, this program would print:

Once upon a time, there was a cat who lived in a very cat
cat.

For the format of the input file, each blank must begin and end with an
underscore '_'. If a blank begins, it must have a matching underscore on
the same line; otherwise, it is an error. If there is anything wrong with
the input file, you should print an appropriate error message and exit with
a failure status.

As you plan your code for this step, consider how you can write re-usable
code for the subsequent parts. You will want to write as much code as
possible in rand_story.c to avoid code duplication. Then you can write the
prototypes of functions in rand_story.h and include this in your
story-step1.c.

Once you have tested this step to your satisfaction, add/commit/push before
going on to the next step.

# Step 2

Write the program story-step2, which takes one command line argument: the
name of the file with the categories and words. This program should read
from the file and store the words into a catarray_t and print them using
the provided function printWords.

For example, if given the file words.txt, the output would be:

animal:
  dragon
  walrus
place:
  cave
adjective:
  peculiar
  scary
  peaceful
  
Each line of the input file must have a colon (':'). The category name may
be any characters (except a colon), and the replacement word is everything
following the colon until (and not including) the newline. We place no
other restrictions on the words or the order the lines appear in the
file. If the input file does not have the right format, you should print an
appropriate error message and exit with a failure status.

Again, consider how you can write as much of this code in rand_story.c in a
re-usable way.

# Step 3

Write the program story-step3, which takes two command line arguments: the
name of the file with the categories/words and the name of the file for the
story template. This program should make use of the functions you wrote
for step 1 and step 2, but it should add the functionality to 1) randomly
choose a word from the named category to replace each blank and 2) support
references to previously used words.

If the category name is a valid integer of at least one, you should replace
the blank with a previously used word, counting backwards from the current
word, such that 1 refers to the immediate previous word.

Otherwise, if the category name is a category in the catarray_t, you should
call chooseWord, which will return a random choice from that category
(since the second argument is not NULL). If a category name is neither a
valid integer nor a valid category name, the program should exit with a
failure status. 

For example, if the story template is story2.txt and the words file is
words.txt, the output would be:

Once upon a time, there was a walrus. This walrus lived in a very
scary cave. One day, it left its scary cave and met a walrus.

Note that in this example, if "walrus" is the word chosen for the first
_animal_ blank, the _1_ blank *must* be replaced with with "walrus". The
second _animal_ blank might be replaced with either "walrus" or "dragon",
but the random seed used in provided.o made chooseWord return "walrus" both
times. 

Hint: You will want a way to keep track of words that have been used. The
struct category_t already has an array of words and the length of that
array. You could maintain a category_t that keeps track of used words.

# Step 4

Write the program story-step4, which takes one optional and two required
command line arguments: an option "-n" indicating no reuse of words, the 
name of the file with the categories/words, and the name of the file for
the story template. This program should make use of the functions you wrote
in previous steps, but should add optional functionality to prevent the
reuse of a word from a category. That is, if the argument "-n" is given,
your program should ensure that chooseWord will not return a word that has
already been used. Numbered blanks should still reference a previously used
word as in step 3.

For example, if you run this program

./story-step4 -n words.txt story2.txt

The output should be:

Once upon a time, there was a walrus. This walrus lived in a very
scary cave. One day, it left its scary cave and met a dragon.

If this program is run without the "-n" argument, its behavior should be
identical to the program in step 3.
