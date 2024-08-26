#include <iostream>
#include <thread>

#define USE_ATOMIC 0

#if USE_ATOMIC
std::atomic<int> x = 0;
#else
int x = 0;
#endif

void __attribute__((noinline)) use(int c)
{
    asm(""); // Отключаем оптимизации
}

void race()
{
    // going up
    for (int i = 0; i < 1000000; ++i)
    {
        x += 1;
        use(x);
    }

    // going down
    for (int i = 0; i < 1000000; ++i)
    {
        x -= 1;
        use(x);
    }
}

int main()
{
    std::thread t1{race};
    std::thread t2{race};
    t1.join();
    t2.join();
    std::cout << x << std::endl;
}
