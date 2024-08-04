#include <iostream>

// clang-format off

int main(int argc, const char** argv)
{
    return
    [argv]  // Список захвата
    ()      // Список аргументов
    -> int  // Выводимый тип
    {       // Тело лямбда-выражения
        std::cout << "Hello from " << argv[0] << std::endl;
        return 0;
    }
    ();     // Вызов лямбда-выражения
}

// clang-format on