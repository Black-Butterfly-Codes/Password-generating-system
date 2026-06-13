#include<stdio.h>

int main()
{
    int num;

    printf("welcome to the password generator\n");
    printf("enter the length of the password how long you want it to be created -> ");
    scanf("%d",&num);

    if(num <= 0)
    {
        printf("Please enter a valid password length.\n");

    }

    printf("%d",num);

    return 0;
}
