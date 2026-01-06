#include <stdio.h>
#include <time.h>
#include <stdbool.h>

double timespec_to_seconds(struct timespec t)
{
    return t.tv_sec + t.tv_nsec / 1e9;
}

int main()
{
    struct timespec cpu_start, cpu_current;
    struct timespec real_start, real_end;

    long long counter = 0;
    
    bool fiveSecPassed = false;
    bool tenSecPassed = false;


    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_start);


    clock_gettime(CLOCK_MONOTONIC, &real_start);

    while (true)
    {
        counter++;

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_current);

        double cpu_passed =
            timespec_to_seconds(cpu_current) -
            timespec_to_seconds(cpu_start);

        if (!fiveSecPassed && cpu_passed >= 5.0)
        {
            printf("five seconds of CPU time passed.\n");
            printf("Amount of iterations: %lld\n\n", counter);
            fiveSecPassed = true;
        }

        if (!tenSecPassed && cpu_passed >= 10.0)
        {
            printf("ten seconds of CPU time passed.\n");
            printf("Amount of iterations: %lld\n\n", counter);
            tenSecPassed = true;
        }

        if (cpu_passed >= 15.0)
        {
            printf("fifteen seconds of CPU time passed.\n");
            printf("Final amount of iterations: %lld\n\n", counter);
            break;
        }
    }


    clock_gettime(CLOCK_MONOTONIC, &real_end);

    double real_passed =
        timespec_to_seconds(real_end) -
        timespec_to_seconds(real_start);

    printf("Real (wall-clock) time passed: %.3f seconds\n", real_passed);

    return 0;
}
