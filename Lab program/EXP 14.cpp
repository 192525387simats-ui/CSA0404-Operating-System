
#include <stdio.h>
#include <string.h>

#define MAX 20
#define LEN 30

int main()
{
    char files[MAX][LEN];
    char name[LEN];
    int count = 0, choice, i, found;

    while (1)
    {
        printf("\n--- Single-Level Directory ---\n");
        printf("1. Create File\n");
        printf("2. Search File\n");
        printf("3. Delete File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (count == MAX)
                {
                    printf("Directory is full.\n");
                    break;
                }

                printf("Enter file name: ");
                scanf("%29s", name);

                found = 0;
                for (i = 0; i < count; i++)
                {
                    if (strcmp(files[i], name) == 0)
                    {
                        found = 1;
                        break;
                    }
                }

                if (found)
                    printf("File already exists.\n");
                else
                {
                    strcpy(files[count], name);
                    count++;
                    printf("File created successfully.\n");
                }
                break;

            case 2:
                printf("Enter file name to search: ");
                scanf("%29s", name);

                found = 0;
                for (i = 0; i < count; i++)
                {
                    if (strcmp(files[i], name) == 0)
                    {
                        found = 1;
                        break;
                    }
                }

                if (found)
                    printf("File found.\n");
                else
                    printf("File not found.\n");
                break;

            case 3:
                printf("Enter file name to delete: ");
                scanf("%29s", name);

                found = 0;
                for (i = 0; i < count; i++)
                {
                    if (strcmp(files[i], name) == 0)
                    {
                        found = 1;

                        for (int j = i; j < count - 1; j++)
                            strcpy(files[j], files[j + 1]);

                        count--;
                        printf("File deleted successfully.\n");
                        break;
                    }
                }

                if (!found)
                    printf("File not found.\n");
                break;

            case 4:
                if (count == 0)
                    printf("Directory is empty.\n");
                else
                {
                    printf("\nFiles in Directory:\n");
                    for (i = 0; i < count; i++)
                        printf("%s\n", files[i]);
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

