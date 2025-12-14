#include <iostream>
#include <vector>
#include <algorithm>

struct Task
{
    int id;
    int arrivalTime;
    int burstTime;
    int startTime;
    int finishTime;
};

int main()
{
    std::vector<Task> tasks = {
        {1, 0, 80}, {2, 20, 45}, {3, 30, 60}, {4, 50, 30},
        {5, 70, 90}, {6, 100, 55}, {7, 120, 75}, {8, 150, 40},
        {9, 180, 65}, {10, 200, 85}
    };

    int currentTime = 0;
    int totalBurst = 0;
    int lastFinish = 0;

    std::vector<Task> completed;

    while (!tasks.empty())
    {
        // задачи, уже поступившие в систему
        std::vector<Task> available;
        for (auto& t : tasks)
            if (t.arrivalTime <= currentTime)
                available.push_back(t);

        // если нет доступных задач — увеличиваем время
        if (available.empty())
        {
            currentTime++;
            continue;
        }

        // выбираем задачу с минимальным burst time — SJF
        auto it = std::min_element(available.begin(), available.end(),
            [](const Task& a, const Task& b)
            {
                return a.burstTime < b.burstTime;
            });

        Task t = *it;
        t.startTime = currentTime;
        t.finishTime = currentTime + t.burstTime;
        currentTime += t.burstTime;

        completed.push_back(t);

        if (t.finishTime > lastFinish)
            lastFinish = t.finishTime;

        // удаляем выполненную задачу
        tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
            [t](const Task& x) { return x.id == t.id; }),
            tasks.end());
    }

    // вывод статистики
    double totalWaiting = 0;
    double totalTurnaround = 0;

    std::cout << "Task |Arrival| Burst | Start | Finish |Waiting|Turnaround\n";
    for (auto& t : completed)
    {
        int waiting = t.startTime - t.arrivalTime;
        int turnaround = t.finishTime - t.arrivalTime;

        totalWaiting += waiting;
        totalTurnaround += turnaround;
        totalBurst += t.burstTime;

        std::cout << t.id << "\t" << t.arrivalTime << "\t" << t.burstTime
            << "\t" << t.startTime << "\t" << t.finishTime
            << "\t" << waiting << "\t" << turnaround << "\n";
    }

    int n = completed.size();
    double avgBurst = (double)totalBurst / n;
    double throughput = (double)n / lastFinish;

    std::cout << "\nAverage burst time: " << avgBurst << "\n";
    std::cout << "Throughput: " << throughput << "\n";
    std::cout << "Average waiting time: " << totalWaiting / n << "\n";
    std::cout << "Average turnaround time: " << totalTurnaround / n << "\n";

    return 0;
}
