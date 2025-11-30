#include <iostream>
#include <unistd.h>   
#include <vector>
#include <string>
#include <cstdlib>     
#include <cstring>      
#include <errno.h>      

bool isPrime(int num);

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    try {
        int lowerLimit;
        int upperLimit;

        
        if (argc > 2) {
            lowerLimit = atoi(argv[1]);
            upperLimit = atoi(argv[2]);
        }
        else {
            throw std::string("❌ Не все аргументы получены.");
        }

        if (lowerLimit >= upperLimit || lowerLimit < 0 || upperLimit < 0) {
            throw std::string("❌ Некорректные аргументы диапазона.");
        }

 
        std::vector<int> buffer;
        for (int i = lowerLimit; i <= upperLimit; i++) {
            if (isPrime(i))
                buffer.push_back(i);
        }

        if (buffer.empty()) {
            std::cout << "Простых чисел в диапазоне [" << lowerLimit << "; " << upperLimit << "] не найдено.\n";
            return 0;
        }

     
        std::string result;
        for (int num : buffer)
            result += std::to_string(num) + " ";

        result += "\n";


        ssize_t written = write(STDOUT_FILENO, result.c_str(), result.size());
        if (written == -1) {
            std::cerr << "Ошибка записи в канал: " << strerror(errno) << std::endl;
        }
        else {
            std::cerr << "Данные записаны в канал (" << written << " байт)\n";
        }
    }
    catch (std::string& err) {
        std::cerr << err << std::endl;
    }

    return 0;
}


bool isPrime(int num) {
    if (num < 2)
        return false;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }

    return true;
}
