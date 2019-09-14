#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
  int f1, f2;

  printf("Alo do pai\n");
  f1 = fork();
  f2 = fork();

  wait(f1);
  printf("Filho 1 Morreu\n");

  wait(f2);
  printf("Filho 2 Morreu\n");

  exit(1);
}
