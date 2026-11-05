
#include <stdio.h>
#include <windows.h>

#define N 5

HANDLE forks[N];

DWORD WINAPI philosopher(LPVOID arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;

    printf("Philosopher %d is thinking.\n", id + 1);

    // Lock forks in a fixed order to avoid deadlock
    int first = left < right ? left : right;
    int second = left < right ? right : left;

    WaitForSingleObject(forks[first], INFINITE);
    WaitForSingleObject(forks[second], INFINITE);

    printf("Philosopher %d is eating.\n", id + 1);

    Sleep(500);

    ReleaseMutex(forks[second]);
    ReleaseMutex(forks[first]);

    printf("Philosopher %d finished eating.\n", id + 1);

    return 0;
}

int main()
{
    HANDLE threads[N];
    int ids[N];
    int i;

    for (i = 0; i < N; i++)
        forks[i] = CreateMutex(NULL, FALSE, NULL);

    for (i = 0; i < N; i++)
    {
        ids[i] = i;
        threads[i] = CreateThread(
            NULL, 0, philosopher, &ids[i], 0, NULL
        );
    }

    WaitForMultipleObjects(N, threads, TRUE, INFINITE);

    for (i = 0; i < N; i++)
    {
        CloseHandle(threads[i]);
        CloseHandle(forks[i]);
    }

    printf("All philosophers completed.\n");

    return 0;
}

