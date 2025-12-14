#include <iostream>
#include <vector>
#include <queue>

struct Task
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int startTime;
    int finishTime;
};

int main()
{
    int quantum = 30;

    std::vector<Task> tasks = {
        {1, 0, 80, 80}, {2, 20, 45, 45}, {3, 30, 60, 60}, {4, 50, 30, 30},
        {5, 70, 90, 90}, {6, 100, 55, 55}, {7, 120, 75, 75}, {8, 150, 40, 40},
        {9, 180, 65, 65}, {10, 200, 85, 85}
    };

    int currentTime = 0;
    std::queue<int> readyQueue;
    std::vector<Task> completed;
    std::vector<bool> inQueue(tasks.size(), false);

    while (completed.size() < tasks.size())
    {
        for (size_t i = 0; i < tasks.size(); i++)
            if (tasks[i].arrivalTime <= currentTime && !inQueue[i] && tasks[i].remainingTime > 0)
            {
                readyQueue.push(i);
                inQueue[i] = true;
            }

        if (readyQueue.empty())
        {
            currentTime++;
            continue;
        }

        int idx = readyQueue.front();
        readyQueue.pop();

        Task& t = tasks[idx];
        if (t.remainingTime == t.burstTime)
            t.startTime = currentTime;

        int execTime = std::min(quantum, t.remainingTime);
        t.remainingTime -= execTime;
        currentTime += execTime;

        for (size_t i = 0; i < tasks.size(); i++)
            if (tasks[i].arrivalTime <= currentTime && !inQueue[i] && tasks[i].remainingTime > 0)
            {
                readyQueue.push(i);
                inQueue[i] = true;
            }

        if (t.remainingTime > 0)
            readyQueue.push(idx);
        else
        {
            t.finishTime = currentTime;
            completed.push_back(t);
        }
    }

    double totalWaiting = 0;
    double totalTurnaround = 0;
    double totalBurst = 0;
    int lastFinish = 0;

    std::cout << "Task |Arrival| Burst | Start | Finish |Waiting| Turnaround\n";

    for (auto& t : completed)
    {
        int waiting = t.finishTime - t.arrivalTime - t.burstTime;
        int turnaround = t.finishTime - t.arrivalTime;

        totalWaiting += waiting;
        totalTurnaround += turnaround;
        totalBurst += t.burstTime;
        if (t.finishTime > lastFinish) lastFinish = t.finishTime;

        std::cout << t.id << "\t" << t.arrivalTime << "\t" << t.burstTime
            << "\t" << t.startTime << "\t" << t.finishTime
            << "\t" << waiting << "\t" << turnaround << "\n";
    }

    int n = completed.size();

    double avgBurst = totalBurst / n;
    double throughput = static_cast<double>(n) / lastFinish;

    std::cout << "\nAverage burst time: " << avgBurst << "\n";
    std::cout << "Throughput: " << throughput << "\n";
    std::cout << "Average waiting time: " << totalWaiting / n << "\n";
    std::cout << "Average turnaround time: " << totalTurnaround / n << "\n";

    return 0;
}
