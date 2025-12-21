#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>

pthread_mutex_t mutex;
pthread_cond_t cvNotFull;
pthread_cond_t cvNotEmpty;

const char* username = "User-672a41d6";

int BUFFER_MAX = 0;
int prodDelayMin = 0, prodDelayMax = 0;
int consDelayMin = 0, consDelayMax = 0;

int bufferCount = 0;

int producedTotal = 0;
int consumedTotal = 0;
int producedPeriod = 0;
int consumedPeriod = 0;

long producerWorkTime = 0;
long consumerWorkTime = 0;

long lastProdTime = 0;
long lastConsTime = 0;

long totalProdInterval = 0;
long totalConsInterval = 0;

long startTimeMs;


long GetTimeMs()
{
    timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int RandInRange(int a, int b)
{
    return a + rand() % (b - a + 1);
}

void* Producer(void*)
{
    while (true)
    {
        int delay = RandInRange(prodDelayMin, prodDelayMax);
        usleep(delay * 1000);
        producerWorkTime += delay;

        pthread_mutex_lock(&mutex);

        while (bufferCount == BUFFER_MAX)
        {
            std::cout << "[Производитель] Буфер полон -> блокировка\n";
            pthread_cond_wait(&cvNotFull, &mutex);
            std::cout << "[Производитель] Пробуждение\n";
        }

        bufferCount++;
        producedTotal++;
        producedPeriod++;

        long now = GetTimeMs();
        if (producedTotal > 1)
            totalProdInterval += (now - lastProdTime);
        lastProdTime = now;

        std::cout << "[Производитель] Добавлен элемент. Буфер = "
            << bufferCount << "\n";

        pthread_cond_signal(&cvNotEmpty);
        pthread_mutex_unlock(&mutex);
    }
}

void* Consumer(void*)
{
    while (true)
    {
        int delay = RandInRange(consDelayMin, consDelayMax);
        usleep(delay * 1000);
        consumerWorkTime += delay;

        pthread_mutex_lock(&mutex);

        while (bufferCount == 0)
        {
            std::cout << "[Потребитель] Буфер пуст -> блокировка\n";
            pthread_cond_wait(&cvNotEmpty, &mutex);
            std::cout << "[Потребитель] Пробуждение\n";
        }

        bufferCount--;
        consumedTotal++;
        consumedPeriod++;

        long now = GetTimeMs();
        if (consumedTotal > 1)
            totalConsInterval += (now - lastConsTime);
        lastConsTime = now;

        std::cout << "[Потребитель] Извлечён элемент. Буфер = "
            << bufferCount << "\n";

        pthread_cond_signal(&cvNotFull);
        pthread_mutex_unlock(&mutex);
    }
}

void* Statistics(void*)
{
    while (true)
    {
        sleep(5);

        pthread_mutex_lock(&mutex);

        long now = GetTimeMs();
        double elapsed = (now - startTimeMs) / 1000.0;

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
            << totalProdInterval / (double)(producedTotal - 1)
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
            << totalConsInterval / (double)(consumedTotal - 1)
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

        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 6)
    {
        std::cerr << "Использование:\n";
        std::cerr << "./Lab-06-conds [Буфер] [Prod min] [max] [Cons min] [max]\n";
        std::cerr << "Пример: ./Lab-06-conds 10 0 100 50 150\n";
        return 1;
    }

    BUFFER_MAX = atoi(argv[1]);
    prodDelayMin = atoi(argv[2]);
    prodDelayMax = atoi(argv[3]);
    consDelayMin = atoi(argv[4]);
    consDelayMax = atoi(argv[5]);

    srand(time(nullptr));

    std::cout << "Пользователь: " << username << "\n";
    std::cout << "Буфер: 0 / " << BUFFER_MAX << "\n\n";

    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cvNotFull, nullptr);
    pthread_cond_init(&cvNotEmpty, nullptr);

    startTimeMs = GetTimeMs();

    pthread_t prod, cons, stat;

    pthread_create(&prod, nullptr, Producer, nullptr);
    pthread_create(&cons, nullptr, Consumer, nullptr);
    pthread_create(&stat, nullptr, Statistics, nullptr);

    pthread_join(prod, nullptr);
    pthread_join(cons, nullptr);
    pthread_join(stat, nullptr);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cvNotFull);
    pthread_cond_destroy(&cvNotEmpty);

    return 0;
}
