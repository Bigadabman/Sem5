#include <iostream>
#include <vector>
#include <algorithm>

struct Task
{
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int startTime;
    int finishTime;
};

int main()
{
    std::vector<Task> tasks = {
        {1, 0, 80, 3, 80}, {2, 20, 45, 5, 45}, {3, 30, 60, 2, 60},
        {4, 50, 30, 4, 30}, {5, 70, 90, 1, 90}, {6, 100, 55, 3, 55},
        {7, 120, 75, 2, 75}, {8, 150, 40, 5, 40}, {9, 180, 65, 4, 65},
        {10, 200, 85, 1, 85}
    };

    int currentTime = 0;
    int totalBurst = 0;
    int lastFinish = 0;

    std::vector<Task> completed;

    while (completed.size() < tasks.size())
    {
        std::vector<Task*> available;
        for (auto& t : tasks)
            if (t.arrivalTime <= currentTime && t.remainingTime > 0)
                available.push_back(&t);

        if (available.empty())
        {
            currentTime++;
            continue;
        }

        Task* t = *std::min_element(available.begin(), available.end(),
            [](Task* a, Task* b) { return a->priority < b->priority; });

        if (t->remainingTime == t->burstTime)
            t->startTime = currentTime;

        t->remainingTime--;
        currentTime++;

        if (t->remainingTime == 0)
        {
            t->finishTime = currentTime;
            completed.push_back(*t);

            if (t->finishTime > lastFinish)
                lastFinish = t->finishTime;
        }
    }

    // вывод статистики
    double totalWaiting = 0;
    double totalTurnaround = 0;

    std::cout << "Task|Arrival| Burst |Priority| Start | Finish |Waiting|Turnaround\n";

    for (auto& t : completed)
    {
        int waiting = t.finishTime - t.arrivalTime - t.burstTime;
        int turnaround = t.finishTime - t.arrivalTime;

        totalWaiting += waiting;
        totalTurnaround += turnaround;
        totalBurst += t.burstTime;

        std::cout << t.id << "\t" << t.arrivalTime << "\t" << t.burstTime
            << "\t" << t.priority << "\t" << t.startTime << "\t"
            << t.finishTime << "\t" << waiting << "\t" << turnaround << "\n";
    }

    int n = completed.size();

    double avgBurst = static_cast<double>(totalBurst) / n;
    double throughput = static_cast<double>(n) / lastFinish;

    std::cout << "\nAverage burst time: " << avgBurst << "\n";
    std::cout << "Throughput: " << throughput << "\n";
    std::cout << "Average waiting time: " << totalWaiting / n << "\n";
    std::cout << "Average turnaround time: " << totalTurnaround / n << "\n";

    return 0;
}
