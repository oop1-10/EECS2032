#include <stdio.h>

void main() {
  int l;
  int m;

  printf("How many rows?");
  scanf("%d", &m);
  printf("What is the left margin?");
  scanf("%d", &l);

  for (int i = 1; i <= m; i++) {
    for (int j = 0; j <= l-i; j++) {
      printf(" ");
    }
    for (int k = 0; k < i; k++) {
      printf("*");
    }
    printf("\n");
  }
}
