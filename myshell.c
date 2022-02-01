/* CS 347 -- Mini Shell!
 * Original author Phil Nelson 2000
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include "argparse.h"
#include "builtin.h"


/* PROTOTYPES */

void processline (char *line);
ssize_t getinput(char** line, size_t* size);

/* main
 * This function is the main entry point to the program.  This is essentially
 * the primary read-eval-print loop of the command interpreter.
 */

int main () {

 //write your code
 //use getinput and processline as appropriate
  char *input = (char*)malloc(sizeof(char) * 100 );
  size_t s;
  ssize_t inputLen = 0;
  
  while(1){
    inputLen = getinput(&input, &s);
    input[inputLen-1] = '\0';

    if(inputLen < 0){
      perror("Error");
      continue;
    }
    processline(input);
  }
  

  return EXIT_SUCCESS;
}


/* getinput
* line     A pointer to a char* that points at a buffer of size *size or NULL.
* size     The size of the buffer *line or 0 if *line is NULL.
* returns  The length of the string stored in *line.
*
* This function prompts the user for input.  If the input fits in the buffer
* pointed to by *line, the input is placed in *line.  However, if there is not
* enough room in *line, *line is freed and a new buffer of adequate space is
* allocated.  The number of bytes allocated is stored in *size.
*/
ssize_t getinput(char** line, size_t* size) {
  assert(line != NULL && size != NULL);

  errno = 0;
  //print the prompt e.g. %myshell%
  ssize_t len = getline(line, size, stdin);
  
  //write your code 

  return len;
}


/* processline
 * The parameter line is interpreted as a command name.  This function creates a
 * new process that executes that command.
 * Note the three cases of the switch: fork failed, fork succeeded and this is
 * the child, fork succeeded and this is the parent (see fork(2)).
 * processline only forks when the line is not empty, and the line is not trying to run a built in command
 */
void processline (char *line)
{
 /*check whether line is empty*/
  if(line == NULL){
    exit(0);
  }
    
  pid_t cpid;
  int   status;
  int argCount;
  char** arguments = argparse(line, &argCount);
  
  /*check whether arguments are builtin commands
   *fork, and execute the commands
   */
  if(builtIn(arguments, argCount) != 1){
    char *newArr[(argCount+1)];
    size_t i = 0;

    for(; i < argCount; i++){
      newArr[i] = arguments[i];
    }

    newArr[i] = (char*)0;

    cpid = fork();
    waitpid(-1, NULL, 0);
    if(cpid == -1){
      perror("fork error");
      exit(EXIT_FAILURE);
    }
    if(cpid == 0){
      int ret;
      ret = execvp(*newArr, newArr);
      exit(0);
    }
  }

  free(arguments);
}

