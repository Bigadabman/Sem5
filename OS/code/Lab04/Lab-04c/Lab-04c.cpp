#include <iostream>
#include <thread>
#include <Windows.h>

void Lab_04x(int iterations) {

	const char* username = "User-672a41d6";
	int nameLength = strlen(username);

	if (iterations < 0) {
		fprintf(stderr, "Количество итераций должно быть положительным\n");
		return;
	}


	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();

	for (int i = 0; i < iterations; i++) {
		char currentLetter = username[i % nameLength];
		printf("%lu - %lu - %d - %c\n", pid, tid, i, currentLetter);
		Sleep(300);
	}


	//fflush(stdout);

	return;
}



int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int iterations1 = 50;
	int iterations2 = 125;
	int iterationsMain = 100;

	HANDLE hThreads[2];
	DWORD ThreadId1, ThreadId2;
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();

	const char* username = "User-672a41d6";
	int nameLength = strlen(username);


	hThreads[0] = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)Lab_04x,
		(LPVOID)iterations1,
		0,
		&ThreadId1
	);


	if (hThreads[0] == NULL)
	{
		fprintf(stderr, "Ошибка создания первого потока\n");
		ExitProcess(1);
	}


	hThreads[1] = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)Lab_04x,
		(LPVOID)iterations2,
		0,
		&ThreadId2
	);


	if (hThreads[1] == NULL)
	{

		fprintf(stderr, "Ошибка создания второго потока\n");
		CloseHandle(hThreads[0]);
		ExitProcess(1);
	}


	for (int i = 0; i < iterationsMain; i++) {

		if (i == 40) {
			printf("Завершение второго потока\n");
			TerminateThread(hThreads[1], 0);
		}


		char currentLetter = username[i % nameLength];
		printf("%lu - %lu - %d - %c\n", pid, tid, i, currentLetter);
		Sleep(300);

	}


	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);


	if (!CloseHandle(hThreads[0]))
	{
		fprintf(stderr, "Ошибка при закрытии потока %lu: код %lu\n", ThreadId1, GetLastError());
	}

	if (!CloseHandle(hThreads[1]))
	{
		fprintf(stderr, "Ошибка при закрытии потока %lu: код %lu\n", ThreadId2, GetLastError());
	}


	printf("Все потоки успешно завершены\n");

	ExitProcess(0);
}