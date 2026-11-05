
#include <stdio.h>
#include <windows.h>

#define READERS 3

int sharedData = 100;
int readerCount = 0;

HANDLE mutex;
HANDLE writeLock;

DWORD WINAPI reader(LPVOID arg)
{
    int id = *(int *)arg;

    WaitForSingleObject(mutex, INFINITE);
    readerCount++;

    if (readerCount == 1)
        WaitForSingleObject(writeLock, INFINITE);

    ReleaseMutex(mutex);

    printf("Reader %d is reading data: %d\n", id, sharedData);

    WaitForSingleObject(mutex, INFINITE);
    readerCount--;

    if (readerCount == 0)
        ReleaseMutex(writeLock);

    ReleaseMutex(mutex);

    return 0;
}

DWORD WINAPI writer(LPVOID arg)
{
    int id = *(int *)arg;

    WaitForSingleObject(writeLock, INFINITE);

    sharedData += 10;
    printf("Writer %d updated data to: %d\n", id, sharedData);

    ReleaseMutex(writeLock);

    return 0;
}

int main()
{
    HANDLE threads[4];
    int ids[4] = {1, 2, 3, 1};
    int i;

    mutex = CreateMutex(NULL, FALSE, NULL);
    writeLock = CreateMutex(NULL, FALSE, NULL);

    if (mutex == NULL || writeLock == NULL)
    {
        printf("Mutex creation failed.\n");
        return 1;
    }

    for (i = 0; i < 3; i++)
        threads[i] = CreateThread(
            NULL, 0, reader, &ids[i], 0, NULL
        );

    threads[3] = CreateThread(
        NULL, 0, writer, &ids[3], 0, NULL
    );

    WaitForMultipleObjects(4, threads, TRUE, INFINITE);

    printf("Final shared data: %d\n", sharedData);

    for (i = 0; i < 4; i++)
        CloseHandle(threads[i]);

    CloseHandle(mutex);
    CloseHandle(writeLock);

    return 0;
}

