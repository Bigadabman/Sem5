#include <iostream>
#include <Windows.h>
#include <cstdlib>

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int iterations;


	if (argc > 1) {
		iterations = atoi(argv[1]);
	}
	else {
		char buffer[200];
		DWORD len = GetEnvironmentVariableA("ITER_NUM", buffer, sizeof(buffer));

		if (len > 0 && len < sizeof(buffer)) {
			iterations = atoi(buffer);
		}

	}


	if (iterations <= 0) {
		std::cerr << "Некорректное значение итераций" << std::endl;
		ExitProcess(1);
	}


	int pid = GetCurrentProcessId();

	std::cout << "Всего будет произведено " << iterations << " итераций" << std::endl;
	std::cout << "-----------------------------------------------\n";
	for (int i = 0; i < iterations; i++) {


		std::cout << "Итерация " << i << ": PID = " << pid << std::endl;

		Sleep(500);

	}


	ExitProcess(0);
}