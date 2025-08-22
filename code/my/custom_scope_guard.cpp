#include <iostream>

int main()
{
    std::cout << "1 ";

    {
        auto scopeGuard = std::shared_ptr<void>(
                                                nullptr, []( void* )
                                                {
                                                    std::cout << "3 ";
                                                } );

        std::cout << "2 ";
    }

    std::cout << "4 ";
}
