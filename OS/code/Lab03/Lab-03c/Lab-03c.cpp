#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>



int main(int arc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);


	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessSnap, &pe32)) {
		int counter = 0;

		std::wcout << "Имя процесса  |  " << "  ID прроцесса  |  "<<  "  ID родительского процесса " <<  std::endl;
		do {

			std::wcout << pe32.szExeFile << " | " << pe32.th32ProcessID
				<< " | " << pe32.th32ParentProcessID << std::endl;
			
		} while (Process32Next(hProcessSnap, &pe32));


	}
	CloseHandle(hProcessSnap);
	ExitProcess(0);
}



