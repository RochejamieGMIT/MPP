#include <stdio.h>

int sumnumbers(int n)
{
    int sum = 0;
    for(int i = 0; i<=n;i++)
        {
            sum += i;
            
        }
    return sum;
}

int main(void){

    int n = 0;
    int sum = 0;

    printf("Enter a number\n");
    scanf("%d",&n);
    int s = sumnumbers(n);
    

    printf("The sum of 1 to %d is %d",n,s);
}