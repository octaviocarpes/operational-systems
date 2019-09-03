#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

pid_t r_wait(int *stat_loc)
{
	int retval;

	while (((retval = wait(stat_loc)) == -1) && (errno == EINTR));

	return retval;
}

int main(int argc, char *argv[]){
	pid_t childpid;
	int i, n;

	if (argc != 2) {	/* check for valid number of command-line arguments */
		fprintf(stderr, "Usage: %s processes\n", argv[0]);
		return 1;
	}
	n = atoi(argv[1]);

	for (i = 1; i < n; i++) {
		childpid = fork();
		if (childpid <= 0)
			break;
	}

	while (r_wait(NULL) > 0);	/* wait for all of your children */
	fprintf(stderr, "i:%d proc ID: %d parent ID: %d  child ID: %d\n",
		i, getpid(), getppid(), childpid);

	return 0;
}
