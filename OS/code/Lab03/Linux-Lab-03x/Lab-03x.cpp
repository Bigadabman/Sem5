#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

int main(int argc, char* argv[])
{
    int iterations = 0;

    if (argc > 1)
    {
        iterations = std::atoi(argv[1]);
    }
    else
    {
        const char* env_iter = std::getenv("ITER_NUM");

        if (env_iter != nullptr)
        {
            iterations = std::atoi(env_iter);
        }
    }

    if (iterations <= 0)
    {
        std::cerr << "Ошибка: не задано количество итераций ни через аргумент, ни через переменную окружения ITER_NUM" << std::endl;
        _exit(1);
    }

    pid_t pid = getpid();
    std::cout << "PID процесса: " << pid << std::endl;
    std::cout << "Количество итераций: " << iterations << std::endl;
    std::cout << "----------------------------------" << std::endl;

    for (int i = 1; i <= iterations; ++i)
    {
        std::cout << "Итерация " << i << " | PID = " << pid << std::endl;
        usleep(500 * 1000);
    }

    std::cout << "----------------------------------" << std::endl;

    _exit(0);
}
