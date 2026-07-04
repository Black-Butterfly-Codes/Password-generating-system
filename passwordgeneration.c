#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

void createPassword();
void viewPasswords();
void searchAccount();
void modifyPassword();
void deletePassword();
void checkPasswordStrength(char password[]);

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
                createPassword();
                break;

            case 2:
                viewPasswords();
                break;

            case 3:
                searchAccount();
                break;

            case 4:
                modifyPassword();
                break;

            case 5:
                deletePassword();
                break;

            case 6:
                printf("\nThank you for using Password Manager.\n");
                break;

            default:
                printf("\nInvalid choice.\n");
        }

    } while(choice != 6);

    return 0;
}
void createPassword()
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
            return;
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
        return;
    }

    printf("\nPassword : %s\n", password);

    checkPasswordStrength(password);

    FILE *fp = fopen("passwords.txt", "a");

    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(fp, "%s | %s\n", account, password);

    fclose(fp);

    printf("Assigned To : %s\n", account);
    printf("Password saved successfully!\n");
}
void viewPasswords()
{
    FILE *fp = fopen("passwords.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo saved passwords found.\n");
        return;
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
}

void searchAccount()
{
    FILE *fp = fopen("passwords.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo saved passwords found.\n");
        return;
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
}
void modifyPassword()
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

        if(fp != NULL)
            fclose(fp);

        if(temp != NULL)
            fclose(temp);

        return;
    }

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        if(strstr(line, search) != NULL)
        {
            found = 1;

            int modifyChoice;
            char password[200];

            printf("\n1. Generate New Password\n");
            printf("2. Enter Password Manually\n");
            printf("Enter choice: ");
            scanf("%d", &modifyChoice);
            getchar();

            if(modifyChoice == 1)
            {
                int num;

                printf("Enter new password length: ");
                scanf("%d", &num);
                getchar();

                if(num <= 0)
                {
                    printf("Invalid password length.\n");
                    fputs(line, temp);
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

            printf("\nNew Password : %s\n", password);

            checkPasswordStrength(password);

            fprintf(temp, "%s | %s\n", search, password);
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
        printf("\nPassword updated successfully!\n");
    }
    else
    {
        printf("\nAccount not found.\n");
    }
}
void deletePassword()
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

        if(fp != NULL)
            fclose(fp);

        if(temp != NULL)
            fclose(temp);

        return;
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
}
void checkPasswordStrength(char password[])
{
    int length;
    int upper = 0;
    int lower = 0;
    int digit = 0;
    int special = 0;
    int score = 0;

    length = strlen(password);

    for(int i = 0; i < length; i++)
    {
        if(isupper(password[i]))
        {
            upper = 1;
        }
        else if(islower(password[i]))
        {
            lower = 1;
        }
        else if(isdigit(password[i]))
        {
            digit = 1;
        }
        else
        {
            special = 1;
        }
    }

    if(length >= 8)
        score++;

    if(upper)
        score++;

    if(lower)
        score++;

    if(digit)
        score++;

    if(special)
        score++;

    printf("\n=========================================\n");
    printf("          PASSWORD ANALYSIS\n");
    printf("=========================================\n");

    printf("Length              : %d\n", length);
    printf("Uppercase Letters   : %s\n", upper ? "Yes" : "No");
    printf("Lowercase Letters   : %s\n", lower ? "Yes" : "No");
    printf("Numbers             : %s\n", digit ? "Yes" : "No");
    printf("Special Characters  : %s\n", special ? "Yes" : "No");

    printf("-----------------------------------------\n");

    if(score <= 2)
    {
        printf("Password Strength : VERY WEAK\n");
    }
    else if(score == 3)
    {
        printf("Password Strength : WEAK\n");
    }
    else if(score == 4)
    {
        printf("Password Strength : MEDIUM\n");
    }
    else
    {
        if(length >= 12)
            printf("Password Strength : VERY STRONG\n");
        else
            printf("Password Strength : STRONG\n");
    }

    printf("\nSuggestions:\n");

    if(length < 8)
        printf("- Use at least 8 characters.\n");

    if(!upper)
        printf("- Add at least one uppercase letter.\n");

    if(!lower)
        printf("- Add at least one lowercase letter.\n");

    if(!digit)
        printf("- Add at least one number.\n");

    if(!special)
        printf("- Add at least one special character.\n");

    if(score == 5 && length >= 12)
        printf("- Excellent! Your password follows all recommended practices.\n");

    printf("=========================================\n");
}
