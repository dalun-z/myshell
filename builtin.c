#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include "builtin.h"
#include <string.h>
#include <dirent.h>

//Prototypes
static void exitProgram(char** args, int argcp);
static void cd(char** args, int argcp);
static void pwd(char** args, int argcp);
static void ls(char** args, int argcp);


/* builtIn
 ** built in checks each built in command the given command, if the given command
 * matches one of the built in commands, that command is called and builtin returns 1.
 *If none of the built in commands match the wanted command, builtin returns 0;
  */
int builtIn(char** args, int argcp)
{
    if(argcp < 1){
      return 0;
    }

    if(!strcmp(args[0], "exit")){
      exitProgram(args, argcp);
      return 1;
    }else if(!strcmp(args[0], "pwd")){
      pwd(args, argcp);
      return 1;
    }else if(!strcmp(args[0], "cd")){
      cd(args, argcp);
      return 1;
    }else if(!strcmp(args[0], "ls")){
      ls(args, argcp);
      return 1;
    }else
      return 0;
}

static void exitProgram(char** args, int argcp)
{
  if(argcp > 1){
    exit(3);
  }else
    exit(0);
}

static void pwd(char** args, int argcp)
{
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  printf("%s\n", cwd);
}


static void cd(char** args, int argcp)
{
  char cwd[256];
  char *newCwd = getcwd(cwd, sizeof(cwd));

  if(argcp > 1){
    chdir(args[1]);
    setenv("pwd", newCwd, 1);
  }
}


static void ls(char** args, int argcp)
{
  struct dirent **nameList;
  int n;

  n = scandir(".", &nameList, NULL, alphasort);
  if(n == -1){
    perror("scandir");
    exit(EXIT_FAILURE);
  }

  while(n--){
    printf("%s\n", nameList[n]->d_name);
    free(nameList[n]);
  }
  free(nameList);
  EXIT_SUCCESS;
}