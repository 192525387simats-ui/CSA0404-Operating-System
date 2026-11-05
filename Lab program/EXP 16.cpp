
#include <stdio.h>

struct Employee
{
    int id;
    char name[30];
    float salary;
};

int main()
{
    FILE *fp;
    struct Employee e;
    int choice, id;
    long position;

    while (1)
    {
        printf("\n--- Employee Record System ---\n");
        printf("1. Add Employee\n");
        printf("2. Search Employee by ID\n");
        printf("3. Display All Employees\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                fp = fopen("employee.dat", "ab+");
                if (fp == NULL)
                {
                    printf("File error.\n");
                    return 1;
                }

                printf("Enter Employee ID: ");
                scanf("%d", &e.id);

                printf("Enter Employee Name: ");
                scanf("%29s", e.name);

                printf("Enter Salary: ");
                scanf("%f", &e.salary);

                fseek(fp, 0, SEEK_END);
                fwrite(&e, sizeof(e), 1, fp);
                fclose(fp);

                printf("Employee record added.\n");
                break;

            case 2:
                fp = fopen("employee.dat", "rb");
                if (fp == NULL)
                {
                    printf("No records found.\n");
                    break;
                }

                printf("Enter Employee ID to search: ");
                scanf("%d", &id);

                {
                    int found = 0;

                    while (fread(&e, sizeof(e), 1, fp) == 1)
                    {
                        if (e.id == id)
                        {
                            printf("\nID: %d\n", e.id);
                            printf("Name: %s\n", e.name);
                            printf("Salary: %.2f\n", e.salary);
                            found = 1;
                            break;
                        }
                    }

                    if (!found)
                        printf("Employee not found.\n");
                }

                fclose(fp);
                break;

            case 3:
                fp = fopen("employee.dat", "rb");
                if (fp == NULL)
                {
                    printf("No records found.\n");
                    break;
                }

                printf("\nID\tName\tSalary\n");

                while (fread(&e, sizeof(e), 1, fp) == 1)
                    printf("%d\t%s\t%.2f\n",
                           e.id, e.name, e.salary);

                fclose(fp);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}


