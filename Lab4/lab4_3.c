#include <stdio.h>

void main() {
	int input1;
	int input2;
	int input3;
	scanf("%d %d %d", &input1, &input2, &input3);

	int bottom=1;
	for (int i = 0; i < input2; i++) {
		bottom = bottom * 10;
	}

	int top=1;
	for (int i = 0; i < input3; i++) {
		top = top * 10;
	}
	
	printf("%d\n", (input1/bottom)%top);
}
