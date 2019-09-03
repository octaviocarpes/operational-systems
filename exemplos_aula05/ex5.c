#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t childpid = 0;
	int i, n;

	if (argc != 2) {   /* check for valid number of command-line arguments */
		printf("Usage: %s processes\n", argv[0]);
		return 1;
	}
	n = atoi(argv[1]);

	for (i = 1; i < n; i++) {
		childpid = fork();
		if (childpid <= 0)	/* only the child (or error) enters */
			break;
	}

	fprintf(stderr, "i:%d  process ID: %d  parent ID: %d  child ID: %d\n",
		i, getpid(), getppid(), childpid);

	return 0;
}
