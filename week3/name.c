#include <stdio.h>

int main(void){
    char name[20];
    printf("Whats name?");

    fgets(name,20,stdin);

    printf("Hello %s", name);


}