#include <Windows.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

int THREAD_COUNT = 0;
int MATRIX_COUNT = 0;
int MATRIX_SIZE = 0;

int*** matrices = nullptr;

volatile LONG64 globalSum = 0;

SYNCHRONIZATION_BARRIER barrier;


int RandomValue()
{
    return rand() % 4001 - 2000;
}


DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
    int threadId = (int)(INT_PTR)lpParam;

    LONG64 localSum = 0;

    for (int k = threadId; k < MATRIX_COUNT; k += THREAD_COUNT)
    {
        for (int i = 0; i < MATRIX_SIZE; i++)
        {
            for (int j = 0; j < MATRIX_SIZE; j++)
            {
                localSum += matrices[k][i][j];
            }
        }
    }

    std::cout << "Поток " << threadId
        << " посчитал частичную сумму = "
        << localSum << std::endl;

    EnterSynchronizationBarrier(&barrier, 0);

    InterlockedAdd64(&globalSum, localSum);

    EnterSynchronizationBarrier(&barrier, 0);

    return 0;
}


int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc != 4)
    {
        std::cerr << "Использование: Lab-06-bar [потоки] [матрицы] [размер]\n";
        return 1;
    }

    THREAD_COUNT = atoi(argv[1]);
    MATRIX_COUNT = atoi(argv[2]);
    MATRIX_SIZE = atoi(argv[3]);

    srand(time(nullptr));

    matrices = new int** [MATRIX_COUNT];

    for (int k = 0; k < MATRIX_COUNT; k++)
    {
        matrices[k] = new int* [MATRIX_SIZE];
        for (int i = 0; i < MATRIX_SIZE; i++)
        {
            matrices[k][i] = new int[MATRIX_SIZE];
            for (int j = 0; j < MATRIX_SIZE; j++)
            {
                matrices[k][i][j] = RandomValue();
            }
        }
    }

    std::cout << "Матрицы сгенерированы\n\n";

    InitializeSynchronizationBarrier(&barrier, THREAD_COUNT, -1);

    HANDLE* threads = new HANDLE[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threads[i] = CreateThread(
            nullptr,
            0,
            ThreadFunc,
            (LPVOID)(INT_PTR)i,
            0,
            nullptr
        );
    }

    WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);

    std::cout << "\n----РЕЗУЛЬТАТ----\n";
    std::cout << "Сумма всех элементов всех матриц = "
        << globalSum << std::endl;

    DeleteSynchronizationBarrier(&barrier);

    for (int i = 0; i < THREAD_COUNT; i++)
        CloseHandle(threads[i]);

    delete[] threads;

    for (int k = 0; k < MATRIX_COUNT; k++)
    {
        for (int i = 0; i < MATRIX_SIZE; i++)
            delete[] matrices[k][i];
        delete[] matrices[k];
    }
    delete[] matrices;

    system("pause");
    return 0;
}
