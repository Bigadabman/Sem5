#include <stdio.h>
#include <windows.h>

int main()
{
    STARTUPINFOA si[2] = {};
    PROCESS_INFORMATION pi[2] = {};

    for (int i = 0; i < 2; ++i)
        si[i].cb = sizeof(STARTUPINFOA);

    char cmd1[] = "Lab-07x.exe 60";
    char cmd2[] = "Lab-07x.exe 120";

    if (!CreateProcessA(
        NULL,
        cmd1,
        NULL, NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL, NULL,
        &si[0],
        &pi[0]))
    {
        printf("Error creating first process. Error code: %lu\n", GetLastError());
        return 1;
    }

    if (!CreateProcessA(
        NULL,
        cmd2,
        NULL, NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL, NULL,
        &si[1],
        &pi[1]))
    {
        printf("Error creating second process. Error code: %lu\n", GetLastError());
        return 1;
    }

    HANDLE procs[2] = { pi[0].hProcess, pi[1].hProcess };

    printf("Waiting for child processes...\n");
    WaitForMultipleObjects(2, procs, TRUE, INFINITE);

    for (int i = 0; i < 2; ++i)
    {
        CloseHandle(pi[i].hThread);
        CloseHandle(pi[i].hProcess);
    }

    return 0;
}
