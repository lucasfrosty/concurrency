#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t pid = fork();

	if (pid == 0) {
		printf("(CHILD) Return reference PID is: %d\n", pid);
		printf("(CHILD) But the actual PID is: %d\n", getpid());
		printf("(CHILD) His parent PID is: %d\n", getppid());
	}
	else if (pid > 0) {
		printf("(PARENT) The parent PID is: %d\n", getpid());
		printf("(PARENT) The child PID is: %d\n", pid);
		wait(0);
	}
	else {
		perror ("fork() error");
	}
	return 0;
}
