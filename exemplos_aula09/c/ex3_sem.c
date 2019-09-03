#include <stdio.h>
/*
exemplo com semaforos

executar p1_rot2 somente depois de p0_rot1
*/

#include <pthread.h>
#include <semaphore.h>

sem_t sem;


void p0_rot1(void){
	printf("p0_rot1()\n");
}

void p0_rot2(void){
	printf("p0_rot2()\n");
}

void p1_rot1(void){
	printf("p1_rot1()\n");
}

void p1_rot2(void){
	printf("p1_rot2()\n");
}


void *task0(void *arg){
	p0_rot1();
	sem_post(&sem);
	p0_rot2();
}

void *task1(void *arg){
	p1_rot1();
	sem_wait(&sem);
	p1_rot2();
}

int main(void){
	long int i;
	pthread_t thread0, thread1;
	
	sem_init(&sem,0,0);

	pthread_create(&thread0, NULL, task0, NULL);
	pthread_create(&thread1, NULL, task1, NULL);

	pthread_exit(NULL);	
	return(0);
}

