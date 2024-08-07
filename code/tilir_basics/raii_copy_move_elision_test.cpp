#include <iostream>

struct A
{
    A() { std::cout << "Default constructor\n"; }
    ~A() { std::cout << "Destructor\n"; }

    // REMOVE BOTH COPY AND MOVE CONSTRUCTORS
    A(const A&) = delete;
    A(A&&) = delete;
};

A createA()
{
    return A{}; // BUT THIS STILL WORKS FINE BECAUSE OF COPY ELISION
}

int main()
{
    A a = createA();
    return 0;
}
