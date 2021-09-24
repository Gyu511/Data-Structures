#include<stdio.h>
#include<string.h>

struct {
    char name[50];
    int age;
    char sex;   
    char* namep;
    char* namep2;
} student;


int main()
{

    while (1) {
        
        printf("Name : ");
        gets(student.name);
        if (!strcmp(student.name, "stop"))
            break;

        student.namep = strtok(student.name, " ");
        student.namep2 = strtok(NULL, " ");

        printf("Age : ");
        scanf("%d", &student.age);

        printf("Sex(M/F) : ");
        scanf(" %c", &student.sex);
        getchar();

        printf("Your name is %s %s, your age is %d, your sex is %c\n", student.namep2, student.namep, student.age, student.sex);
    }
    return 0;
}