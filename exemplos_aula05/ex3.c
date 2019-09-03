#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	pid_t childpid;

	childpid = fork();
	if (childpid == -1) {			/* error */
		perror("Failed to fork\n");
		return 1;
	}

	if (childpid == 0) { 			/* child code */
		printf("I am child %d\n", getpid());
	} else {				/* parent code */
		printf("I am parent %d\n", getpid());
	}

	return 0;
}
