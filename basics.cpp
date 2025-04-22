#include <iostream>
#include <thread>
#include <syncstream>
#include <vector>
#include <chrono>
#include <random>
#include <mutex>

#define sync_cout std::osyncstream(std::cout)

using namespace std::chrono_literals;


// unamed namespaces better than static globals
namespace {
    int res = 0;
    std::mutex mtx;
}

void func_with_mutex() {
    std::this_thread::sleep_for(1s);
    int local_var = 1 + (rand() % 10);
    std::lock_guard<std::mutex> lock(mtx);
    res = local_var;
}

// there are more elegant ways of threads returning values
int main() {
    std::thread t1 {func_with_mutex};
    t1.join();
    sync_cout << res << std::endl;
}
