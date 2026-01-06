#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int isPrime(long long n)
{
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (long long i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return 0;

    return 1;
}


double to_seconds(struct timespec t)
{
    return t.tv_sec + t.tv_nsec / 1e9;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./Lab-07x <time_to_work_seconds>\n");
        return 1;
    }

    int timeToWork = atoi(argv[1]);
    if (timeToWork <= 0)
    {
        printf("Time must be greater than zero\n");
        return 1;
    }

    struct timespec start, current;
    clock_gettime(CLOCK_MONOTONIC, &start);

    long long counter = 0;

    while (1)
    {
        clock_gettime(CLOCK_MONOTONIC, &current);

        double passed =
            to_seconds(current) - to_seconds(start);

        if (passed >= timeToWork)
            break;

        if (isPrime(counter))
            printf("%lld ", counter);

        counter++;
    }

    clock_gettime(CLOCK_MONOTONIC, &current);
    double total =
        to_seconds(current) - to_seconds(start);

    printf("\n\nprocess worked for %.2f seconds\n", total);

    return 0;
}
