
#include <stdio.h>
#include <windows.h>
#include <string.h>

int main()
{
    HANDLE hMapFile;
    char *sharedMemory;
    const char *message = "Hello from shared memory!";

    hMapFile = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        1024,
        "MySharedMemory"
    );

    if (hMapFile == NULL)
    {
        printf("Error creating shared memory.\n");
        return 1;
    }

    sharedMemory = (char *)MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        1024
    );

    if (sharedMemory == NULL)
    {
        printf("Error mapping shared memory.\n");
        CloseHandle(hMapFile);
        return 1;
    }

    strcpy(sharedMemory, message);

    printf("Message written to shared memory: %s\n",
           sharedMemory);

    UnmapViewOfFile(sharedMemory);
    CloseHandle(hMapFile);

    return 0;
}

