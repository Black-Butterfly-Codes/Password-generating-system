#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int num;

    printf("Welcome to the Password Generator\n");
    printf("Enter the length of the password: ");
    scanf("%d", &num);

    if(num <= 0)
    {
        printf("Invalid password length.\n");

    }

    char digits[] = "0123456789";
    char password[num + 1];

    srand(time(NULL));

    for(int i = 0; i < num; i++)
    {
        password[i] = digits[rand() % 10];
    }

    password[num] = '\0';

    printf("Generated Password: %s\n", password);

    return 0;
}
