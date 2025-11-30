#include <iostream>
#include <windows.h>



int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char procName[] = "C:\\Users\\User-672a41d6\\OS3\\Lab-03d-client.exe";


	try {

		int processesAmount;
		int lowerLimit;
		int upperLimit;

		if (argc > 3) {
			processesAmount = atoi(argv[1]);
			lowerLimit = atoi(argv[2]);
			upperLimit = atoi(argv[3]);
		}
		else
			throw std::runtime_error("Не все аргументы получены\n");


		if (processesAmount <= 0 || lowerLimit >= upperLimit || lowerLimit < 0 || upperLimit < 0)
			throw std::runtime_error("Некорректные аргументы");



		HANDLE hWritePipe, hReadPipe;

		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = true;
		sa.lpSecurityDescriptor = NULL;


		if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
			std::cerr << "Ошибка создания канала. " << GetLastError() << std::endl;

		}

		std::cout << "Канала связи создан\n";




		PROCESS_INFORMATION* processes = new PROCESS_INFORMATION[processesAmount];
		ZeroMemory(processes, sizeof(PROCESS_INFORMATION) * processesAmount);



		int range = (upperLimit - lowerLimit + 1) / processesAmount;


		for (int i = 0; i < processesAmount; i++) {


			STARTUPINFOA si;
			ZeroMemory(&si, sizeof(STARTUPINFO));

			si.cb = sizeof(STARTUPINFO);
			si.dwFlags = STARTF_USESTDHANDLES;
			si.hStdOutput = hWritePipe;
			si.hStdError = hWritePipe;
			si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

			PROCESS_INFORMATION pi;
			ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));



			int procLowerLimit = lowerLimit + i * range;
			int procUpperLimit = lowerLimit + (i + 1) * range - 1;

			char cmdLine[512];
			sprintf_s(cmdLine, sizeof(cmdLine), "Lab-03d-client.exe %d %d", procLowerLimit, procUpperLimit);
			


			if (!CreateProcessA(NULL,
				(LPSTR)cmdLine,
				NULL,
				NULL,
				true,
				0,
				NULL,
				NULL,
				&si,
				&pi))
			{
				std::cerr << "Не удалось создать проецесс " << i << ". Ошибка: " << GetLastError() << std::endl;
				delete[] processes;
				CloseHandle(hReadPipe);
				CloseHandle(hWritePipe);
				ExitProcess(1);
			}

			std::cout << "Запущен процесс #" << i << ". Диапазон [" << procLowerLimit << "; " << procUpperLimit << "]\n";

			processes[i] = pi;

		}
		CloseHandle(hWritePipe);


		char buffer[1024];
		DWORD bytesRead;


		while (ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
			buffer[bytesRead] = '\0';
			std::cout << buffer<<"\n";
		}



		for (int i = 0; i < processesAmount; i++) {
			WaitForSingleObject(processes[i].hProcess, INFINITE);
			CloseHandle(processes[i].hProcess);
			CloseHandle(processes[i].hThread);
		}


		CloseHandle(hReadPipe);
		


		delete[] processes;
	}
	catch (std::runtime_error err) {
		std::cout << err.what();
	}

	std::cout << "Все дочерние процессы завершены\n";

	ExitProcess(0);
}
 
