#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <string>
#include <thread>

#define ITERATIONS 1000000

struct ThreadParams
{
	int threadNum;
};


std::string GetThreadPriorityToString(int tp)
{
	switch (tp)
	{
	case THREAD_PRIORITY_IDLE: return "THREAD_PRIORITY_IDLE";
	case THREAD_PRIORITY_LOWEST: return "THREAD_PRIORITY_LOWEST";
	case THREAD_PRIORITY_BELOW_NORMAL: return "THREAD_PRIORITY_BELOW_NORMAL";
	case THREAD_PRIORITY_NORMAL: return "THREAD_PRIORITY_NORMAL";
	case THREAD_PRIORITY_ABOVE_NORMAL: return "THREAD_PRIORITY_ABOVE_NORMAL";
	case THREAD_PRIORITY_HIGHEST: return "THREAD_PRIORITY_HIGHEST";
	case THREAD_PRIORITY_TIME_CRITICAL: return "THREAD_PRIORITY_TIME_CRITICAL";
	case THREAD_PRIORITY_ERROR_RETURN: return "THREAD_PRIORITY_ERROR_RETURN";
	default: return "UNKNOWN_THREAD_PRIORITY";
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


int GetThreadPriorityFromInt(int val)
{
	switch (val)
	{
	case 1: return THREAD_PRIORITY_IDLE;
	case 2: return THREAD_PRIORITY_LOWEST;
	case 3: return THREAD_PRIORITY_BELOW_NORMAL;
	case 4: return THREAD_PRIORITY_NORMAL;
	case 5: return THREAD_PRIORITY_ABOVE_NORMAL;
	case 6: return THREAD_PRIORITY_HIGHEST;
	case 7: return THREAD_PRIORITY_TIME_CRITICAL;
	default: return THREAD_PRIORITY_NORMAL;
	}
}


std::string GetPriorityClassToString(DWORD priorityClass) {

	std::string stringPriority;

	switch (priorityClass) {
	case ABOVE_NORMAL_PRIORITY_CLASS:
		stringPriority = "ABOVE_NORMAL_PRIORITY_CLASS";
		break;
	case BELOW_NORMAL_PRIORITY_CLASS:
		stringPriority = "BELOW_NORMAL_PRIORITY_CLASS";
		break;
	case HIGH_PRIORITY_CLASS:
		stringPriority = "HIGH_PRIORITY_CLASS";
		break;
	case IDLE_PRIORITY_CLASS:
		stringPriority = "IDLE_PRIORITY_CLASS";
		break;
	case NORMAL_PRIORITY_CLASS:
		stringPriority = "NORMAL_PRIORITY_CLASS";
		break;
	case REALTIME_PRIORITY_CLASS:
		stringPriority = "REALTIME_PRIORITY_CLASS";
		break;

	default:
		stringPriority = "No class";
		break;
	}

	return stringPriority;

}





void cycleFunction(LPVOID lpParam) {

	
	if (lpParam == nullptr)
	{
		std::cerr << "lpParam == nullptr\n";
		return;
	}


	ThreadParams* pThreadNumber = static_cast<ThreadParams*>(lpParam);
	int  ThreadNumber = pThreadNumber->threadNum;




	clock_t t = clock();

	for (int i = 0; i < ITERATIONS; i++) {


		if (i % 1000 == 0)
		{
			std::cout << "\n\n------------------Thead " << ThreadNumber << "-------------------------------\n\n";
			std::cout << "Iteration: " << i << std::endl;

			std::cout << "Pid: " << GetCurrentProcessId() << std::endl;
			std::cout << "Tid: " << GetCurrentThreadId() << std::endl;


			HANDLE proc = GetCurrentProcess();

			std::cout << "Priority class: " << GetPriorityClassToString(GetPriorityClass(proc)) << std::endl;


			HANDLE thread = GetCurrentThread();

			std::cout << "thread priority: " << GetThreadPriority(thread) << std::endl;

			std::cout << "Processor number: " << GetCurrentProcessorNumber() << std::endl;


			std::cout << "\n\n---------------------------------------------------------\n\n";

			Sleep(200);

		}


	}

	t = clock() - t;


	std::cout << "It took " << (float)t / CLOCKS_PER_SEC << " seconds to complete the cycle.\n";

}




int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc != 5) {
		std::cerr << "Usage: Lab-05b.exe <int affinity mask> <int parent thread priority class>"<<
			" <int thread 1 priority class> <int thread 1 priority class>\n";
		ExitProcess(1);
	}

	DWORD_PTR mask = std::stoull(argv[1], nullptr, 0);
	int procPriority = std::stoi(argv[2]);
	int threadPriority1 = std::stoi(argv[3]);
	int threadPriority2 = std::stoi(argv[4]);
	DWORD priorityClass = GetPriorityClassFromInt(procPriority);



	if (!SetProcessAffinityMask(GetCurrentProcess(), mask)) {
		std::cerr << "Coudn't set process affinity mask: " << GetLastError() <<"\n";
		ExitProcess(1);
	}

	if (!SetPriorityClass(GetCurrentProcess(), priorityClass)) {
		std::cerr << "Coudn't set process priority class: " << GetLastError() << "\n";
		ExitProcess(1);
	}


	HANDLE hThreads[2];
	DWORD Thread1, Thread2;

	ThreadParams p1{ 1 }, p2{ 2 };


	hThreads[0] = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)cycleFunction,
		&p1,
		0,
		&Thread1
	);


	if (hThreads[0] == NULL) {
		std::cerr << "Coudn't create first thread\n";
		ExitProcess(1);
	}

	hThreads[1] = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)cycleFunction,
		&p2,
		0,
		&Thread2
	);


	if (hThreads[1] == NULL) {
		std::cerr << "Coudn't create second thread\n";
		CloseHandle(hThreads[0]);
		ExitProcess(1);
	}


	if (!SetThreadPriority(hThreads[0], GetThreadPriorityFromInt(threadPriority1)) 
		|| !SetThreadPriority(hThreads[1], GetThreadPriorityFromInt(threadPriority2))) {
		std::cerr << "Coudn't set thread priority\n";
		CloseHandle(hThreads[0]);
		CloseHandle(hThreads[1]);
		ExitProcess(1);
	}

	std::cout << "Params: \n";
	std::cout << "\tMask: " << mask << std::endl;
	std::cout << "\tpriority class: " << GetPriorityClassToString(priorityClass) << std::endl;
	std::cout << "\tThread 1 priority: " << GetThreadPriorityToString(threadPriority1) << std::endl;
	std::cout << "\tThread 2 priority: " << GetThreadPriorityToString(threadPriority2) << std::endl;



	WaitForMultipleObjects(2, hThreads, true, INFINITE);

	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);


	ExitProcess(0);
}