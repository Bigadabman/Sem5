#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>

void* Lab_04x(void* arg) {
    int iterations = *(int*)arg;

    const char* username = "User-672a41d6";
    int nameLength = strlen(username);

    if (iterations < 0) {
        fprintf(stderr, "Количество итераций должно быть положительным\n");
        return nullptr;
    }

    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    for (int i = 0; i < iterations; i++) {
        char currentLetter = username[i % nameLength];
        printf("%d - %lu - %d - %c\n", pid, (unsigned long)tid, i, currentLetter);
        usleep(300000); 
    }

    return nullptr;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int iterations1 = 50;
    int iterations2 = 125;
    int iterationsMain = 100;

    pthread_t t1, t2;


    if (pthread_create(&t1, nullptr, Lab_04x, &iterations1) != 0) {
        std::cerr << "Ошибка создания первого потока\n";
        return 1;
    }

    if (pthread_create(&t2, nullptr, Lab_04x, &iterations2) != 0) {
        std::cerr << "Ошибка создания второго потока\n";
        return 1;
    }


    Lab_04x(&iterationsMain);


    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    std::cout << "Все потоки успешно завершены\n";
    return 0;
}
