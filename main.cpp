#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include "nonPrimeNumbers.h"

int main() {
    std::vector<int> numbers(100000000);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    std::generate(numbers.begin(), numbers.end(), [&]() { return dist(gen); });

    //std::vector<int> numbers = {3, 5, 6, 9, 11, 13, 0, 20, 23, 16, 1, 2};

    // Seq
    auto start = std::chrono::high_resolution_clock::now();
    int hasNonPrimeSeq = hasNonPrime(numbers);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Sequential result: " << hasNonPrimeSeq << std::endl;
    const std::chrono::duration<double> diff = end - start;
    std::cout << "Seq speed: " << diff.count() << std::endl;

    // Par
    start = std::chrono::high_resolution_clock::now();
    int hasNonPrimePar = hasNonPrime(numbers, par_exec());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel result: " << hasNonPrimePar << std::endl;
    const std::chrono::duration<double> diff2 = end - start;
    std::cout << "Par speed: " << diff2.count() << std::endl;

    double speeddiff = diff2.count()/diff.count();
    std::cout << "Par/Seq: " << speeddiff << std::endl;
    std::cout << "Seq/Par: " << 1/speeddiff << std::endl;

    return 0;
}
