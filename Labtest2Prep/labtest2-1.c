#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void main() {
    char input[20];
    scanf("%s", input);

    int length = strlen(input);
    if (length < 6) {
        printf("Weak\n");
        return;
    }

    bool digit = false;
    bool upper = false;

    for (int i = 0; i < length; i++) {
        if (isdigit(input[i])) {
            digit = true;
        }
        if (isupper(input[i])) {
            upper = true;
        }
    }
    if (digit && upper) {
        printf("Strong\n");
    } else {
        printf("Weak\n");
    }
}