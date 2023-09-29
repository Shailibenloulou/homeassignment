#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <memory> 

struct Payload {
    Payload(uint64_t id_) :
        id(id_),
        veryLargeVector(1000 * 1000)
    {}

    uint64_t id;
    std::vector<int> veryLargeVector;
};

void operation1(std::shared_ptr<Payload> payload) {
    std::cout << "Performing operation1 on payload " << payload->id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));  
    std::cout << "Operation1 Performed" << std::endl;
}

void operation2(std::shared_ptr<Payload> payload) {
    std::cout << "Performing operation2 on payload " << payload->id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1)))); 
    std::cout << "Operation2 Performed" << std::endl;
}

void dispatcher_thread() {
    std::shared_ptr<Payload> payload = std::make_shared<Payload>(1); 
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    std::thread wt1(&operation1, payload);
    std::thread wt2(&operation2, payload);
    wt1.detach();
    wt2.detach();
}

int main(int argc, char** argv)
{
    std::cout << "Calling dispatcher thread" << std::endl;
    std::thread t(&dispatcher_thread);
    t.join();

    std::cout << "Press enter to exit" << std::endl;
    getchar();
    return 0;
}