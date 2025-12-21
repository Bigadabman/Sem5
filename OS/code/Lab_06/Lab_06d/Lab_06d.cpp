#include <iostream>
#include <Windows.h>
#include <semaphore>

const char* EventName = "KEOEvent";

const char* username = "User-672a41d6";
int nameLength = strlen(username);


void printChildInfo(const char* stringname) {

	HANDLE hEvent = OpenEventA(EVENT_ALL_ACCESS, FALSE, EventName);

	if (hEvent == NULL)
	{
		std::cerr << "Не удалось открыть мьютекс!\n";
		return;
	}
		
	WaitForSingleObject(hEvent, INFINITE);
	for (int i = 0; i < 90; i++) {

		std::cout << stringname << " " << username[(i) % nameLength] << " " << i << "\n";

		Sleep(100);
	}
	CloseHandle(hEvent);
}


void printParentInfo() {
	HANDLE hEvent = OpenEventA(EVENT_ALL_ACCESS, FALSE, EventName);

	for (int i = 0; i < 90; i++) {

		if (i == 15)
			SetEvent(hEvent);

		std::cout << "Main" << " " << username[(i) % nameLength] << " " << i << "\n";

		Sleep(100);
	}
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
		printChildInfo("Child");
	}
	else if (mod == 0) {


		HANDLE hEvent = CreateEventA(NULL, TRUE, FALSE, EventName);
		if (!hEvent)
		{
			std::cerr << "Не удалось создать ивент\n";
			ExitProcess(1);
		}


		STARTUPINFOA si[2] = { 0 };
		si[0].cb = sizeof(STARTUPINFO);
		si[1].cb = sizeof(STARTUPINFO);
		PROCESS_INFORMATION pi[2] = { 0 };

		
		char processName[] = "Lab_06d.exe 1";

		if (!CreateProcessA(NULL, processName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[0], &pi[0])) {
			std::cerr << "Не удалось создать процесс A";
			ExitProcess(1);
		}

		if (!CreateProcessA(NULL, processName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[1], &pi[1])) {
			std::cerr << "Не удалось создать процесс B";
			ExitProcess(1);
		}

		printParentInfo();

		for (int i = 0; i < 2; i++) {
			WaitForSingleObject(pi[i].hProcess, INFINITE);
			CloseHandle(pi[i].hProcess);
			CloseHandle(pi[i].hThread);
		}

		CloseHandle(hEvent);
	}
	else {
		std::cerr << "Использование: Lab_06b.exe 0/1(Родительский/дочерний)\n";
		ExitProcess(1);
	}
	system("pause");
	ExitProcess(0);
}
