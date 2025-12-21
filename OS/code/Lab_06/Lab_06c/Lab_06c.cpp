#include <iostream>
#include <Windows.h>
#include <semaphore>

const char* SemaphorName = "Global\\Semaphore";

const char* username = "User-672a41d6";
int nameLength = strlen(username);


void printInfo(const char* stringname) {


	HANDLE hSemaphore = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, SemaphorName);

	
	if (hSemaphore == NULL)
	{
		std::cerr << "Не удалось открыть мьютекс!\n";
		return;
	}


	for (int i = 0; i < 90; i++) {

		if (i == 30) {
			WaitForSingleObject(hSemaphore, INFINITE);
		}

		std::cout << stringname << " " <<  username[(i) % nameLength] << " " << i << "\n";

		if (i == 60) {
			ReleaseSemaphore(hSemaphore, 1, NULL);
		}
		Sleep(100);
	}
	CloseHandle(hSemaphore);
}


int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc != 2) {
		std::cerr << "Использование: Lab_06b.exe 0/1(Родительский/дочерний)\n";
		ExitProcess(1);
	}

	int mod = atoi(argv[1]);

	if (mod == 1) {
		printInfo("Child");
	}
	else if (mod == 0) {


		HANDLE hSemaphore = CreateSemaphoreA(NULL, 1, 1, SemaphorName);
		if (!hSemaphore)
		{
			std::cerr << "Не удалось создать семафор\n";
			ExitProcess(1);
		}


		STARTUPINFOA si[2] = { 0 };
		si[0].cb = sizeof(STARTUPINFO);
		si[1].cb = sizeof(STARTUPINFO);
		PROCESS_INFORMATION pi[2] = { 0 };

		char processName[] = "Lab_06c.exe 1";

		if (!CreateProcessA(NULL, processName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[0], &pi[0])) {
			std::cerr << "Не удалось создать процесс A";
			ExitProcess(1);
		}

		if (!CreateProcessA(NULL, processName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[1], &pi[1])) {
			std::cerr << "Не удалось создать процесс B";
			ExitProcess(1);
		}

		printInfo("Main");

		for (int i = 0; i < 2; i++) {
			WaitForSingleObject(pi[i].hProcess, INFINITE);
			CloseHandle(pi[i].hProcess);
			CloseHandle(pi[i].hThread);
		}

		CloseHandle(hSemaphore);
	}
	else {
		std::cerr << "Использование: Lab_06b.exe 0/1(Родительский/дочерний)\n";
		ExitProcess(1);
	}
	system("pause");
	ExitProcess(0);
}
