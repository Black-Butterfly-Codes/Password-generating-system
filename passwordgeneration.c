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
        return 1;
    }

    char characters[] =
    "0123456789"
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "!@#$%^&*()-_=+[]{};:,.<>?/";

    int size = sizeof(characters) - 1;

    char password[num + 1];

    srand(time(NULL));

    for(int i = 0; i < num; i++)
    {
        password[i] = characters[rand() % size];
    }

    password[num] = '\0';

    printf("\nGenerated Password: %s\n", password);

    return 0;
}