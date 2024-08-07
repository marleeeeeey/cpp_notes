#include <iostream>
#include <type_traits>

// Написать вычисление целочисленного квадратного корня в compile time.
// 1. Пишем функцию в функциональном стиле для run time:

// int sqrt_int(int N, int lo = 1, int hi = N)
// {
//     int mid = (hi + lo + 1) / 2;
//     if (lo == hi) // Это похоже на специализацию
//     {
//         return lo;
//     }
//     else
//     {
//         if (N < mid * mid) // На SFINAE можно сделать IF через std::conditional
//             return sqrt_int(N, lo, mid - 1);
//         else
//             return sqrt_int(N, mid, hi);
//     }
// }

// 2. Пишем SFINAE

// clang-format off

template<int N, int L=1, int H=N, int MID=(L+H+1)/2>
struct SqrtInt : std::integral_constant<int,
    std::conditional_t< (N < MID * MID),
                        SqrtInt<N, L, MID-1>,
                        SqrtInt<N, MID, H>>{}>{};

template<int N, int S>
struct SqrtInt<N, S, S, S> : std::integral_constant<int, S>{};

// clang-format on

int main()
{
    auto result = SqrtInt<999>();
    std::cout << "SqrtInt<999> = " << result << std::endl;
    std::cout << result << " * " << result << " = " << result * result << std::endl;
}