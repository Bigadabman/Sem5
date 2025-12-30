#include <iostream>
#include <Windows.h>
#include <thread>
#include <string>

std::string GetPriorityClassToString(DWORD priorityClass) {
    switch (priorityClass) {
    case ABOVE_NORMAL_PRIORITY_CLASS: return "ABOVE_NORMAL_PRIORITY_CLASS";
    case BELOW_NORMAL_PRIORITY_CLASS: return "BELOW_NORMAL_PRIORITY_CLASS";
    case HIGH_PRIORITY_CLASS: return "HIGH_PRIORITY_CLASS";
    case IDLE_PRIORITY_CLASS: return "IDLE_PRIORITY_CLASS";
    case NORMAL_PRIORITY_CLASS: return "NORMAL_PRIORITY_CLASS";
    case REALTIME_PRIORITY_CLASS: return "REALTIME_PRIORITY_CLASS";
    }
    return "No class";
}

std::string GetThreadPriorityToString(int prio)
{
    switch (prio)
    {
    case THREAD_PRIORITY_IDLE: return "THREAD_PRIORITY_IDLE";
    case THREAD_PRIORITY_LOWEST: return "THREAD_PRIORITY_LOWEST";
    case THREAD_PRIORITY_BELOW_NORMAL: return "THREAD_PRIORITY_BELOW_NORMAL";
    case THREAD_PRIORITY_NORMAL: return "THREAD_PRIORITY_NORMAL";
    case THREAD_PRIORITY_ABOVE_NORMAL: return "THREAD_PRIORITY_ABOVE_NORMAL";
    case THREAD_PRIORITY_HIGHEST: return "THREAD_PRIORITY_HIGHEST";
    case THREAD_PRIORITY_TIME_CRITICAL: return "THREAD_PRIORITY_TIME_CRITICAL";
    default: return "UNKNOWN_PRIORITY";
    }
}

std::string MaskToBinaryString(uint64_t mask, unsigned int showBits = 16)
{
    std::string s;
    for (int i = showBits - 1; i >= 0; --i) {
        s += ((mask >> i) & 1ULL) ? '1' : '0';
        if (i % 8 == 0 && i != 0) s += ' ';
    }
    return s;
}


int GetThreadPriorityProcessExplorer(DWORD processPriorityClass, int threadPriority)
{
    int basePriority = 0;


    switch (processPriorityClass)
    {
    case IDLE_PRIORITY_CLASS:          basePriority = 4;  break;
    case BELOW_NORMAL_PRIORITY_CLASS:  basePriority = 6;  break;
    case NORMAL_PRIORITY_CLASS:        basePriority = 8;  break;
    case ABOVE_NORMAL_PRIORITY_CLASS:  basePriority = 10; break;
    case HIGH_PRIORITY_CLASS:          basePriority = 13; break;
    case REALTIME_PRIORITY_CLASS:      basePriority = 24; break;
    default:                           basePriority = 8;  break;
    }

    int relativePriority = 0;

    switch (threadPriority)
    {
    case THREAD_PRIORITY_IDLE:           relativePriority = -15; break;
    case THREAD_PRIORITY_LOWEST:         relativePriority = -2;  break;
    case THREAD_PRIORITY_BELOW_NORMAL:   relativePriority = -1;  break;
    case THREAD_PRIORITY_NORMAL:         relativePriority = 0;   break;
    case THREAD_PRIORITY_ABOVE_NORMAL:   relativePriority = 1;   break;
    case THREAD_PRIORITY_HIGHEST:        relativePriority = 2;   break;
    case THREAD_PRIORITY_TIME_CRITICAL:  relativePriority = 15;  break;
    default:                             relativePriority = 0;   break;
    }

    return basePriority + relativePriority;
}



unsigned int CountBits(uint64_t x)
{
    unsigned int counter = 0;
    while (x) {
        if (x & 1) counter++;
        x >>= 1;
    }
    return counter;
}

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    std::cout << "Pid: " << GetCurrentProcessId() << std::endl;
    std::cout << "Tid: " << GetCurrentThreadId() << std::endl;

    HANDLE proc = GetCurrentProcess();
    std::cout << "Priority class: "
        << GetPriorityClassToString(GetPriorityClass(proc)) << std::endl;

    HANDLE thread = GetCurrentThread();
    int pr = GetThreadPriority(thread);

    int pePriority = GetThreadPriorityProcessExplorer(GetPriorityClass(proc), pr);

    std::cout << "Thread priority: " << pePriority
        << " (" << GetThreadPriorityToString(pr) << ")" << std::endl;

    DWORD_PTR procMask;
    DWORD_PTR sysMask;

    if (!GetProcessAffinityMask(proc, &procMask, &sysMask))
    {
        std::cout << "failed to get affinity mask\n";
        return 1;
    }

    std::cout << "Process affinity mask: " << MaskToBinaryString(procMask) << std::endl;
    std::cout << "System affinity mask: " << MaskToBinaryString(sysMask) << std::endl;

    std::cout << "Processors available for process: " << CountBits(procMask) << std::endl;
    std::cout << "Total processor amount: " << CountBits(sysMask) << std::endl;

    std::cout << "Processor number: " << GetCurrentProcessorNumber() << std::endl;

    return 0;
}
