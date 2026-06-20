#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    int choice;

    srand(time(NULL));

    do
    {
        printf("\n==================================\n");
        printf("       PASSWORD MANAGER\n");
        printf("==================================\n");
        printf("1. Create New Password\n");
        printf("2. View Saved Passwords\n");
        printf("3. Search Account\n");
        printf("4. Modify Password\n");
        printf("5. Delete Password\n");
        printf("6. Exit\n");
        printf("==================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
           case 1:
{
    char account[50];
    char password[200];

    printf("\nEnter account name: ");
    fgets(account, sizeof(account), stdin);
    account[strcspn(account, "\n")] = '\0';

    int createChoice;

    printf("\n1. Generate Password\n");
    printf("2. Enter Password Manually\n");
    printf("Enter choice: ");
    scanf("%d", &createChoice);
    getchar();

    if(createChoice == 1)
    {
        int num;

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

        for(int i = 0; i < num; i++)
        {
            password[i] = characters[rand() % size];
        }

        password[num] = '\0';
    }
    else if(createChoice == 2)
    {
        printf("Enter password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
    }
    else
    {
        printf("Invalid choice.\n");
        break;
    }

    FILE *fp = fopen("passwords.txt", "a");

    if(fp == NULL)
    {
        printf("Error opening file.\n");
        break;
    }

    fprintf(fp, "%s | %s\n", account, password);

    fclose(fp);

    printf("\nPassword: %s\n", password);
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
    int count = 0;

    printf("\n========== SAVED PASSWORDS ==========\n");

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
        count++;
    }

    if(count == 0)
    {
        printf("No saved passwords found.\n");
    }

    printf("=====================================\n");

    fclose(fp);
    break;
}
            case 3:
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

          case 4:
{
    char search[50];
    char line[200];
    int found = 0;

    printf("\nEnter account name to modify: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

    FILE *fp = fopen("passwords.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if(fp == NULL || temp == NULL)
    {
        printf("Error opening file.\n");
        break;
    }

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        if(strstr(line, search) != NULL)
        {
            found = 1;

            int modifyChoice;

            printf("\n1. Generate New Password\n");
            printf("2. Enter Password Manually\n");
            printf("Enter choice: ");
            scanf("%d", &modifyChoice);
            getchar();

            char password[200];

            if(modifyChoice == 1)
            {
                int num;

                printf("Enter new password length: ");
                scanf("%d", &num);
                getchar();

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

                for(int i = 0; i < num; i++)
                {
                    password[i] = characters[rand() % size];
                }

                password[num] = '\0';
            }
            else if(modifyChoice == 2)
            {
                printf("Enter new password: ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = '\0';
            }
            else
            {
                printf("Invalid choice.\n");
                fputs(line, temp);
                continue;
            }

            fprintf(temp, "%s | %s\n", search, password);

            printf("\nNew Password: %s\n", password);
        }
        else
        {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("passwords.txt");
    rename("temp.txt", "passwords.txt");

    if(found)
    {
        printf("Password updated successfully!\n");
    }
    else
    {
        printf("Account not found.\n");
    }

    break;
}
            case 5:
            {
                char search[50];
                char line[200];
                int found = 0;

                printf("\nEnter account name to delete: ");
                fgets(search, sizeof(search), stdin);
                search[strcspn(search, "\n")] = '\0';

                FILE *fp = fopen("passwords.txt", "r");
                FILE *temp = fopen("temp.txt", "w");

                if(fp == NULL || temp == NULL)
                {
                    printf("Error opening file.\n");
                    break;
                }

                while(fgets(line, sizeof(line), fp) != NULL)
                {
                    if(strstr(line, search) != NULL)
                    {
                        found = 1;
                        printf("\nDeleted Entry:\n%s", line);
                        continue;
                    }

                    fputs(line, temp);
                }

                fclose(fp);
                fclose(temp);

                remove("passwords.txt");
                rename("temp.txt", "passwords.txt");

                if(found)
                {
                    printf("\nAccount deleted successfully!\n");
                }
                else
                {
                    printf("\nAccount not found.\n");
                }

                break;
            }

            case 6:
            {
                printf("\nThank you for using Password Manager.\n");
                break;
            }

            default:
            {
                printf("\nInvalid choice.\n");
            }
        }

    } while(choice != 6);

    return 0;
}
