#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>

pthread_mutex_t mutex;

const char* username = "User-672a41d6";
int nameLength = strlen(username);

void* printInfo(void* arg)
{
    const char* threadName = static_cast<const char*>(arg);

    for (int i = 0; i < 90; i++)
    {
        if (i == 30)
        {
            pthread_mutex_lock(&mutex);
        }

        std::cout << threadName
            << username[i % nameLength]
            << " " << i << std::endl;

        if (i == 60)
        {
            pthread_mutex_unlock(&mutex);
        }

        usleep(100000);
    }

    return nullptr;
}

int main()
{
    pthread_t threads[3];

    pthread_mutex_init(&mutex, nullptr);

    pthread_create(&threads[0], nullptr, printInfo, (void*)"A:");
    pthread_create(&threads[1], nullptr, printInfo, (void*)"B:");
    pthread_create(&threads[2], nullptr, printInfo, (void*)"Main:");

    for (int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], nullptr);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
