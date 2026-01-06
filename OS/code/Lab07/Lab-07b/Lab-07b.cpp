#include <stdio.h>
#include <Windows.h>

int main()
{
	LARGE_INTEGER current, start, freq;
	long long counter = 0;
	bool fiveSecPassed = false,
		tenSecPassed = false,
		fifteenSecPassed = false;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	while (true) {
		counter++;

		QueryPerformanceCounter(&current);

		double passed = (double)(current.QuadPart - start.QuadPart) /
			freq.QuadPart;

		if (!fiveSecPassed && passed >= 5.0) {
			printf("five seconds passed.\nAmount of iterations: %lld\n", counter);
			fiveSecPassed = true;
		}

		if (!tenSecPassed && passed >= 10.0) {
			printf("ten seconds passed.\nAmount of iterations: %lld\n", counter);
			tenSecPassed = true;
		}

		if (!fifteenSecPassed && passed >= 15.0) {
			printf("15 seconds passed.\nAmount of iterations: %lld\n", counter);
			fifteenSecPassed = true;
			break;
		}


	}



	return 0;
}
