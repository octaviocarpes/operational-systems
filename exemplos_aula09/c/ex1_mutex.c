/*
exemplo com mutex

uma unica thread acessa a regiao critica por vez.
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREADS		30

sem_t mutex;

void *task(void *arg){
	int item, tid, i;

	tid = (int)(long int)arg;
	while(1){
		sem_wait(&mutex);
		printf("thread %d entrando na regiao critica..\n", tid);
		usleep(100000);
		printf("thread %d saindo da regiao critica..\n", tid);
		sem_post(&mutex);
		usleep(100000);
	}
}

int main(void){
	long int i;
	pthread_t threads[THREADS];
	
	sem_init(&mutex,0,1);

	for(i = 0; i < THREADS; i++)
		pthread_create(&threads[i], NULL, task, (void *)i);

	pthread_exit(NULL);	
	return(0);
}

