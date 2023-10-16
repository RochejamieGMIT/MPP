#include <stdio.h>
#include <string.h>

int main(void){
    char name[20];
    printf("Whats name?");

    fgets(name,20,stdin);
    name[strcspn(name,"\n")] ='\0';

    if ((strcmp(name,"Alice") == 0) || (strcmp(name,"Bob") == 0))
    {
        printf("hello %s",name);

    }
    else{

        printf("Hello Buddy");
    }


}