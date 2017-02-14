#include <stdio.h>
#include <unistd.h>  
#include <sys/wait.h>
#include <stdlib.h>

// *********************** LIGHT FUNCTION **********************
void function_light(){
  printf("--beginning of program\n");

  int counter = 0;
  pid_t pid = fork();
  int y;
  if (pid == 0) {
        // child process
    for (int i = 0; i < 5; ++i) {
      printf("(light) child process: counter=%d\n", ++counter);
    }
  }
  else if (pid > 0) {
        // parent process
    for (int j = 0; j < 5; ++j) {
      printf("(light) parent process: counter=%d\n", ++counter);
    }
    // wait(0);
  }
  else {
        // fork failed
    perror("fork() error");
    exit(-1);
  }
  printf("--end of program--\n\n");

}

// *********************** HEAVY FUNCTION **********************
void function_heavy(){
  printf("--beginning of program\n");

  int counter = 0;
  pid_t pid = fork();
  int y;
  if (pid == 0) {
        // child process
    for (int i = 0; i < 5; ++i)
    {
      printf("(heavy) child process: counter=%d\n", ++counter);
    }
  }
  else if (pid > 0) {
        // parent process
    for (int j = 0; j < 5; ++j) {
      for (int k = 0; k < 400; ++k) {
        if(k != 99) {
          for (int e = 0; e < 800; ++e) {
            y = k;
          }
        }
      }
      printf("(heavy) parent process: counter=%d\n", ++counter);
    }
    // wait(NULL);
  }
  else {
        // fork failed
    perror("fork() error");
    exit(-1);
  }

  printf("--end of program--\n");
}


// *********************** MAIN FUNCTION **********************
int main(int argc, char **argv) {

  printf("\n** Light Started **\n\n");
  function_light();
  printf("\n** Heavy Started ** \n\n");
  function_heavy();

  return 0;
} 