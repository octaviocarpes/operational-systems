#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	pid_t childpid;

	childpid = fork();

	if (childpid == -1) {
		perror("Failed to fork\n");
		return 1;
	}
	if (childpid == 0) {
		execl("/bin/ls", "ls", "-l", 0);
		perror("Child failed to exec ls\n");
		return 1;
	}
	if (childpid != wait(0)){
		perror("Parent failed to wait due to signal or error\n");
		return 1;
	}

	return 0;
}
