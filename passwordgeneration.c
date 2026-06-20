#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    int choice;

    do
    {
        printf("\n==================================\n");
        printf("       PASSWORD MANAGER\n");
        printf("==================================\n");
        printf("1. Create New Password\n");
        printf("2. View Saved Passwords\n");
        printf("3. Exit\n");
        printf("4. Search Account\n");
        printf("==================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
            {
                int num;
                char account[50];

                printf("\nEnter account name: ");
                fgets(account, sizeof(account), stdin);
                account[strcspn(account, "\n")] = '\0';

                printf("Enter password length: ");
                scanf("%d", &num);
                getchar();

                if(num <= 0)
                {
                    printf("Invalid password length.\n");
                    break;
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

                FILE *fp = fopen("passwords.txt", "a");

                if(fp == NULL)
                {
                    printf("Error opening file.\n");
                    break;
                }

                fprintf(fp, "%s | %s\n", account, password);

                fclose(fp);

                printf("\nGenerated Password: %s\n", password);
                printf("Assigned To: %s\n", account);
                printf("Password saved successfully!\n");

                break;
            }

            case 2:
            {
                FILE *fp = fopen("passwords.txt", "r");

                if(fp == NULL)
                {
                    printf("\nNo saved passwords found.\n");
                    break;
                }

                char line[200];

                printf("\n========== SAVED PASSWORDS ==========\n");

                while(fgets(line, sizeof(line), fp) != NULL)
                {
                    printf("%s", line);
                }

                printf("=====================================\n");

                fclose(fp);

                break;
            }

            case 3:
            {
                printf("\nThank you for using Password Manager.\n");
                break;
            }

            case 4:
            {
                FILE *fp = fopen("passwords.txt", "r");

                if(fp == NULL)
                {
                    printf("\nNo saved passwords found.\n");
                    break;
                }

                char search[50];
                char line[200];
                int found = 0;

                printf("\nEnter account name: ");
                fgets(search, sizeof(search), stdin);

                search[strcspn(search, "\n")] = '\0';

                while(fgets(line, sizeof(line), fp) != NULL)
                {
                    if(strstr(line, search) != NULL)
                    {
                        printf("\nFound:\n%s", line);
                        found = 1;
                    }
                }

                if(found == 0)
                {
                    printf("\nAccount not found.\n");
                }

                fclose(fp);

                break;
            }

            default:
            {
                printf("\nInvalid choice.\n");
            }
        }

    } while(choice != 3);

    return 0;
}
