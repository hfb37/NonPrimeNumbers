#include "nonPrimeNumbers.h"
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= std::sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

TEST(tests, smallTest) {
    std::cout << "small(10) test" << std::endl;

    std::vector<int> vec = {5, 6, 9, 13, 0, 20, 23, 16, 1, 2}; // 6 non-prime numbers

    auto start = std::chrono::high_resolution_clock::now();
    int nonPrime = hasNonPrime(vec);                        // seq policy by default
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = finish - start;
    std::cout << "Seq time: " << diff.count() << std::endl;
    EXPECT_EQ(6, nonPrime);

    start = std::chrono::high_resolution_clock::now();
    nonPrime = hasNonPrime(vec, par_exec());            // par policy
    finish = std::chrono::high_resolution_clock::now();
    diff = finish - start;
    std::cout << "Par time: " << diff.count() << std::endl;
    EXPECT_EQ(6, nonPrime);
}

TEST(tests, emptyTest) {
    std::cout << "empty test" << std::endl;

    std::vector<int> vec{};

    auto start = std::chrono::high_resolution_clock::now();
    int nonPrime = hasNonPrime(vec);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = finish - start;
    std::cout << "Seq time: " << diff.count() << std::endl;
    EXPECT_EQ(0, nonPrime);

    start = std::chrono::high_resolution_clock::now();
    nonPrime = hasNonPrime(vec, par_exec());
    finish = std::chrono::high_resolution_clock::now();
    diff = finish - start;
    std::cout << "Par time: " << diff.count() << std::endl;
    EXPECT_EQ(0, nonPrime);
}

TEST(tests, mediumRandTest) {
    std::cout << "medium(100k) rand test" << std::endl;

    std::vector<int> vec(100000); // 100k
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    std::generate(vec.begin(), vec.end(), [&]() { return dist(gen); });

    int real_result = 0;
    std::for_each(vec.begin(), vec.end(), [&real_result](int n){if (!isPrime(n)) real_result++;});

    auto start = std::chrono::high_resolution_clock::now();
    int nonPrime = hasNonPrime(vec);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = finish - start;
    std::cout << "Seq time: " << diff.count() << std::endl;
    EXPECT_EQ(real_result, nonPrime);

    start = std::chrono::high_resolution_clock::now();
    nonPrime = hasNonPrime(vec, par_exec());
    finish = std::chrono::high_resolution_clock::now();
    diff = finish - start;
    std::cout << "Par time: " << diff.count() << std::endl;
    EXPECT_EQ(real_result, nonPrime);
}

TEST(tests, bigRandTest) {
    std::cout << "big(100m) rand test" << std::endl;

    std::vector<int> vec(100000000); // 100k
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    std::generate(vec.begin(), vec.end(), [&]() { return dist(gen); });

    int real_result = 0;
    std::for_each(vec.begin(), vec.end(), [&real_result](int n){if (!isPrime(n)) real_result++;});

    auto start = std::chrono::high_resolution_clock::now();
    int nonPrime = hasNonPrime(vec);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = finish - start;
    std::cout << "Seq time: " << diff.count() << std::endl;
    EXPECT_EQ(real_result, nonPrime);

    start = std::chrono::high_resolution_clock::now();
    nonPrime = hasNonPrime(vec, par_exec());
    finish = std::chrono::high_resolution_clock::now();
    diff = finish - start;
    std::cout << "Par time: " << diff.count() << std::endl;
    EXPECT_EQ(real_result, nonPrime);
}