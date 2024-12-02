#include "nonPrimeNumbers.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <future>

bool Policy::isPrime(int n) const {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= std::sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int seq_exec::hasNonPrime(const std::vector<int>& numbers) const {
    int result = 0;
    std::for_each(numbers.begin(), numbers.end(), [&result, this](int n) {if (!isPrime(n)) ++result;});
    return result;
}

int par_exec::hasNonPrime(const std::vector<int> &numbers) const {
    size_t threadCount;
    if (threads != 0) {
        threadCount = threads;
    }
    else threadCount = 4;

    std::vector<std::future<int>> futures;
    size_t chunkSize = (numbers.size() + threadCount - 1) / threadCount;

    for (size_t i = 0; i < threadCount; ++i) {
        size_t start = i * chunkSize;
        size_t end = std::min(start + chunkSize, numbers.size());

        if (start >= end) break;

        futures.push_back(std::async(std::launch::async, [start, end, &numbers, this]() {
            int result = 0;
            for (size_t j = start; j < end; ++j) {
                if (!isPrime(numbers[j])) {
                    ++result;
                }
            }
            return result;
        }));
    }

    int result = 0;
    for (auto& fut : futures) {
        result += fut.get();
    }
    return result;
}

int hasNonPrime(const std::vector<int>& numbers, const Policy& policy) {
    return policy.hasNonPrime(numbers);
}
