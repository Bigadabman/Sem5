// Lab-04p-linux.cpp (верси€ с измерением производительности)
//  омпил€ци€: g++ Lab-04p-linux.cpp -o Lab-04p -pthread -std=c++17

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <time.h>

struct ThreadParams {
    int lower;
    int upper;
};

std::vector<int> globalPrimes;
pthread_key_t tlsKey;
pthread_once_t tlsKeyOnce = PTHREAD_ONCE_INIT;

// получить текущее врем€ в мс
static inline long long now_ms() {
    timespec ts{};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
}

void make_tls_key() {
    int rc = pthread_key_create(&tlsKey, [](void* p) {
        delete static_cast<std::vector<int>*>(p);
        });

    if (rc != 0) {
        std::cerr << "pthread_key_create failed: " << strerror(rc) << std::endl;
        std::abort();
    }
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

void* thread_func(void* arg) {
    pthread_once(&tlsKeyOnce, make_tls_key);

    long long tStart = now_ms();

    ThreadParams* params = static_cast<ThreadParams*>(arg);
    ThreadParams local = *params;
    delete params;

    auto* primes = new std::vector<int>();
    int rc = pthread_setspecific(tlsKey, primes);
    if (rc != 0) {
        std::cerr << "pthread_setspecific failed: " << strerror(rc) << std::endl;
        delete primes;
        return nullptr;
    }

    for (int x = local.lower; x <= local.upper; ++x)
        if (isPrime(x)) primes->push_back(x);

    globalPrimes.insert(globalPrimes.end(), primes->begin(), primes->end());

    long long tEnd = now_ms();

    std::cout << "ѕоток TID=" << syscall(SYS_gettid)
        << " диапазон [" << local.lower << ";" << local.upper << "]"
        << " Ч найдено " << primes->size() << " чисел"
        << " Ч врем€: " << (tEnd - tStart) << " мс\n";

    delete primes;
    pthread_setspecific(tlsKey, nullptr);

    return nullptr;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <threads> <lower> <upper>\n";
        return 1;
    }

    int threadsCount = std::stoi(argv[1]);
    int lower = std::stoi(argv[2]);
    int upper = std::stoi(argv[3]);

    if (threadsCount <= 0 || lower < 0 || upper <= lower) {
        std::cerr << "Invalid arguments\n";
        return 1;
    }

    std::vector<pthread_t> threads(threadsCount);

    long long appStart = now_ms();

    int baseRange = (upper - lower + 1) / threadsCount;

    for (int i = 0; i < threadsCount; ++i) {
        ThreadParams* p = new ThreadParams;
        p->lower = lower + i * baseRange;
        p->upper = (i == threadsCount - 1) ? upper : (lower + (i + 1) * baseRange - 1);

        int rc = pthread_create(&threads[i], nullptr, thread_func, p);
        if (rc != 0) {
            std::cerr << "pthread_create failed: " << strerror(rc) << std::endl;
            delete p;

            for (int j = 0; j < i; ++j) pthread_join(threads[j], nullptr);
            return 1;
        }
    }

    for (pthread_t& t : threads)
        pthread_join(t, nullptr);

    long long appEnd = now_ms();

    std::sort(globalPrimes.begin(), globalPrimes.end());

    std::cout << "\n»тог: найдено всего " << globalPrimes.size() << " простых чисел\n";
    std::cout << "ќбщее врем€ работы программы: " << (appEnd - appStart) << " мс\n";

    pthread_key_delete(tlsKey);

    return 0;
}
