// Should it compile?

struct A
{
    A() {}
    A(A&&) = delete;
    void f(this A) {}
};

int main()
{
    A{}.f();
}

// выводить void f(this A); A{}.f(); по сути эквивалентно static void f(A); f(A{}); эквивалентно, но не совсем:
// https://stackoverflow.com/q/78785176/7325599
