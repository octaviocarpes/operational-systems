#include <stdio.h>
/*
exemplo com semaforos

no maximo 3 threads estao acessando o recurso ao mesmo tempo.
*/

#include <pthread.h>
#include <semaphore.h>

#define THREADS		10

sem_t sem;
int r = 0;

void *task(void *arg){
	int item, tid, i;

	tid = (int)(long int)arg;
	while(1){
		sem_wait(&sem);
		r++;
		printf("thread %d acessando recurso.. (%d)\n", tid, r);
		usleep(100000);
		printf("thread %d liberando recurso.. (%d)\n", tid, r);
		r--;
		sem_post(&sem);
		usleep(100000 * THREADS);
	}
}

int main(void){
	long int i;
	pthread_t threads[THREADS];
	
	sem_init(&sem,0,3);

	for(i = 0; i < THREADS; i++)
		pthread_create(&threads[i], NULL, task, (void *)i);

	pthread_exit(NULL);
	return(0);
}

