
#include <stdio.h>
#include <windows.h>

#define THREADS 3
#define ITERATIONS 5

int counter = 0;
HANDLE mutex;

DWORD WINAPI incrementCounter(LPVOID arg)
{
    int i;

    for (i = 0; i < ITERATIONS; i++)
    {
        WaitForSingleObject(mutex, INFINITE);

        counter++;
        printf("Thread %d: Counter = %d\n",
               GetCurrentThreadId(), counter);

        ReleaseMutex(mutex);
        Sleep(50);
    }

    return 0;
}

int main()
{
    HANDLE threads[THREADS];
    int i;

    mutex = CreateMutex(NULL, FALSE, NULL);

    if (mutex == NULL)
    {
        printf("Mutex creation failed.\n");
        return 1;
    }

    for (i = 0; i < THREADS; i++)
    {
        threads[i] = CreateThread(
            NULL, 0, incrementCounter, NULL, 0, NULL
        );

        if (threads[i] == NULL)
        {
            printf("Thread creation failed.\n");
            CloseHandle(mutex);
            return 1;
        }
    }

    WaitForMultipleObjects(THREADS, threads, TRUE, INFINITE);

    printf("\nFinal Counter Value = %d\n", counter);

    for (i = 0; i < THREADS; i++)
        CloseHandle(threads[i]);

    CloseHandle(mutex);

    return 0;
}

