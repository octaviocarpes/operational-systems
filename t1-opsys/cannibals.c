#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  int cannibals;
  int meats;
} data;

int TABLE;
pthread_mutex_t lock;
data problemData = {
  .cannibals = 0,
  .meats = 0
};

void *
cook_thread(void *argument) {
  int meatsToCook = *(int *)argument;
  printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
  printf("I am the Cook!!! Zug Zug! \\o/\n");
  printf("Cooking da dinner!!!\n");
  for (int i = 1; i <= meatsToCook; i++)
  {
    TABLE++;
    printf("Cooked %d pieces... (Table size: %d)\n", i, TABLE);
    sleep(1);
  }
  printf("\n\n*JOB DONE!*\n\n");
  printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
  pthread_exit(NULL);
}

void *
cannibals_thread(void *argument)
{
  pthread_mutex_lock(&lock);

  int cannibal = *(int *)argument;
  printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
  printf("I am Cannibal %d!", cannibal);

  if (TABLE == 0) {
    // wake up cook
    printf("\nCannibal %d: COOOOK! WAKE UP! There is no FOOD! >:(\n", cannibal);
    pthread_t my_cook;
    pthread_create(&my_cook, NULL, cook_thread, &problemData.meats);
    pthread_join(my_cook, NULL);
  } else {
    // eat from table
    TABLE--;
    printf("\nCannibal %d eating... (Table size: %d)\n", cannibal, TABLE);
    printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
  }

  pthread_mutex_unlock(&lock);
  pthread_exit(NULL);
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

  pthread_t my_cannibals[problemData.cannibals];

  while(1) {
    for(int i = 1; i <= problemData.cannibals; i++ ) {
      pthread_create(&my_cannibals[i], NULL, cannibals_thread, &i);
      pthread_join(my_cannibals[i], NULL);
      sleep(1);
    }
  }

  return 0;
}