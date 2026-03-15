#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct Employee {
    char id[20];
    double salary;
};

void increasePay(struct Employee *e, double amount) {
    e->salary += amount;
}

int main() {
    
    FILE *fp = fopen("emp.txt", "r");
    if (fp == NULL) {
        printf("Cannot open file");
        return 1;
    }

    struct Employee emp;
    fscanf(fp, "%s %lf", emp.id, &emp.salary);

    for (int i = 0; i < strlen(emp.id); i++) {
        if (emp.id[i] >= 'A' && emp.id[i] <= 'Z') {
            emp.id[i] = tolower(emp.id[i]);
        }
    }

    increasePay(&emp, 1000.0);
    printf("ID: %s\nSalary: %.2f\n", emp.id, emp.salary);

    fclose(fp);
    return 0;
}