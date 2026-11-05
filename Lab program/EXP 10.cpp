
#include <stdio.h>
#include <windows.h>
#include <string.h>

#define BUFFER_SIZE 256

int main()
{
    HANDLE hMapFile;
    HANDLE hEvent;
    char *sharedMemory;
    const char *message = "Hello from Message Queue!";
    
    hMapFile = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        BUFFER_SIZE,
        "MessageQueueMemory"
    );

    if (hMapFile == NULL)
    {
        printf("Error creating message storage.\n");
        return 1;
    }

    sharedMemory = (char *)MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        BUFFER_SIZE
    );

    if (sharedMemory == NULL)
    {
        printf("Error accessing message storage.\n");
        CloseHandle(hMapFile);
        return 1;
    }

    hEvent = CreateEventA(
        NULL,
        TRUE,
        FALSE,
        "MessageQueueEvent"
    );

    if (hEvent == NULL)
    {
        printf("Error creating event.\n");
        UnmapViewOfFile(sharedMemory);
        CloseHandle(hMapFile);
        return 1;
    }

    strcpy(sharedMemory, message);
    SetEvent(hEvent);

    if (WaitForSingleObject(hEvent, 1000) == WAIT_OBJECT_0)
    {
        printf("Message received: %s\n", sharedMemory);
    }

    CloseHandle(hEvent);
    UnmapViewOfFile(sharedMemory);
    CloseHandle(hMapFile);

    return 0;
}

