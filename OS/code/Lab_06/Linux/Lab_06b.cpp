#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <cstring>

const char* SEM_NAME = "/lab06_semaphore";

const char* username = "User-672a41d6";
int nameLength = strlen(username);

void printInfo(const char* name)
{
    sem_t* sem = sem_open(SEM_NAME, 0);
    if (sem == SEM_FAILED)
    {
        std::cerr << "Не удалось открыть семафор\n";
        return;
    }

    for (int i = 0; i < 90; i++)
    {
        if (i == 30)
        {
            sem_wait(sem);
        }

        std::cout << name << " "
            << username[i % nameLength]
            << " " << i << std::endl;

        if (i == 60)
        {
            sem_post(sem);
        }

        usleep(100000); 
    }

    sem_close(sem);
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "RU");
    if (argc != 2)
    {
        std::cerr << "Использование: ./Lab_06b 0/1 (родитель/дочерний)\n";
        return 1;
    }

    int mode = atoi(argv[1]);

    if (mode == 1)
    {

        printInfo("Child");
        return 0;
    }



    sem_t* sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0666, 1);
    if (sem == SEM_FAILED)
    {
        std::cerr << "Не удалось создать семафор\n";
        return 1;
    }

    pid_t p1 = fork();
    if (p1 == 0)
    {
        execl("./Lab_06b", "./Lab_06b", "1", nullptr);
        _exit(1);
    }

    pid_t p2 = fork();
    if (p2 == 0)
    {
        execl("./Lab_06b", "./Lab_06b", "1", nullptr);
        _exit(1);
    }


    printInfo("Main");

    waitpid(p1, nullptr, 0);
    waitpid(p2, nullptr, 0);

    sem_close(sem);
    sem_unlink(SEM_NAME);

    return 0;
}
