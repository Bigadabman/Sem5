#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    DWORD pid = GetCurrentProcessId();
    printf("Текущий процесс PID = %lu\n", pid);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Ошибка создания снимка потоков. Код ошибки: %lu\n", GetLastError());
        ExitProcess(1);
    }

    THREADENTRY32 te32;
    te32.dwSize = sizeof(THREADENTRY32);

    if (Thread32First(hSnapshot, &te32))
    {
        do
        {
            if (te32.th32OwnerProcessID == pid)
            {
                printf("TID: %lu\n", te32.th32ThreadID);
            }
        } while (Thread32Next(hSnapshot, &te32));
    }
    else
    {
        fprintf(stderr, "Ошибка перебора потоков. Код ошибки: %lu\n", GetLastError());
        CloseHandle(hSnapshot);
        ExitProcess(1);
    }

    CloseHandle(hSnapshot);

    ExitProcess(0);
}
