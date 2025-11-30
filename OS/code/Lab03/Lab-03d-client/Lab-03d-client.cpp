#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

bool isPrime(int num);


int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	

	try {


		int lowerLimit;
		int upperLimit;

		if (argc > 2) {
			lowerLimit = atoi(argv[1]);
			upperLimit = atoi(argv[2]);
		}
		else
			throw new std::string("Не все аргументы получены");

		if (lowerLimit >= upperLimit || lowerLimit < 0 || upperLimit < 0)
			throw new std::string("Некорректные аргументы");


		std::vector<int> buffer;

		for (int i = lowerLimit; i <= upperLimit; i++) {

			if (isPrime(i))
				buffer.push_back(i);
		}


		if (buffer.empty()) {
			std::cout << "Простых чисел в диапазоне [" << lowerLimit << "; " << upperLimit << "] не найдено;\n";
			ExitProcess(0);
		}




		HANDLE hWritePipe = GetStdHandle(STD_OUTPUT_HANDLE);

		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = true;
		sa.lpSecurityDescriptor = NULL;


		DWORD bytesWritten;


		std::string result;
		for (int num : buffer)
			result += std::to_string(num) + " ";
		

		if (!WriteFile(hWritePipe, result.c_str(), result.size(), &bytesWritten, NULL)) {
			std::cerr << "Ошибка записи в канал. " << GetLastError() << std::endl;

		}
		else {
			std::cout << "Данные записаны в канал\n";

		}

		if (hWritePipe != INVALID_HANDLE_VALUE)
			CloseHandle(hWritePipe);

	}
	catch (std::string err) {
		std::cout << err << std::endl;
	}


	system("pause");

	ExitProcess(0);
}




bool isPrime(int num) {

	if (num < 2)
		return false;

	for (int i = 2; i*i < num; i++) {
		if (num % i == 0)
			return false;
	}

	return true;
}