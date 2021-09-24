#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int main()
{
    struct{
        char name[50];
        int age;
        char sex;
        char* namep;
    }student;

    int i = 0;
    while (1) {
        printf("provide your personal information:\n\n");
        printf("Name : ");
        gets(student.name);
        if (strcmp(student.name, "stop") == 0) {
            break;
        }
        student.namep = student.name;
        char name1[50];
        int i = 0, k = 0;
        while (*(student.namep + i) != ' ') {
            name1[i] = *(student.namep + i);
            i++;
        }
        name1[i] = '\0';
        i++;
        
        printf("Age : ");
        scanf("%d", &student.age);
        getchar();
        printf("Sex(M/F) : ");
        scanf("%c", &student.sex);
        getchar();
        printf("\nYour name is %s %s, your age is %d, your sex is %c.\n\n", student.namep+i, name1, student.age, student.sex);
    }

    return 0;
}