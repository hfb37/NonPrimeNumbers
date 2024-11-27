cmake_minimum_required(VERSION 3.30)

project(n3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)

add_executable(n3 main.cpp
                nonPrimeNumbers.h
                nonPrimeNumbers.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(
        tests
        nonPrimeNumbers.h
        nonPrimeNumbers.cpp
        gtests.cpp
)

target_link_libraries(
        tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

enable_testing()
