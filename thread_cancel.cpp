#include <chrono>
#include <functional>
#include <iostream>
#include <syncstream>
#include <thread>

#define sync_cout std::osyncstream(std::cout)

using namespace std::chrono_literals;

class Counter {
public:
    using Callback = std::function<void(void)>;
    Counter(const Callback& callback) {
        t = std::jthread([&]() {
            while (running.load() == true) {
                callback();
                std::this_thread::sleep_for(1s);
            }
        });
    }
    void stop() { running.store(false); }

private:
    std::jthread t;
    std::atomic_bool running{true};
};

int main() {
    Counter counter([&]() {
        sync_cout << "Callback: Running...\n";
    });
    std::this_thread::sleep_for(3s);
    counter.stop();
}