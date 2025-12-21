#include <iostream>
#include <Windows.h>
#include <ctime>


CRITICAL_SECTION cs;
const char* username = "User-672a41d6";
int nameLength = strlen(username);


void printInfo(char* stringname) {

	for (int i = 0; i < 90; i++) {

		if (i == 30) {
			EnterCriticalSection(&cs);
		}

		std::cout << stringname << username[(i) % nameLength] << " " << i << "\n";

		if (i == 60) {
			LeaveCriticalSection(&cs);
		}

		Sleep(100);

	}
}


int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hThread[3];
	DWORD Thread1, Thread2, Thread3;


	InitializeCriticalSection(&cs);


	hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)printInfo, (LPVOID)"A:", 0, &Thread1);

	if (hThread[0] == NULL) {
		std::cerr << "Не удалось создать поток A";
		ExitProcess(1);
	}


	hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)printInfo, (LPVOID)"B:", 0, &Thread2);

	if (hThread[1] == NULL) {
		std::cerr << "Не удалось создать поток B";
		CloseHandle(hThread[0]);
		ExitProcess(1);
	}

	hThread[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)printInfo, (LPVOID)"Main:", 0, &Thread1);

	if (hThread[2] == NULL) {
		std::cerr << "Не удалось создать поток Main";
		ExitProcess(1);
	}

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);


	DeleteCriticalSection(&cs);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);

	ExitProcess(0);
}