#include <iostream>
#include <unistd.h>   
#include <sys/wait.h> 
#include <cstdlib>    
#include <cstring>    
#include <errno.h>    

int main(int argc, char* argv[]) {

    const char* programPath = "./Lab-03x";
    const char* iterValue = "10";        

    pid_t pid1, pid2;


    std::cout << "Запуск первого процесса (аргумент через командную строку): "
        << programPath << " " << iterValue << std::endl;

    pid1 = fork();
    if (pid1 == 0) {

        execl(programPath, programPath, iterValue, (char*)NULL);
        std::cerr << "Ошибка execl: " << strerror(errno) << std::endl;
        _exit(1);
    }
    else if (pid1 < 0) {
        std::cerr << "Ошибка fork() при создании первого процесса: " << strerror(errno) << std::endl;
        exit(1);
    }


    std::cout << "Запуск второго процесса (аргумент через переменную окружения ITER_NUM="
        << iterValue << ")" << std::endl;

    if (setenv("ITER_NUM", iterValue, 1) != 0) {
        std::cerr << "Ошибка setenv: " << strerror(errno) << std::endl;
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {

        extern char** environ;
        execle(programPath, programPath, (char*)NULL, environ);
        std::cerr << "Ошибка execle: " << strerror(errno) << std::endl;
        _exit(1);
    }
    else if (pid2 < 0) {
        std::cerr << "Ошибка fork() при создании второго процесса: " << strerror(errno) << std::endl;
        exit(1);
    }


    int status1, status2;
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    std::cout << "\nПервый процесс завершён со статусом: " << status1 << std::endl;
    std::cout << "Второй процесс завершён со статусом: " << status2 << std::endl;

    std::cout << "\nВсе дочерние процессы завершены." << std::endl;

    return 0;
}
