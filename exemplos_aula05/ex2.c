#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int x;

	x = 0;
	fork();
	x = getppid();
	printf("I am process %d and my x is %d\n", getpid(), x);
	return 0;
}

