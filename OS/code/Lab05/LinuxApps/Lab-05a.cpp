#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <cstring>
#include <cstdlib>
#include <bitset>

#define MASK_BITS 16  // для вывода маски CPU в двоичном виде

std::string GetSchedulerToString(int policy)
{
    switch (policy)
    {
    case SCHED_OTHER: return "SCHED_OTHER (normal)";
    case SCHED_FIFO:  return "SCHED_FIFO (real-time)";
    case SCHED_RR:    return "SCHED_RR (real-time)";
#ifdef SCHED_BATCH
    case SCHED_BATCH: return "SCHED_BATCH";
#endif
#ifdef SCHED_IDLE
    case SCHED_IDLE:  return "SCHED_IDLE";
#endif
    default:          return "UNKNOWN_SCHEDULER";
    }
}

void PrintAffinityMask(cpu_set_t* set)
{
    std::bitset<MASK_BITS> maskBits(0);

    for (int cpu = 0; cpu < MASK_BITS; cpu++)
        if (CPU_ISSET(cpu, set))
            maskBits.set(cpu);

    std::cout << "Affinity mask (binary): " << maskBits << std::endl;
}

void PrintProcessInfo()
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    int policy = sched_getscheduler(0);
    sched_param param{};
    sched_getparam(0, &param);

    cpu_set_t cpuSet{};
    CPU_ZERO(&cpuSet);
    pthread_getaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuSet);

    long cpuCount = sysconf(_SC_NPROCESSORS_ONLN);
    int cpuCurrent = sched_getcpu();

    std::cout << "---------------------- Process / Thread Info ----------------------\n";

    std::cout << "Pid: " << pid << std::endl;
    std::cout << "Tid: " << tid << std::endl;

    std::cout << "Scheduler class: " << GetSchedulerToString(policy) << std::endl;
    std::cout << "Thread priority: " << param.sched_priority << std::endl;

    PrintAffinityMask(&cpuSet);

    std::cout << "CPU count available: " << cpuCount << std::endl;
    std::cout << "Current CPU number: " << cpuCurrent << std::endl;

    std::cout << "------------------------------------------------------------------\n";
}

int main(int argc, char* argv[])
{
    if (argc != 1)
    {
        std::cerr << "Usage: ./Lab-05a\n";
        return 1;
    }

    PrintProcessInfo();

    return 0;
}
