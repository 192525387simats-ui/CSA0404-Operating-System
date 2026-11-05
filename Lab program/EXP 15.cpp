
#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 10
#define LEN 30

char users[MAX_USERS][LEN];
char files[MAX_USERS][MAX_FILES][LEN];
int fileCount[MAX_USERS] = {0};
int userCount = 0;

int findUser(char name[])
{
    int i;
    for (i = 0; i < userCount; i++)
        if (strcmp(users[i], name) == 0)
            return i;

    return -1;
}

int main()
{
    char user[LEN], filename[LEN];
    int choice, u, i, j, found;

    while (1)
    {
        printf("\n--- Two-Level Directory ---\n");
        printf("1. Create User Directory\n");
        printf("2. Create File\n");
        printf("3. Search File\n");
        printf("4. Display Directory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (userCount == MAX_USERS)
                {
                    printf("Maximum users reached.\n");
                    break;
                }

                printf("Enter user name: ");
                scanf("%29s", user);

                if (findUser(user) != -1)
                    printf("User already exists.\n");
                else
                {
                    strcpy(users[userCount], user);
                    userCount++;
                    printf("User directory created.\n");
                }
                break;

            case 2:
                printf("Enter user name: ");
                scanf("%29s", user);

                u = findUser(user);

                if (u == -1)
                {
                    printf("User not found.\n");
                    break;
                }

                if (fileCount[u] == MAX_FILES)
                {
                    printf("Directory is full.\n");
                    break;
                }

                printf("Enter file name: ");
                scanf("%29s", filename);

                found = 0;
                for (i = 0; i < fileCount[u]; i++)
                    if (strcmp(files[u][i], filename) == 0)
                        found = 1;

                if (found)
                    printf("File already exists for this user.\n");
                else
                {
                    strcpy(files[u][fileCount[u]], filename);
                    fileCount[u]++;
                    printf("File created successfully.\n");
                }
                break;

            case 3:
                printf("Enter user name: ");
                scanf("%29s", user);

                u = findUser(user);

                if (u == -1)
                {
                    printf("User not found.\n");
                    break;
                }

                printf("Enter file name to search: ");
                scanf("%29s", filename);

                found = 0;
                for (i = 0; i < fileCount[u]; i++)
                    if (strcmp(files[u][i], filename) == 0)
                        found = 1;

                if (found)
                    printf("File found.\n");
                else
                    printf("File not found.\n");
                break;

            case 4:
                for (i = 0; i < userCount; i++)
                {
                    printf("\nUser: %s\n", users[i]);

                    for (j = 0; j < fileCount[i]; j++)
                        printf("  %s\n", files[i][j]);
                }
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

