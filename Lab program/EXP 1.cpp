
#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char command[] = "cmd.exe /c echo Child process created";

    if (!CreateProcess(
        NULL, command, NULL, NULL, FALSE, 0,
        NULL, NULL, &si, &pi)) {
        printf("Process creation failed\n");
        return 1;
    }

    printf("Parent Process ID: %lu\n",
           (unsigned long)GetCurrentProcessId());

    printf("Child Process ID: %lu\n",
           (unsigned long)pi.dwProcessId);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

