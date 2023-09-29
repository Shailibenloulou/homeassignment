#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

constexpr size_t ITERATIONS = 1000 * 1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;

size_t sum = 0;

//shifting from serial to parallel execution requires us to ensure that sum is updated correctly by multiple threads and is well synchronized
//which is why i used Mutex to ensure that only one thread accesses a shared resource at a time.
std::mutex gMutex;

void operation1(size_t arg) {
    std::cout << "Performing operation1" << std::endl;
    size_t gSum = 0;
    for (size_t i = 0; i < ITERATIONS; i++) {
        gSum += (arg + i);
    }

    std::lock_guard<std::mutex> lock(gMutex); //we will lock the mutex before we update the shared gSum
    sum += gSum;

    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Operation1 Performed" << std::endl;
}

void operation2(size_t arg) {
    std::cout << "Performing operation2" << std::endl;
    size_t gSum = 0;
    for (size_t i = 0; i < ITERATIONS; i++) {
        gSum += (arg * i);
    }

    std::lock_guard<std::mutex> lock(gMutex); //same as operation1
    sum += gSum;

    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "Operation2 Performed" << std::endl;
}

int main(int argc, char** argv)
{
    auto start = std::chrono::steady_clock::now();

    //we will create two threads to execute operation1 and operation2 concurrently and join them to wait for their completion
    std::thread t1(operation1, OP1_PARAM);
    std::thread t2(operation2, OP2_PARAM);
    t1.join();
    t2.join();

    auto end = std::chrono::steady_clock::now();

    std::cout << "Total execution duration in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    std::cout << "Result: " << sum << ", " << (sum == EXPECTED_SUM ? "success" : "failure!") << std::endl;
    std::cout << "Press enter to exit" << std::endl;
    getchar();
    return 0;
}