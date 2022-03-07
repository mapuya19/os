#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_LEN 1024

// hello
int hello() { printf("Hey there!\n"); }

// bye
int bye() {
  printf("See ya later!\n");
  exit(0);
}

// assignment
int assignment() { printf("202 lab #1 (Spring 2022)\n"); }

// author
int author() { printf("Matthew Apuya • N13953137 • mja610\n"); }

// section
int section() { printf("002\n"); }

// check if command is built in
int isBuiltIn(char *args) {
  if (strcmp(args, "hello") == 0) {
    hello();
    return 1;
  } else if (strcmp(args, "bye") == 0) {
    bye();
    // program should be ending
  } else if (strcmp(args, "assignment") == 0) {
    assignment();
    return 1;
  } else if (strcmp(args, "author") == 0) {
    author();
    return 1;
  } else if (strcmp(args, "section") == 0) {
    section();
    return 1;
  }

  return 0;
}

int main() {
  // initialize stuff
  char line[BUFFER_LEN]; // command line
  char *argv[50];         // user command
  char *path = "/bin/";  // setting path to bin
  char progpath[20];     // full file path
  int argc;              // argument count
  int status;            // status

  // main loop
  while (1) {
    // shell name!
    printf("apuya_shell >> ");

    // get user command
    if (!fgets(line, BUFFER_LEN, stdin)) {
      break;
    }

    // remove trailing new line
    line[strcspn(line, "\n")] = 0;

    if (isBuiltIn(line)) {
      continue;
    } else {      
      // split command into separate strings
      char *token;
      token = strtok(line, " ");
      int i = 0;

      while (token != NULL) {
        argv[i] = token;
        token = strtok(NULL, " ");
        i++;
      }

      // set last value to NULL & get arg count
      argv[i] = NULL; 
      argc = i; 

      // copy /bin/ to file path & add program to path
      strcpy(progpath, path);    
      strcat(progpath, argv[0]); 

      // delete newline
      for (i = 0; i < strlen(progpath); i++) { 
        if (progpath[i] == '\n') {
          progpath[i] = '\0';
        }
      }

      // fork child
      int parentOrChild = fork();

      if (parentOrChild == 0) { // child
        execve(progpath, argv, NULL);
        fprintf(stderr, "could not execve\n");

      } else { // parent
        wait(&status);
      }
    }
  }
}