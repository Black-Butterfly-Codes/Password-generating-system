#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    int total;

    printf("Welcome to the Password Generator\n");

    printf("How many accounts do you want to create? ");
    scanf("%d", &total);

    getchar(); // consume newline left by scanf

    srand(time(NULL));

    for(int j = 0; j < total; j++)
    {
        int num;
        char account[50];

        printf("\n==============================\n");
        printf("Account %d\n", j + 1);
        printf("==============================\n");

        printf("Enter account name: ");
        fgets(account, sizeof(account), stdin);

        account[strcspn(account, "\n")] = '\0';

        printf("Enter the length of the password: ");
        scanf("%d", &num);

        getchar(); // consume newline

        if(num <= 0)
        {
            printf("Invalid password length.\n");
            continue;
        }

        char characters[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "!@#$%^&*()-_=+[]{};:,.<>?/";

        int size = sizeof(characters) - 1;

        char password[num + 1];

        for(int i = 0; i < num; i++)
        {
            password[i] = characters[rand() % size];
        }

        password[num] = '\0';

        printf("\nGenerated Password: %s\n", password);
        printf("Assigned To: %s\n", account);
    }

    return 0;
}