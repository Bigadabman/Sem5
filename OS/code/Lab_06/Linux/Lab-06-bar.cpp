#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>

int THREAD_COUNT = 0;
int MATRIX_COUNT = 0;
int MATRIX_SIZE = 0;

int*** matrices = nullptr;

volatile long long globalSum = 0;

pthread_barrier_t barrier;


int RandomValue()
{
    return rand() % 4001 - 2000;
}

void* ThreadFunc(void* arg)
{
    int threadId = *(int*)arg;

    long long localSum = 0;

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


    pthread_barrier_wait(&barrier);


    __sync_fetch_and_add(&globalSum, localSum);


    pthread_barrier_wait(&barrier);

    return nullptr;
}

int main(int argc, char* argv[])
{
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

    pthread_barrier_init(&barrier, nullptr, THREAD_COUNT);

    pthread_t* threads = new pthread_t[THREAD_COUNT];
    int* threadIds = new int[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threadIds[i] = i;
        pthread_create(
            &threads[i],
            nullptr,
            ThreadFunc,
            &threadIds[i]
        );
    }

    for (int i = 0; i < THREAD_COUNT; i++)
        pthread_join(threads[i], nullptr);

    std::cout << "\n----РЕЗУЛЬТАТ----\n";
    std::cout << "Сумма всех элементов всех матриц = "
        << globalSum << std::endl;

    pthread_barrier_destroy(&barrier);

    delete[] threads;
    delete[] threadIds;


    for (int k = 0; k < MATRIX_COUNT; k++)
    {
        for (int i = 0; i < MATRIX_SIZE; i++)
            delete[] matrices[k][i];
        delete[] matrices[k];
    }
    delete[] matrices;

    return 0;
}
