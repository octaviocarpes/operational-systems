#include <pthread.h>
#include <stdio.h>
#include <malloc.h>

void *PrintHello(void *name){

	while(1){
		printf("Hello World! It's me, thread %s!, (thread: %x)\n", name, pthread_self());
		sleep(1);
	}
}

int main(int argc, char *argv[]){
	pthread_t thread[100];
	int err_code, i=0;
	char *name;

	printf ("Enter thread name at any time to create thread\n");
	while (1){
		name = (char *)malloc(80*sizeof(char));
		scanf("%s", name);
		printf("In main: creating thread %d\n", i);
		err_code = pthread_create(&thread[i], NULL, PrintHello, (void *)name);
		if (err_code){
			printf("ERROR code is %d\n", err_code);
			return -1;
		}else i++;
	}
	pthread_exit(NULL);
}

