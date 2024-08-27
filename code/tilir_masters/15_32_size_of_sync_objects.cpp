#include <condition_variable>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

int main()
{
    std::cout << "once_flag: " << sizeof(std::once_flag) << std::endl;
    std::cout << "lock_guard<mutex>: " << sizeof(std::lock_guard<std::mutex>) << std::endl;
    std::cout << "scoped_lock<mutex>: " << sizeof(std::scoped_lock<std::mutex>) << std::endl;
    std::cout << "unique_lock<mutex>: " << sizeof(std::unique_lock<std::mutex>) << std::endl;
    std::cout << "shared_lock<mutex>: " << sizeof(std::shared_lock<std::mutex>) << std::endl;
    std::cout << "condition_variable: " << sizeof(std::condition_variable) << std::endl;
    std::cout << "mutex: " << sizeof(std::mutex) << std::endl;
    std::cout << "recursive_mutex: " << sizeof(std::recursive_mutex) << std::endl;
    std::cout << "timed_mutex: " << sizeof(std::timed_mutex) << std::endl;
    std::cout << "recursive_timed_mutex: " << sizeof(std::recursive_timed_mutex) << std::endl;
    std::cout << "shared_mutex: " << sizeof(std::shared_mutex) << std::endl;
}
