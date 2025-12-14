#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <string>


std::string PriorityClassToString(DWORD pc)
{
	switch (pc)
	{
	case IDLE_PRIORITY_CLASS: return "IDLE_PRIORITY_CLASS";
	case BELOW_NORMAL_PRIORITY_CLASS: return "BELOW_NORMAL_PRIORITY_CLASS";
	case NORMAL_PRIORITY_CLASS: return "NORMAL_PRIORITY_CLASS";
	case ABOVE_NORMAL_PRIORITY_CLASS: return "ABOVE_NORMAL_PRIORITY_CLASS";
	case HIGH_PRIORITY_CLASS: return "HIGH_PRIORITY_CLASS";
	case REALTIME_PRIORITY_CLASS: return "REALTIME_PRIORITY_CLASS";
	default: return "UNKNOWN_PRIORITY_CLASS";
	}
}

DWORD GetPriorityClassFromInt(int val)
{
	switch (val)
	{
	case 1: return IDLE_PRIORITY_CLASS;
	case 2: return BELOW_NORMAL_PRIORITY_CLASS;
	case 3: return NORMAL_PRIORITY_CLASS;
	case 4: return ABOVE_NORMAL_PRIORITY_CLASS;
	case 5: return HIGH_PRIORITY_CLASS;
	case 6: return REALTIME_PRIORITY_CLASS;
	default: return NORMAL_PRIORITY_CLASS;
	}
}



int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	if (argc != 4) {
		std::cout << "Usage: Lab-05b.exe <int affinity mask> <int proc 1 priority class> <int proc 2 priority class>\n";
		ExitProcess(1);
	}

	DWORD_PTR mask = std::stoull(argv[1], nullptr, 0);
	int procPriority1 = std::stoi(argv[2]);
	int procPriority2 = std::stoi(argv[3]);

	DWORD priorityClass1 = GetPriorityClassFromInt(procPriority1);
	DWORD priorityClass2 = GetPriorityClassFromInt(procPriority2);






	STARTUPINFOA si[2] = { 0 };
	PROCESS_INFORMATION pi[2] = { 0 };

	for (int i = 0; i < 2; ++i)
	{
		si[i].cb = sizeof(STARTUPINFOA);
	}

	char processName[] = ".\\Lab-05x.exe";


	if (CreateProcessA((LPSTR)processName,
		NULL,
		NULL,
		NULL,
		FALSE,
		priorityClass1 | CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si[0],
		&pi[0]
	)) {
		SetProcessAffinityMask(pi[0].hProcess, mask);
	}
	
	else{
		std::cerr << "CreateProcess 1 failed " << GetLastError() << std::endl;
	}




	if (CreateProcessA((LPSTR)processName,
		NULL,
		NULL,
		NULL,
		FALSE,
		priorityClass2 | CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si[1],
		&pi[1]
	)) {
		SetProcessAffinityMask(pi[1].hProcess, mask);
	}

	else {
		std::cerr << "CreateProcess 2 failed " << GetLastError() << std::endl;
	}


	for (int i = 0; i < 2; ++i)
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