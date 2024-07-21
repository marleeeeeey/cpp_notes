struct A
{
    A()
    try : a(1) // !!! See this line
    {}
    catch (...)
    {}

    int a;
};

int main()
{}