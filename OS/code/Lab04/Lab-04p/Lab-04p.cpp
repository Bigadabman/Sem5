#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

struct ThreadParams {
    int lowerLimit;
    int upperLimit;
};

std::vector<int> globalPrimes;

DWORD tlsIndex = TLS_OUT_OF_INDEXES;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

DWORD WINAPI L4Primes(LPVOID lpParam) {

    ULONGLONG tStart = GetTickCount64(); 

    if (lpParam == nullptr) {
        return 1;
    }

    ThreadParams* pLimits = static_cast<ThreadParams*>(lpParam);
    ThreadParams limits = *pLimits;
    delete pLimits;

    std::vector<int>* primes = new std::vector<int>();
    if (TlsSetValue(tlsIndex, primes) == 0) {
        delete primes;
        return 2;
    }

    for (int i = limits.lowerLimit; i <= limits.upperLimit; ++i) {
        if (isPrime(i)) primes->push_back(i);
    }

    globalPrimes.insert(globalPrimes.end(), primes->begin(), primes->end());

    delete primes;
    TlsSetValue(tlsIndex, nullptr);

    ULONGLONG tEnd = GetTickCount64(); 

    printf("Поток %lu завершил работу за %llu мс\n",
        GetCurrentThreadId(), tEnd - tStart); 

    return 0;
}

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE* threads = nullptr;
    int threadAmount = 0;

    try {
        if (argc != 4) {
            throw std::invalid_argument("Некорректное количество аргументов. Использование: Lab-04p <threads> <low> <high>");
        }

        threadAmount = std::stoi(argv[1]);
        int lowerLimit = std::stoi(argv[2]);
        int upperLimit = std::stoi(argv[3]);

        if (threadAmount <= 0 || lowerLimit < 0 || upperLimit <= lowerLimit) {
            throw std::invalid_argument("Некорректные параметры");
        }


        tlsIndex = TlsAlloc();
        if (tlsIndex == TLS_OUT_OF_INDEXES) {
            throw std::runtime_error("TlsAlloc failed");
        }


        threads = new HANDLE[threadAmount];
        for (int i = 0; i < threadAmount; ++i) threads[i] = NULL;

        int baseRange = (upperLimit - lowerLimit + 1) / threadAmount;

        ULONGLONG appStart = GetTickCount64();

        for (int i = 0; i < threadAmount; ++i) {
            ThreadParams* limits = new ThreadParams;
            limits->lowerLimit = lowerLimit + i * baseRange;

            if (i == threadAmount - 1) limits->upperLimit = upperLimit;
            else limits->upperLimit = lowerLimit + (i + 1) * baseRange - 1;

            threads[i] = CreateThread(NULL, 0, L4Primes, limits, 0, NULL);

            if (threads[i] == NULL) {
                throw std::runtime_error("Не удалось создать поток");
            }
        }

        DWORD waitResult = WaitForMultipleObjects(threadAmount, threads, TRUE, INFINITE);
        if (waitResult == WAIT_FAILED) {
            throw std::runtime_error("WaitForMultipleObjects failed");
        }

        ULONGLONG appEnd = GetTickCount64(); 

        std::cout << "Общее время работы программы: "
            << (appEnd - appStart) << " мс\n";


      /*  std::sort(globalPrimes.begin(), globalPrimes.end());
        for (int v : globalPrimes) {
            std::cout << v << " ";
        }*/
        std::cout << std::endl;

        for (int i = 0; i < threadAmount; ++i) {
            if (threads[i] != NULL) CloseHandle(threads[i]);
        }

        delete[] threads;
        threads = nullptr;

        TlsFree(tlsIndex);
        tlsIndex = TLS_OUT_OF_INDEXES;

        std::cout << "Завершено успешно" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;

        if (threads != nullptr) {
            for (int i = 0; i < threadAmount; ++i)
                if (threads[i] != NULL) CloseHandle(threads[i]);
            delete[] threads;
        }

        if (tlsIndex != TLS_OUT_OF_INDEXES) TlsFree(tlsIndex);

        ExitProcess(1);
    }

    ExitProcess(0);
}
