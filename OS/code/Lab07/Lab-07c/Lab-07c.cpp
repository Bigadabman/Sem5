#include <stdio.h>
#include <Windows.h>

int main()
{

	HANDLE hTimer = CreateWaitableTimerA(NULL, FALSE, NULL);


	LARGE_INTEGER timeToWork;
	timeToWork.QuadPart = -30000000;
	LONG period = 3000;

	SetWaitableTimer(hTimer, &timeToWork, period, NULL, NULL, FALSE);

	long long counter = 0;
	int seconds = 0;

	while (seconds < 15) {
		counter++;
		if ((WaitForSingleObject(hTimer, 0)) == WAIT_OBJECT_0) {
			seconds += 3;
			printf("%d seconds passed.\nAmount of iterations: %lld\n",seconds, counter);
		}

	}

	printf("total iterations: %lld", counter);

	CloseHandle(hTimer);

	return 0;
}
