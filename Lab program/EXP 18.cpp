
#include <stdio.h>
#include <windows.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;
int count = 0;

HANDLE mutex;
HANDLE emptySlots;
HANDLE fullSlots;

DWORD WINAPI producer(LPVOID arg)
{
    int item;

    for (item = 1; item <= 5; item++)
    {
        WaitForSingleObject(emptySlots, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % SIZE;
        count++;

        ReleaseMutex(mutex);
        ReleaseSemaphore(fullSlots, 1, NULL);

        Sleep(100);
    }

    return 0;
}

DWORD WINAPI consumer(LPVOID arg)
{
    int item, i;

    for (i = 1; i <= 5; i++)
    {
        WaitForSingleObject(fullSlots, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % SIZE;
        count--;

        ReleaseMutex(mutex);
        ReleaseSemaphore(emptySlots, 1, NULL);

        Sleep(150);
    }

    return 0;
}

int main()
{
    HANDLE pThread, cThread;

    mutex = CreateMutex(NULL, FALSE, NULL);
    emptySlots = CreateSemaphore(NULL, SIZE, SIZE, NULL);
    fullSlots = CreateSemaphore(NULL, 0, SIZE, NULL);

    if (mutex == NULL || emptySlots == NULL || fullSlots == NULL)
    {
        printf("Synchronization object creation failed.\n");
        return 1;
    }

    pThread = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    cThread = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    if (pThread == NULL || cThread == NULL)
    {
        printf("Thread creation failed.\n");
        return 1;
    }

    WaitForSingleObject(pThread, INFINITE);
    WaitForSingleObject(cThread, INFINITE);

    CloseHandle(pThread);
    CloseHandle(cThread);
    CloseHandle(mutex);
    CloseHandle(emptySlots);
    CloseHandle(fullSlots);

    printf("Producer-Consumer execution completed.\n");

    return 0;
}

