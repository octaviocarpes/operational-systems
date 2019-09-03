#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("I am process %d\n", getpid());
	printf("My parent is %d\n", getppid());

	printf("My real user ID is       %d\n", getuid());
	printf("My effective user ID is  %d\n", geteuid());
	printf("My real group ID is      %d\n", getgid());
	printf("My effective group ID is %d\n", getegid());

	return 0;
}

