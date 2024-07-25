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

// FC
// On July, 24 10:42 AM, Egor Bychin <ybychin@fleep.io> wrote:
// > void f(this A); A{}.f(); по сути эквивалентно static void f(A); f(A{});
// эквивалентно, но не совсем )
// https://stackoverflow.com/q/78785176/7325599
// ST
// static void f(A&&); f(A{}); - а не такой эквивалент должен быть? У нас же там rvalue? Deducing THIS умеет выводить
// rvalue ref?
// EB
// чтоб было так, как ты говоришь, сигнатура у метода должна была бы быть такой void f(this A &&);
// SUMMARY:
// Как я понял, operator.() вызывает материализацю обекта, т.е. превращение prvalue -> glvalue.