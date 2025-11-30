#include <iostream>
#include <Windows.h>
#include <cstdlib>

#define _CRT_SECURE_NO_WARNINGS


int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);



	STARTUPINFOA si[3] = { 0 };
	PROCESS_INFORMATION pi[3] = { 0 };

	for (int i = 0; i < 3; ++i)
	{
		si[i].cb = sizeof(STARTUPINFOA);
	}


	char processName[] = "C:\\Users\\User-672a41d6\\OS3\\Lab-03x.exe";
	std::cout << "Запуск процесса c первым параметром: " << processName << std::endl;


	if (!CreateProcessA(processName,
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si[0],
		&pi[0]
	)) {
		std::cerr << "CreateProcess failed " << GetLastError() << std::endl;

	}


	std::cout << "Запуск процесса cо вторым параметром: " << processName << std::endl;


	if (!CreateProcessA(NULL,
		(LPSTR)"\"C:\\Users\\User-672a41d6\\OS3\\Lab-03x.exe\" 10",
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si[1],
		&pi[1]
	)) {
		std::cout << "CreateProcess failed " << GetLastError() << std::endl;
	}




	SetEnvironmentVariableA("ITER_NUM", "15");

	std::cout << "Запуск процесса c двумя параметрами: " << processName << std::endl;


	if (!CreateProcessA((LPSTR)"C:\\Users\\User-672a41d6\\OS3\\Lab-03x.exe",
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si[2],
		&pi[2]
	)) {
		std::cout << "CreateProcess failed " << GetLastError() << std::endl;
	}



	for (int i = 0; i < 3; ++i)
	{
		if (pi[i].hProcess)
		{
			WaitForSingleObject(pi[i].hProcess, INFINITE);
			CloseHandle(pi[i].hThread);
			CloseHandle(pi[i].hProcess);
		}
	}


	ExitProcess(0);
}