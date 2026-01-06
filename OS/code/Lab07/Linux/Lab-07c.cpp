#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>


volatile sig_atomic_t timer_fired = 0;


void timer_handler(int sig)
{
    timer_fired = 1;
}

int main()
{
    timer_t timerid;
    struct sigevent sev;
    struct itimerspec its;
    struct sigaction sa;

    long long counter = 0;
    int seconds = 0;

    sa.sa_handler = timer_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, NULL);


    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &timerid;

    timer_create(CLOCK_MONOTONIC, &sev, &timerid);


    its.it_value.tv_sec = 3;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 3;
    its.it_interval.tv_nsec = 0;

    timer_settime(timerid, 0, &its, NULL);


    while (seconds < 15)
    {
        counter++;


        if (timer_fired)
        {
            timer_fired = 0;
            seconds += 3;

            printf("%d seconds passed.\n", seconds);
            printf("Amount of iterations: %lld\n\n", counter);
        }
    }

    printf("Total iterations: %lld\n", counter);

    timer_delete(timerid);
    return 0;
}
