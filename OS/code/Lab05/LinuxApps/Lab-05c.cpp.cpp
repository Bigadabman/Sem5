#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <cstring>
#include <cstdlib>
#include <ctime>

#define ITERATIONS 1000000

struct ThreadParams
{
    int threadNum;
    int niceLevel;
};


std::string GetNiceToString(int niceVal)
{
    return "nice=" + std::to_string(niceVal);
}


bool SetAffinityMask(unsigned long mask)
{
    cpu_set_t set;
    CPU_ZERO(&set);

    for (int i = 0; i < 64; i++)
    {
        if (mask & (1ULL << i))
            CPU_SET(i, &set);
    }

    return sched_setaffinity(0, sizeof(cpu_set_t), &set) == 0;
}


int GetProcessorNumber()
{
    return sched_getcpu(); // Linux API
}


void* cycleFunction(void* lpParam)
{
    if (lpParam == nullptr)
    {
        std::cerr << "lpParam == nullptr\n";
        pthread_exit(nullptr);
    }

    ThreadParams* p = static_cast<ThreadParams*>(lpParam);

    // Устанавливаем nice() для потока
    if (setpriority(PRIO_PROCESS, 0, p->niceLevel) != 0)
    {
        std::cerr << "Could not set nice level\n";
    }

    clock_t t = clock();

    for (int i = 0; i < ITERATIONS; i++)
    {
        if (i % 1000 == 0)
        {
            std::cout << "\n\n------------------Thread "
                << p->threadNum
                << "-------------------------------\n\n";

            std::cout << "Iteration: " << i << "\n";
            std::cout << "Pid: " << getpid() << "\n";

            std::cout << "Tid: " << syscall(SYS_gettid) << "\n";

            std::cout << "Nice level: " << GetNiceToString(
                getpriority(PRIO_PROCESS, 0)
            ) << "\n";

            std::cout << "Processor number: " << GetProcessorNumber() << "\n";

            std::cout << "\n\n---------------------------------------------------------\n\n";

            usleep(200000);
        }
    }

    t = clock() - t;

    std::cout << "Thread " << p->threadNum <<
        " finished. Time: " << (float)t / CLOCKS_PER_SEC << " sec.\n";

    delete p;

    return nullptr;
}


void PrintParams(unsigned long mask, int pr1, int pr2)
{
    std::cout << "Params:\n";
    std::cout << "\tMask: " << mask << "\n";
    std::cout << "\tThread 1 priority: " << GetNiceToString(pr1) << "\n";
    std::cout << "\tThread 2 priority: " << GetNiceToString(pr2) << "\n";
}


int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: Lab-05c <mask> <nice1> <nice2>\n";
        return 1;
    }

    unsigned long mask = std::stoul(argv[1], nullptr, 0);
    int nice1 = std::stoi(argv[2]);
    int nice2 = std::stoi(argv[3]);

    PrintParams(mask, nice1, nice2);

    if (!SetAffinityMask(mask))
    {
        std::cerr << "Could not set affinity mask\n";
        return 1;
    }

    pthread_t t1, t2;

    ThreadParams* p1 = new ThreadParams{ 1, nice1 };
    ThreadParams* p2 = new ThreadParams{ 2, nice2 };

    if (pthread_create(&t1, nullptr, cycleFunction, p1) != 0)
    {
        std::cerr << "Could not create first thread\n";
        delete p1;
        return 1;
    }

    if (pthread_create(&t2, nullptr, cycleFunction, p2) != 0)
    {
        std::cerr << "Could not create second thread\n";
        delete p2;
        return 1;
    }

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    std::cout << "All threads finished.\n";

    return 0;
}
