#include <iostream>
#include <unistd.h>      
#include <sys/wait.h>    
#include <vector>
#include <cstring>       
#include <cstdlib>       
#include <errno.h>       

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    try {
        int processesAmount;
        int lowerLimit;
        int upperLimit;

        
        if (argc > 3) {
            processesAmount = atoi(argv[1]);
            lowerLimit = atoi(argv[2]);
            upperLimit = atoi(argv[3]);
        } else {
            throw std::string("❌ Не все аргументы получены");
        }
        

        if (processesAmount <= 0 || lowerLimit >= upperLimit || lowerLimit < 0 || upperLimit < 0)
            throw std::string("Некорректные аргументы");

        std::cout << "Канал связи будет создан..." << std::endl;

        int fd[2];
        if (pipe(fd) == -1) {
            std::cerr << "Ошибка создания канала: " << strerror(errno) << std::endl;
            exit(1);
        }

        std::cout << "Канал связи создан.\n";

        std::vector<pid_t> children;
        int range = (upperLimit - lowerLimit + 1) / processesAmount;

        for (int i = 0; i < processesAmount; ++i) {
            int procLower = lowerLimit + i * range;
            int procUpper = (i == processesAmount - 1)
                ? upperLimit
                : lowerLimit + (i + 1) * range - 1;

            pid_t pid = fork();

            if (pid == -1) {
                std::cerr << "Ошибка fork() при создании процесса #" << i << ": "
                    << strerror(errno) << std::endl;
                exit(1);
            }
            else if (pid == 0) {
                
                close(fd[0]); 
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);

               
                char lowerStr[16], upperStr[16];
                sprintf(lowerStr, "%d", procLower);
                sprintf(upperStr, "%d", procUpper);

                execl("./Lab-03d-client", "./Lab-03d-client", lowerStr, upperStr, (char*)NULL);

                
                std::cerr << "Ошибка exec: " << strerror(errno) << std::endl;
                _exit(1);
            }
            else {
               
                children.push_back(pid);
                std::cout << "Запущен процесс #" << i
                    << ". Диапазон [" << procLower << "; " << procUpper << "] PID=" << pid << std::endl;
            }
        }

       
        close(fd[1]);
        char buffer[256];
        ssize_t bytesRead;

        std::cout << "\nЧтение данных от дочерних процессов:\n";
        while ((bytesRead = read(fd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytesRead] = '\0';
            std::cout << buffer;
        }

        close(fd[0]);

        for (pid_t pid : children) {
            waitpid(pid, NULL, 0);
        }

        std::cout << "\nВсе дочерние процессы завершены." << std::endl;
    }
    catch (std::string& err) {
        std::cerr << err << std::endl;
    }

    return 0;
}
