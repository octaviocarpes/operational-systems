#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  int cannibals;
  int meats;
} data;

int TABLE;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int play = 0;
data problemData = {
  .cannibals = 0,
  .meats = 0
};

void *
cook_thread(void *argument) {
  int meatsToCook = *(int *)argument;
  printf("\n\n-------------------------\n\n");
  printf("I am the Cook!!!\\o/\n");
  printf("\n-------------------------\n\n");
  while(1) {
    if (TABLE == 0) {
      pthread_mutex_lock(&lock);
      printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
      printf("Cook: Time to Cook! \\o/\n");
      for (int i = 1; i <= problemData.meats; i++)
      {
        TABLE = i;
        printf("Cooking %d pieces of meat...(Table Size: %d)\n", i, TABLE);
      }
      printf("Job Done! Da table is fuul! \\o/\n");
      printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
      pthread_mutex_unlock(&lock);
    }
    sleep(3);
  }
}

void *
cannibals_thread(void *argument)
{
  int cannibal = *(int *)argument;
  while(1) {
    printf("I am Cannibal %d\n", cannibal);
    if (TABLE > 0) {
      printf("Cannibal: %d eats....(Table Size: %d)\n\n", cannibal, TABLE);
      TABLE--;
    } else if(TABLE == 0) {
      printf("Cannibal %d: COOOK! Wake up! There is no food! >:(\n\n", cannibal);
    }
    sleep(2);
  }
}

int main(int argc, char *argv[]) {
  int cannibals = atoi(argv[1]);
  int meats = atoi(argv[2]);
  TABLE = meats;

  problemData.cannibals = cannibals;
  problemData.meats = meats;

  printf("Cannibals: %d\n", problemData.cannibals);
  printf("Meats: %d\n", problemData.meats);
  printf("\n");

  pthread_t my_cannibals[problemData.cannibals], my_cook;

  pthread_create(&my_cook, NULL, cook_thread, &problemData.meats);

  for(int i = 0; i < problemData.cannibals; i++ ) {
    pthread_create(&my_cannibals[i], NULL, cannibals_thread, &i);
  }
  for(int j = 0; j < problemData.cannibals; j++ ) {
    pthread_join(my_cannibals[j], NULL);
  }
  pthread_join(my_cook, NULL);

  return 0;
}