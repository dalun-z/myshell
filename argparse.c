#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "argparse.h"
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define FALSE (0)
#define TRUE  (1)

static int argCount(char* line);



/*
* argCount is a helper function that takes in a String and returns the number of "words" in the string assuming that whitespace is the only possible delimeter.
*/
static int argCount(char*line)
{
  int count_words = 0;
  int length = strlen(line);

  if(line == NULL){
    return count_words;
  }else {
    for(int i = 0; i < length; i++){
      if(isspace(line[i])){
        count_words++;
      }
    }
  }
  return count_words+1;
}



/*
*
* Argparse takes in a String and returns an array of strings from the input.
* The arguments in the String are broken up by whitespaces in the string.
* The count of how many arguments there are is saved in the argcp pointer
*/
char** argparse(char* line, int* argcp)
{

  char *word;
  *argcp = argCount(line);

  char **argArr = (char**)malloc((*argcp) * sizeof(char**));
  int begCounter = 0;

  while((word = strsep(&line, " ")) != NULL ){
    if(strcmp(word, "\0") != 0){
      argArr[begCounter] = word;
      begCounter++;
    }
  }
  
  return argArr;
}

