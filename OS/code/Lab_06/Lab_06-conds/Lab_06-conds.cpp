#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

CRITICAL_SECTION cs;
CONDITION_VARIABLE cvNotFull;
CONDITION_VARIABLE cvNotEmpty;

const char* username = "User-672a41d6";

int BUFFER_MAX = 0;
int prodDelayMin = 0, prodDelayMax = 0;
int consDelayMin = 0, consDelayMax = 0;

int bufferCount = 0;

int producedTotal = 0;
int consumedTotal = 0;
int producedPeriod = 0;
int consumedPeriod = 0;

DWORD producerWorkTime = 0;
DWORD consumerWorkTime = 0;

DWORD lastProdTime = 0;
DWORD lastConsTime = 0;

DWORD totalProdInterval = 0;
DWORD totalConsInterval = 0;

DWORD startTime;


int RandInRange(int a, int b)
{
    return a + rand() % (b - a + 1);
}


DWORD WINAPI Producer(LPVOID)
{
    while (true)
    {
        int delay = RandInRange(prodDelayMin, prodDelayMax);
        Sleep(delay);

        EnterCriticalSection(&cs);

        while (bufferCount == BUFFER_MAX)
        {
            std::cout << "[Производитель] Буфер полон -> блокировка\n";
            SleepConditionVariableCS(&cvNotFull, &cs, INFINITE);
            std::cout << "[Производитель] Пробуждение\n";
        }

        bufferCount++;
        producedTotal++;
        producedPeriod++;

        DWORD now = GetTickCount();

        if (producedTotal > 1)
            totalProdInterval += (now - lastProdTime);

        lastProdTime = now;
        producerWorkTime += delay;

        std::cout << "[Производитель] Добавлен элемент. Буфер = "
            << bufferCount << "\n";

        WakeConditionVariable(&cvNotEmpty);
        LeaveCriticalSection(&cs);
    }
}


DWORD WINAPI Consumer(LPVOID)
{
    while (true)
    {
        int delay = RandInRange(consDelayMin, consDelayMax);
        Sleep(delay);

        EnterCriticalSection(&cs);

        while (bufferCount == 0)
        {
            std::cout << "[Потребитель] Буфер пуст -> блокировка\n";
            SleepConditionVariableCS(&cvNotEmpty, &cs, INFINITE);
            std::cout << "[Потребитель] Пробуждение\n";
        }

        bufferCount--;
        consumedTotal++;
        consumedPeriod++;

        DWORD now = GetTickCount();

        if (consumedTotal > 1)
            totalConsInterval += (now - lastConsTime);

        lastConsTime = now;
        consumerWorkTime += delay;

        std::cout << "[Потребитель] Извлечён элемент. Буфер = "
            << bufferCount << "\n";

        WakeConditionVariable(&cvNotFull);
        LeaveCriticalSection(&cs);
    }
}


DWORD WINAPI Statistics(LPVOID)
{
    while (true)
    {
        Sleep(5000);

        EnterCriticalSection(&cs);

        DWORD now = GetTickCount();
        double elapsed = (now - startTime) / 1000.0;

        std::cout << "\n------- Статистика ---------\n";
        std::cout << "Время работы приложения: " << elapsed << " с\n";

        std::cout << "Произведено всего: " << producedTotal << "\n";
        std::cout << "Потреблено всего: " << consumedTotal << "\n";

        std::cout << "Элементов в буфере: " << bufferCount << "\n";
        std::cout << "Заполнение буфера: "
            << (bufferCount * 100.0 / BUFFER_MAX) << "%\n";

        std::cout << "Произведено за период: " << producedPeriod << "\n";

        if (producedTotal > 1)
            std::cout << "Среднее время между производством: "
            << (totalProdInterval / (double)(producedTotal - 1))
            << " мс\n";
        else
            std::cout << "Среднее время между производством: 0 мс\n";

        std::cout << "Скорость производства: "
            << producedPeriod / 5.0 << " эл/с\n";

        std::cout << "Общее время работы производителя: "
            << producerWorkTime / 1000.0 << " с\n";

        std::cout << "Потреблено за период: " << consumedPeriod << "\n";

        if (consumedTotal > 1)
            std::cout << "Среднее время обработки элемента: "
            << (totalConsInterval / (double)(consumedTotal - 1))
            << " мс\n";
        else
            std::cout << "Среднее время обработки элемента: 0 мс\n";

        std::cout << "Скорость потребления: "
            << consumedPeriod / 5.0 << " эл/с\n";

        std::cout << "Общее время работы потребителя: "
            << consumerWorkTime / 1000.0 << " с\n";

        std::cout << "-----------------------------\n\n";

        producedPeriod = 0;
        consumedPeriod = 0;

        LeaveCriticalSection(&cs);
    }
}


int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc != 6)
    {
        std::cerr << "Использование:\n";
        std::cerr << "Lab-06-conds [Размер буфера] [Задержка производителя min] [max] [Задержка потребителя min] [max]\n";
        std::cerr << "Пример: Lab-06-conds 10 0 100 50 150\n";
        return 1;
    }

    BUFFER_MAX = atoi(argv[1]);
    prodDelayMin = atoi(argv[2]);
    prodDelayMax = atoi(argv[3]);
    consDelayMin = atoi(argv[4]);
    consDelayMax = atoi(argv[5]);

    srand((unsigned)time(nullptr));

    std::cout << "Пользователь: " << username << "\n";
    std::cout << "Буфер: 0 / " << BUFFER_MAX << "\n\n";

    InitializeCriticalSection(&cs);
    InitializeConditionVariable(&cvNotFull);
    InitializeConditionVariable(&cvNotEmpty);

    startTime = GetTickCount();

    HANDLE hProd = CreateThread(nullptr, 0, Producer, nullptr, 0, nullptr);
    HANDLE hCons = CreateThread(nullptr, 0, Consumer, nullptr, 0, nullptr);
    HANDLE hStat = CreateThread(nullptr, 0, Statistics, nullptr, 0, nullptr);

    WaitForSingleObject(hProd, INFINITE);
    WaitForSingleObject(hCons, INFINITE);
    WaitForSingleObject(hStat, INFINITE);

    DeleteCriticalSection(&cs);
    return 0;
}
