#include <iostream>
#include <Windows.h>
#include <thread>
#include <string>
#include <time.h>

#define ITERATIONS 1000000


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


int GetThreadPriorityProcessExplorer(DWORD processPriorityClass, int threadPriority)
{
	int basePriority = 0;


	switch (processPriorityClass)
	{
	case IDLE_PRIORITY_CLASS:          basePriority = 4;  break;
	case BELOW_NORMAL_PRIORITY_CLASS:  basePriority = 6;  break;
	case NORMAL_PRIORITY_CLASS:        basePriority = 8;  break;
	case ABOVE_NORMAL_PRIORITY_CLASS:  basePriority = 10; break;
	case HIGH_PRIORITY_CLASS:          basePriority = 13; break;
	case REALTIME_PRIORITY_CLASS:      basePriority = 24; break;
	default:                           basePriority = 8;  break;
	}

	int relativePriority = 0;

	switch (threadPriority)
	{
	case THREAD_PRIORITY_IDLE:           relativePriority = -15; break;
	case THREAD_PRIORITY_LOWEST:         relativePriority = -2;  break;
	case THREAD_PRIORITY_BELOW_NORMAL:   relativePriority = -1;  break;
	case THREAD_PRIORITY_NORMAL:         relativePriority = 0;   break;
	case THREAD_PRIORITY_ABOVE_NORMAL:   relativePriority = 1;   break;
	case THREAD_PRIORITY_HIGHEST:        relativePriority = 2;   break;
	case THREAD_PRIORITY_TIME_CRITICAL:  relativePriority = 15;  break;
	default:                             relativePriority = 0;   break;
	}

	return basePriority + relativePriority;
}


int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int iterations = 1000000;


	clock_t t = clock();

	for (int i = 0; i < iterations; i++) {


		if(i % 1000 == 0)
		{

			std::cout << "Iteration: " << i << std::endl;

			std::cout << "Pid: " << GetCurrentProcessId() << std::endl;
			std::cout << "Tid: " << GetCurrentThreadId() << std::endl;


			HANDLE proc = GetCurrentProcess();

			std::cout << "Priority class: " << GetPriorityClassToString(GetPriorityClass(proc)) << std::endl;


			HANDLE thread = GetCurrentThread();

			std::cout << "thread priority: " << GetThreadPriorityProcessExplorer(GetPriorityClass(proc), GetThreadPriority(thread)) << std::endl;

			std::cout << "Processor number: " << GetCurrentProcessorNumber() << std::endl;


			std::cout << "\n\n---------------------------------------------------------\n\n";

			Sleep(200);

		}


	}

	t = clock() - t;


	std::cout << "It took " << (float)t / CLOCKS_PER_SEC << " seconds to complete the cycle.\n";

	system("pause");
	return 0;
}