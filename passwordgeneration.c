#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
void createPassword();
void viewPasswords();
void searchAccount();
void modifyPassword();
void deletePassword();
void checkPasswordStrength(char password[]);
int duplicatePassword(char password[]);
unsigned long generateHash(char *str);

unsigned long generateHash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}


void createPassword()
{
    char account[50];
    char password[200];

    printf("\nEnter account name: ");
    getchar();

    fgets(account, sizeof(account), stdin);
    account[strcspn(account, "\n")] = '\0';

    if(strlen(account) == 0)
    {
        printf("Account name cannot be empty.\n");
        return;
    }

    /*
       Check whether the account already exists.
       We will make this check more complete when
       we build the duplicate-account function.
    */

    int createChoice;

    printf("\n1. Generate Password\n");
    printf("2. Enter Password Manually\n");
    printf("Enter choice: ");

    scanf("%d", &createChoice);
    getchar();

    if(createChoice == 1)
    {
        int length;

        printf("Enter password length: ");
        scanf("%d", &length);
        getchar();

        if(length <= 0 || length >= sizeof(password))
        {
            printf("Invalid password length.\n");
            return;
        }

        char characters[] =
            "0123456789"
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "!@#$%^&*()-_=+[]{};:,.<>?/";

        int size = strlen(characters);

        for(int i = 0; i < length; i++)
        {
            password[i] = characters[rand() % size];
        }

        password[length] = '\0';
    }
    else if(createChoice == 2)
    {
        printf("Enter password: ");

        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        if(strlen(password) == 0)
        {
            printf("Password cannot be empty.\n");
            return;
        }
    }
    else
    {
        printf("Invalid choice.\n");
        return;
    }

    /*
       Check whether this password is already used.
    */

    if(!duplicatePassword(password))
    {
        printf("\nPassword was not saved.\n");
        return;
    }

    unsigned long hashID = generateHash(account);

    printf("\n=========================================\n");
    printf("          PASSWORD CREATED\n");
    printf("=========================================\n");

    printf("Account    : %s\n", account);
    printf("Hash ID    : %lu\n", hashID);
    printf("Password   : %s\n", password);

    /*
       Check password strength.
    */

    checkPasswordStrength(password);

    /*
       Save to file.

       Format:
       account|hashID|password
    */

    FILE *fp = fopen("passwords.txt", "a");

    if(fp == NULL)
    {
        printf("Error opening passwords.txt\n");
        return;
    }

    fprintf(fp, "%s|%lu|%s\n",
            account,
            hashID,
            password);

    fclose(fp);

    printf("\nPassword saved successfully!\n");
}

void viewPasswords()
{
    FILE *fp = fopen("passwords.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo saved passwords found.\n");
        return;
    }

    char line[300];

    char account[50];
    char hashID[50];
    char password[200];

    int count = 0;

    printf("\n=========================================\n");
    printf("          SAVED PASSWORDS\n");
    printf("=========================================\n");

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        /*
           Read:
           account|hashID|password
        */

        if(sscanf(line,
                  "%49[^|]|%49[^|]|%199[^\n]",
                  account,
                  hashID,
                  password) == 3)
        {
            printf("\nAccount  : %s\n", account);
            printf("Hash ID  : %s\n", hashID);
            printf("Password : %s\n", password);

            printf("-----------------------------------------\n");

            count++;
        }
    }

    if(count == 0)
    {
        printf("No saved passwords found.\n");
    }

    printf("=========================================\n");

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

    char line[300];
    char account[50];
    char hashID[50];
    char password[200];

    int found = 0;

    printf("\nEnter account name to search: ");
    getchar();

    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        /*
           Read:
           account|hashID|password
        */

        if(sscanf(line,
                  "%49[^|]|%49[^|]|%199[^\n]",
                  account,
                  hashID,
                  password) == 3)
        {
            if(strcmp(account, search) == 0)
            {
                printf("\n=========================================\n");
                printf("          ACCOUNT FOUND\n");
                printf("=========================================\n");

                printf("Account  : %s\n", account);
                printf("Hash ID  : %s\n", hashID);
                printf("Password : %s\n", password);

                printf("=========================================\n");

                found = 1;
                break;
            }
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("\nAccount not found.\n");
    }
}

void checkPasswordStrength(char password[])
{
    int length = strlen(password);

    int upper = 0;
    int lower = 0;
    int digit = 0;
    int special = 0;
    int score = 0;

    for(int i = 0; i < length; i++)
    {
        if(isupper((unsigned char)password[i]))
        {
            upper = 1;
        }
        else if(islower((unsigned char)password[i]))
        {
            lower = 1;
        }
        else if(isdigit((unsigned char)password[i]))
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

    printf("\n=========================================\n");

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
    {
        printf("- Excellent! Your password follows all recommended practices.\n");
    }

    printf("=========================================\n");
}
int duplicatePassword(char password[])
{
    FILE *fp = fopen("passwords.txt", "r");

    /* No file means there are no existing passwords */
    if(fp == NULL)
    {
        return 1;
    }

    char line[300];
    char account[50];
    char hashID[50];
    char savedPassword[200];

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        /*
            Read:

            account|hashID|password
        */

        if(sscanf(line,
                  "%49[^|]|%49[^|]|%199[^\n]",
                  account,
                  hashID,
                  savedPassword) == 3)
        {
            if(strcmp(savedPassword, password) == 0)
            {
                int choice;

                printf("\n=========================================\n");
                printf("                 WARNING\n");
                printf("=========================================\n");

                printf("This password is already used by another account.\n\n");

                printf("Used by account : %s\n", account);

                printf("\nDo you still want to use it?\n");
                printf("1. Yes\n");
                printf("2. No\n");
                printf("Enter your choice: ");

                scanf("%d", &choice);
                getchar();

                fclose(fp);

                if(choice == 1)
                {
                    return 1;
                }
                else if(choice == 2)
                {
                    return 0;
                }
                else
                {
                    printf("\nInvalid choice.\n");
                    return 0;
                }
            }
        }
    }

    fclose(fp);

    /*
       Password was not found.
       It is safe to use.
    */

    return 1;
}

void modifyPassword()
{
    FILE *fp = fopen("passwords.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if(fp == NULL)
    {
        printf("\nNo saved passwords found.\n");
        return;
    }

    if(temp == NULL)
    {
        printf("\nError creating temporary file.\n");
        fclose(fp);
        return;
    }

    char searchHash[50];

    char line[300];
    char account[50];
    char hashID[50];
    char savedPassword[200];

    int found = 0;

    printf("\nEnter Hash ID of account to modify: ");
    scanf("%49s", searchHash);
    getchar();

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        if(sscanf(line,
                  "%49[^|]|%49[^|]|%199[^\n]",
                  account,
                  hashID,
                  savedPassword) != 3)
        {
            /*
               If the line is invalid, preserve it.
            */
            fputs(line, temp);
            continue;
        }

        if(strcmp(hashID, searchHash) == 0)
        {
            found = 1;

            int choice;
            char newPassword[200];

            printf("\n=========================================\n");
            printf("          ACCOUNT FOUND\n");
            printf("=========================================\n");

            printf("Account  : %s\n", account);
            printf("Hash ID  : %s\n", hashID);

            printf("\n1. Generate New Password\n");
            printf("2. Enter Password Manually\n");
            printf("3. Cancel\n");
            printf("Enter your choice: ");

            scanf("%d", &choice);
            getchar();

            if(choice == 1)
            {
                int length;

                printf("\nEnter new password length: ");
                scanf("%d", &length);
                getchar();

                if(length <= 0 || length >= sizeof(newPassword))
                {
                    printf("\nInvalid password length.\n");

                    fprintf(temp,
                            "%s|%s|%s\n",
                            account,
                            hashID,
                            savedPassword);

                    continue;
                }

                char characters[] =
                    "0123456789"
                    "abcdefghijklmnopqrstuvwxyz"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "!@#$%^&*()-_=+[]{};:,.<>?/";

                int size = strlen(characters);

                for(int i = 0; i < length; i++)
                {
                    newPassword[i] =
                        characters[rand() % size];
                }

                newPassword[length] = '\0';
            }
            else if(choice == 2)
            {
                printf("\nEnter new password: ");

                fgets(newPassword,
                      sizeof(newPassword),
                      stdin);

                newPassword[strcspn(newPassword, "\n")] = '\0';

                if(strlen(newPassword) == 0)
                {
                    printf("\nPassword cannot be empty.\n");

                    fprintf(temp,
                            "%s|%s|%s\n",
                            account,
                            hashID,
                            savedPassword);

                    continue;
                }
            }
            else if(choice == 3)
            {
                printf("\nModification cancelled.\n");

                fprintf(temp,
                        "%s|%s|%s\n",
                        account,
                        hashID,
                        savedPassword);

                continue;
            }
            else
            {
                printf("\nInvalid choice.\n");

                fprintf(temp,
                        "%s|%s|%s\n",
                        account,
                        hashID,
                        savedPassword);

                continue;
            }

            /*
               Check whether the new password
               is already used.
            */

            if(strcmp(newPassword, savedPassword) != 0)
            {
                if(!duplicatePassword(newPassword))
                {
                    printf("\nPassword was not changed.\n");

                    fprintf(temp,
                            "%s|%s|%s\n",
                            account,
                            hashID,
                            savedPassword);

                    continue;
                }
            }

            printf("\nNew Password : %s\n", newPassword);

            checkPasswordStrength(newPassword);

            fprintf(temp,
                    "%s|%s|%s\n",
                    account,
                    hashID,
                    newPassword);

            printf("\nPassword updated successfully!\n");
        }
        else
        {
            /*
               Copy all other accounts unchanged.
            */

            fprintf(temp,
                    "%s|%s|%s\n",
                    account,
                    hashID,
                    savedPassword);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("passwords.txt");
    rename("temp.txt", "passwords.txt");

    if(!found)
    {
        printf("\nAccount with Hash ID '%s' not found.\n",
               searchHash);
    }
}
void deletePassword()
{
    FILE *fp = fopen("passwords.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if(fp == NULL)
    {
        printf("\nNo saved passwords found.\n");
        return;
    }

    if(temp == NULL)
    {
        printf("\nError creating temporary file.\n");
        fclose(fp);
        return;
    }

    char searchHash[50];

    char line[300];
    char account[50];
    char hashID[50];
    char password[200];

    int found = 0;
    int deleted = 0;

    printf("\nEnter Hash ID of account to delete: ");
    scanf("%49s", searchHash);
    getchar();

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        if(sscanf(line,
                  "%49[^|]|%49[^|]|%199[^\n]",
                  account,
                  hashID,
                  password) != 3)
        {
            /* Keep invalid lines unchanged */
            fputs(line, temp);
            continue;
        }

        if(strcmp(hashID, searchHash) == 0)
        {
            found = 1;

            printf("\n=========================================\n");
            printf("          ACCOUNT FOUND\n");
            printf("=========================================\n");

            printf("Account  : %s\n", account);
            printf("Hash ID  : %s\n", hashID);
            printf("Password : %s\n", password);

            printf("=========================================\n");

            int choice;

            printf("\nAre you sure you want to delete this account?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            printf("Enter your choice: ");

            scanf("%d", &choice);
            getchar();

            if(choice == 1)
            {
                printf("\nAccount deleted successfully!\n");
                deleted = 1;

                /* Do NOT write this account to temp.txt */
                continue;
            }
            else
            {
                printf("\nDeletion cancelled.\n");

                fprintf(temp,
                        "%s|%s|%s\n",
                        account,
                        hashID,
                        password);
            }
        }
        else
        {
            /*
               Copy all other accounts unchanged.
            */

            fprintf(temp,
                    "%s|%s|%s\n",
                    account,
                    hashID,
                    password);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("passwords.txt");
    rename("temp.txt", "passwords.txt");

    if(!found)
    {
        printf("\nAccount with Hash ID '%s' not found.\n",
               searchHash);
    }
    else if(!deleted)
    {
        printf("\nAccount was not deleted.\n");
    }
}

int main() {

    int choice;
    srand(time(NULL));

    do {
        printf("\n==================================\n");
        printf("   SECURE PASSWORD MANAGER (v2)\n");
        printf("==================================\n");
        printf("1. Create New Password\n");
        printf("2. View All Saved Passwords\n");
        printf("3. Search Account (by Name)\n");
        printf("4. Modify Password (via Hash ID)\n");
        printf("5. Delete Password (via Hash ID)\n");
        printf("6. Exit\n");
        printf("==================================\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1: createPassword(); break;
            case 2: viewPasswords(); break;
            case 3: searchAccount(); break;
            case 4: modifyPassword(); break;
            case 5: deletePassword(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
