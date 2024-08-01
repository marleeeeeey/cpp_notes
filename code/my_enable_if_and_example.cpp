#include <iostream>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

// SFINAE IF
// - Либо ТИП,
// - Либо НЕВАЛИДНЫЙ ТИП (ОШИБКА)

// clang-format off

// B - condition
// T - type when condition true
// F - type when condition false (REMOVED)
template<bool B, typename T = void>
struct enable_if { using type = T; }; // (1) Primary spec - true by default

template<typename T>
struct enable_if<false, T> { }; // (2) Part spec for false - type always invalid

template<bool B, typename T>
using enable_if_t = typename enable_if<B, T>::type; // (3) Convinient using

template <typename It>
using iterator_category_t = typename std::iterator_traits<It>::iterator_category;

template <
    typename It,
    typename T = // Неиспользуемый нами тип будет либо void, либо невалиден
        std::enable_if_t<std::is_base_of_v<
                            std::random_access_iterator_tag,
                            iterator_category_t<It>>>>
void method_for_random_access_iterators(It first, It last)
{
    std::cout << "print for input iterators: ";
    for(auto&& it = first; it != last; ++it)
    {
        std::cout << *it;
    }
}

// clang-format on

int main()
{
    std::vector<int> vec{10, 20, 30, 40}; // OK
    // std::list<int> vec{10, 20, 30, 40}; // NOK
    method_for_random_access_iterators(begin(vec), end(vec));
}