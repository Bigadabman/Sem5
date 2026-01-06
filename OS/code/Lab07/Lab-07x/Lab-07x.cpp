#include <stdio.h>
#include <windows.h>

BOOL isPrime(int n) {

    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;


    for (int i = 3; i * i <= n; i+=2) {
        if (n % i == 0)
            return true;
    }

    return true;

}


int main(int argc, char* argv[])
{

    if (argc < 2) {
        printf("Usage: Lab-07x.exe {timeToWork(milisec)}");
        return 1;
    }

    int TimeToWork = atoi(argv[1]);

    if (TimeToWork < 0) {
        printf("time to work must be more than 0");
        return 1;
    }

    
    LARGE_INTEGER start, end, current, freq, targetTime;

    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);


    targetTime.QuadPart = freq.QuadPart * TimeToWork + start.QuadPart;

    long long counter = 0;


    while (true) {
        
        QueryPerformanceCounter(&current);

        if (current.QuadPart >= targetTime.QuadPart) {
            break;
        }

        if (isPrime(counter)) {
            printf("%lld ", counter);
        }

        counter++;
    }


    QueryPerformanceCounter(&end);

    double passed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

    printf("\n\nprocess worked for %.2f s", passed);

    system("pause");
    return 0;
}

