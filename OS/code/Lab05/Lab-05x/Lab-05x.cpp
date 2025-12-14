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

			std::cout << "thread priority: " << GetThreadPriority(thread) << std::endl;

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