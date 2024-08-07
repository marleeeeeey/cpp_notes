#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>

#define NAIVE_ORIGINAL_FINALLY_CLASS 0

#if NAIVE_ORIGINAL_FINALLY_CLASS
// Lightning Talk: FINALLY - The Presentation You've All Been Waiting For - Louis Thomas - CppCon 2021
// https://www.youtube.com/watch?v=eG5suWcHI8M
// Here is an overhead - we have to use heap to save lambda `[]` values.
struct Finally
{
    std::function<void()> action_;
    explicit Finally(std::function<void()> action) : action_(std::move(action)) {}
    ~Finally() { action_(); }
};
#else
// Improved version of Finally class. Head is not used here. No type erasure because use lambda object as is without
// std::function.
template <typename T>
struct Finally
{
    T action_;
    explicit Finally(T action) : action_(std::move(action)) {}
    ~Finally() { action_(); }
};
#endif

int main()
{
    try
    {
        std::string fileHandle = "0x12345678";
        std::cout << "Open file with handle " << fileHandle << std::endl;
        Finally close_f([&fileHandle] { std::cout << "Closed file " << fileHandle << " anyway\n"; });

        std::cout << "Throw exception\n";
        throw std::logic_error("Throw exception, but file may be still opened");
        std::cout << "Never reach this line\n";
    }
    catch (std::exception& e)
    {
        std::cout << "Catch: " << e.what() << std::endl;
    }
}