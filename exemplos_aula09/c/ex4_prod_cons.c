#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N		20
#define PRODUCERS	3
#define CONSUMERS	3

sem_t mutex, empty, full;
int in=0, out=0, buffer[N];

void *producer(void *arg){
	int item, tid;

	tid = (int)(long int)arg;
	while(1){
		item=random();
		sem_wait(&empty);			/* wait() ou p() ou down() */
		sem_wait(&mutex);			/* wait() ou p() ou down() ou lock() */
		buffer[in]=item;
		printf("produtor %d escrevendo na pos %d\n", tid, in);
		in=(in+1)%N;
		sem_post(&mutex);			/* post() ou v() ou up() ou signal() ou unlock() */
		sem_post(&full);			/* post() ou v() ou up() ou signal() */
	}
}

void *consumer(void *arg){
	int item, tid;

	tid = (int)(long int)arg;
	while(1){
		sem_wait(&full);			/* wait() ou p() ou down() */
		sem_wait(&mutex);			/* wait() ou p() ou down() */
		item=buffer[out];
		printf("consumidor %d retirando da pos %d\n", tid, out);
		out=(out+1)%N;
		sem_post(&mutex);			/* post() ou v() ou up() ou signal() */
		sem_post(&empty);			/* post() ou v() ou up() ou signal() */
		item=0;
	}
}

int main(void){
	long int i;
	pthread_t producers[PRODUCERS], consumers[CONSUMERS];
	
	sem_init(&mutex,0,1);
	sem_init(&empty,0,N);
	sem_init(&full,0,0);

	for(i = 0; i < PRODUCERS; i++)
		pthread_create(&producers[i], NULL, producer, (void *)i);
	for(i = 0; i < CONSUMERS; i++)
		pthread_create(&consumers[i], NULL, consumer, (void *)i);

	pthread_exit(NULL);	
	return(0);
}

