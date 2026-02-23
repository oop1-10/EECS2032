#include <stdio.h>

void backwardsArray(int input[]) {
  for (int i = 0; i < 3; i++) {
    int temp = input[i];
    input[i] = input[5 - i];
    input[5 - i] = temp;
  }
}

void main() {
  int input[6];
  printf("Enter 6 integers: ");
  for (int i = 0; i < 6; i++) {
    scanf("%d", &input[i]);
  }

  backwardsArray(input);

  for (int i = 0; i < 6; i++) {
    printf("%d ", input[i]);
  }
  printf("\n");
}
