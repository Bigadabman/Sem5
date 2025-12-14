#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <sched.h>
#include <cstring>
#include <cstdlib>
#include <sys/wait.h>

std::string GetNiceString(int val)
{
    return "nice=" + std::to_string(val);
}

void PrintParams(unsigned long mask, int pr1, int pr2)
{
    std::cout << "Params:\n";
    std::cout << "\tMask: " << mask << "\n";
    std::cout << "\tProcess 1 priority: " << GetNiceString(pr1) << "\n";
    std::cout << "\tProcess 2 priority: " << GetNiceString(pr2) << "\n";
}

bool SetAffinityMask(pid_t pid, unsigned long mask)
{
    cpu_set_t set;
    CPU_ZERO(&set);

    for (int i = 0; i < 64; i++)
    {
        if (mask & (1ULL << i))
            CPU_SET(i, &set);
    }

    return sched_setaffinity(pid, sizeof(cpu_set_t), &set) == 0;
}

void LaunchChild(int niceLevel)
{
    // установить nice второго процесса
    if (setpriority(PRIO_PROCESS, 0, niceLevel) != 0)
    {
        std::cerr << "Could not set nice value\n";
        _exit(1);
    }

    execl("./Lab-05x", "./Lab-05x", (char*)nullptr);
    std::cerr << "execl failed\n";
    _exit(1);
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: Lab-05b <mask> <nice1> <nice2>\n";
        return 1;
    }

    unsigned long mask = std::stoul(argv[1], nullptr, 0);
    int pr1 = std::stoi(argv[2]);
    int pr2 = std::stoi(argv[3]);

    PrintParams(mask, pr1, pr2);

    // установить affinity для родительского процесса
    if (!SetAffinityMask(getpid(), mask))
    {
        std::cerr << "Could not set affinity mask\n";
        return 1;
    }

    pid_t p1 = fork();
    if (p1 == 0)
    {
        LaunchChild(pr1);
    }
    else if (p1 < 0)
    {
        std::cerr << "Could not create first process\n";
        return 1;
    }

    pid_t p2 = fork();
    if (p2 == 0)
    {
        LaunchChild(pr2);
    }
    else if (p2 < 0)
    {
        std::cerr << "Could not create second process\n";
        return 1;
    }

    // ожидание обоих
    waitpid(p1, nullptr, 0);
    waitpid(p2, nullptr, 0);

    std::cout << "All child processes finished\n";

    return 0;
}
