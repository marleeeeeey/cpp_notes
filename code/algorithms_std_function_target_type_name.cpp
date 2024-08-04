#include <functional>
#include <iostream>

// clang-format off

int f(int a) { return a; }

int main()
{
  int x = 5;

  std::function<int(int)> fn1 = f,                          // int (__cdecl*)(int)
                          fn2 = [](int a) { return -a; },   // class `main'::`1'::<lambda_0>
                          fn3 = [x](int a) {return x - a;}; // class `main'::`1'::<lambda_1>

  std::cout << fn1.target_type().name() << std::endl
            << fn2.target_type().name() << std::endl
            << fn3.target_type().name() << std::endl;
}

// clang-format on