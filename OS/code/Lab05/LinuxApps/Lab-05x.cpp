#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
#include <ctime>

#define ITERATIONS 1000000

static inline long GetTid()
{
    return syscall(SYS_gettid);
}

std::string GetNiceLevelString(int niceVal)
{
    return "Nice level: " + std::to_string(niceVal);
}

int main(int argc, char* argv[])
{
    timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < ITERATIONS; i++)
    {
        if (i % 1000 == 0)
        {
            std::cout << "\n\n------------------ Thread info -------------------------------\n\n";

            std::cout << "Iteration: " << i << std::endl;
            std::cout << "Pid: " << getpid() << std::endl;
            std::cout << "Tid: " << GetTid() << std::endl;

            int niceVal = getpriority(PRIO_PROCESS, 0);
            std::cout << GetNiceLevelString(niceVal) << std::endl;

            int cpuNo = sched_getcpu();
            std::cout << "Processor number: " << cpuNo << std::endl;

            std::cout << "\n--------------------------------------------------------------\n";

            usleep(200 * 1000);
        }
    }

    gettimeofday(&end, NULL);

    double elapsed =
        (end.tv_sec - start.tv_sec) +
        (end.tv_usec - start.tv_usec) / 1e6;

    std::cout << "\nIt took " << elapsed << " seconds to complete the cycle.\n";

    return 0;
}
