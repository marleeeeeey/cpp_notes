#include <iostream>

// clang-format off

#define INCREMENT_ALL_VARIABLES 1

int g = 1;              // <=== не копируется в лямбду, т.к. глобальная.

void foo(int b)
{
    int x = 2;
    static int a = 3;   // <=== не копируется в лямбду, т.к. статическая.
    if (b == 4)
    {
        int y = 5;
        auto lam = [=]
        {
            return x + y + a + b + g;
        };

#if INCREMENT_ALL_VARIABLES
        // здесь изменения x, y, b уже не изменят результат
        // зато изменения a и g − изменят
        g++;
        b++;
        x++;
        a++;
        y++;
#endif

        std::cout << lam() << std::endl;
    }
}

int main()
{
    foo(4);
}