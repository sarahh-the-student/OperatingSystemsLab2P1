/*
 * Program Description: 
 * This program creates two child processes. Each child loops a random number 
 * of times (up to 30), sleeping for a random duration (1-10s) in each iteration.
 * * The parent waits for both children to complete and decodes their exit status
 * using WIFEXITED/WEXITSTATUS to ensure valid termination reporting.
 * * Randomness is seeded using time(NULL) ^ PID to ensure unique sequences per child.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <sys/wait.h> 
#include <time.h>    

void child_process();

// parent process
int main () {
  int pid;
  int i; 

  // Loop to create two child processes
  for (i = 0; i < 2; i++) {
    pid = fork(); 
    if (pid == 0) {
      child_process();
    }
    else if (pid < 0) {
      perror("Fork failed");
      exit(1);
    }
  }

  // Parent continues the loop to wait for children
  for (i = 0; i < 2; i++){
    int status;
    int completed_pid = wait(&status);
    if (WIFEXITED(status)) {
      printf("Parent: Child Pid %d has completed with exit status: %d\n", completed_pid, WEXITSTATUS(status));
    }
  } 
  return 0;
} 

// run one child process
void child_process(){
  int pid = getpid();
  int parent_pid = getppid();
  srandom(time(NULL) ^ pid);

  // random number no more than 30 
  int n = 1 + (random() % 30); 
  int i;
  printf("Child Pid: %d starting %d iterations...\n", pid, n);
  fflush(stdout);

  for (i = 0; i < n; i++){
    int sleep_time = 1 + (random() % 10);
    printf("Child Pid: %d is going to sleep for %d seconds!\n", pid, sleep_time);
    fflush(stdout);
    sleep(sleep_time);
    printf("Child Pid: %d is awake! Where is my Parent: %d?\n", pid, parent_pid); 
    fflush(stdout);
  }
  exit(0);
} 