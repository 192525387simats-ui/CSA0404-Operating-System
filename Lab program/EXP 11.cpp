
#include <stdio.h>
#include <windows.h>

DWORD WINAPI threadFunction(LPVOID lpParam)
{
    int threadNumber = *(int *)lpParam;

    printf("Thread %d is executing.\n", threadNumber);

    return 0;
}

int main()
{
    HANDLE thread1, thread2;
    int n1 = 1, n2 = 2;

    thread1 = CreateThread(
        NULL, 0, threadFunction, &n1, 0, NULL
    );

    thread2 = CreateThread(
        NULL, 0, threadFunction, &n2, 0, NULL
    );

    if (thread1 == NULL || thread2 == NULL)
    {
        printf("Error creating thread.\n");
        return 1;
    }

    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    CloseHandle(thread1);
    CloseHandle(thread2);

    printf("Main thread completed.\n");

    return 0;
}

