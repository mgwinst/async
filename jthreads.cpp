#include <iostream>
#include <thread>
#include <syncstream>
#include <vector>
#include <chrono>
#include <random>
#include <mutex>
#include <functional>
#include <string>

#define sync_cout std::osyncstream(std::cout)

using namespace std::chrono_literals;

void func(const std::string& name) {
    sync_cout << "Thread " << name << " starting...\n";
    std::this_thread::sleep_for(1s);
    sync_cout << "Thread " << name << " finishing...\n";
}

class JthreadWrapper {
public:
    JthreadWrapper(const std::function<void(const std::string&)>& func,
        const std::string& str) : t{func, str} , name{str} {
            sync_cout << "Thread " << name << " being created\n";
    }
    
    ~JthreadWrapper() { sync_cout << "Thread " << name << " being destroyed\n"; }
private: 
    std::jthread t;
    std::string name;
};

template <typename F>
class JthreadWrapperT {
public:
    JthreadWrapperT(F&& func, const std::string& str) : t{std::forward<F>(func), str}, name{str} {
        sync_cout << "Thread " << name << " being created\n";
    }

    ~JthreadWrapperT() { sync_cout << "Thread " << name << " being destroyed\n"; }

private:
    std::jthread t;
    std::string name;
};

int main() {
    JthreadWrapperT t1 {func, "t1"};
    JthreadWrapperT t2 {func, "t2"};
    JthreadWrapperT t3 {func, "t3"};
    std::this_thread::sleep_for(2s);
    sync_cout << "MAIN THREAD EXITING..." << std::endl;
}
