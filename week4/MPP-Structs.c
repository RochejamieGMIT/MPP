#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee {
    char name[50];
    int age;
    float salary;
    int earsWorked;
    char jobTitle[50];
};

struct Module {
    char name[50];
    int credit;
};


struct Student {
    char name[50];
    int age;
    struct Module modules [10];
    int ModNum;
};


struct Manager {
    char name[50];
    int age;
    float salary;
   struct Employee Employee [10];
};

void printStudent ( struct Student s){
printf ("the Student name is %s\n", s.name);
printf ("the Student age is %i\n", s.age);
printf ("the number of modules the student takes is %i\n", s.ModNum);
//printf ("the Student name is %s\n", s.name);
}

void printModules ( struct Student Jamie ){
int n = 0;
while (n<Jamie.ModNum){
    printf ("%s's Module %d: %s\n",Jamie.name,n + 1,Jamie.modules[n].name);
    n++;
}
}

int main ( void )
{   
struct Module module1 = { "Multi - paradigm Programming " };
struct Module module2 = { "Introduction to Programming " };
struct Module module3 = { "Data Rep" };
struct Module module4 = { "Machine Learning" };
struct Module module5 = { "Data Analysis" };
struct Module module6 = { "Data Fundamentals" };


//printModule ( module1 );

struct Student Jamie = {"Jamie"};

Jamie.modules [0] = module1 ;
Jamie.ModNum = Jamie.ModNum+1;
Jamie.modules [1] = module2 ;
Jamie.ModNum = Jamie.ModNum+1;
Jamie.modules [2] = module3 ;
Jamie.ModNum = Jamie.ModNum+1;
Jamie.age = 28;

printStudent (Jamie) ;
printModules (Jamie) ;



return 0;
}
