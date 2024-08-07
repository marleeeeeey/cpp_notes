#include <array>
#include <initializer_list>

#define USE_MAKE_ARRAY 1

// clang-format off

template <typename T, size_t N, size_t... Ns>
constexpr std::array<T, N>
make_array_impl(std::initializer_list<T> t,
                std::index_sequence<Ns...>) {
    return std::array<T, N>{*(t.begin() + Ns)...};
}

template <typename T, size_t N>
constexpr std::array<T, N>
make_array(std::initializer_list<T> t) {
    return make_array_impl<T, N>(t,
                                 std::make_index_sequence<N>());
}


struct S
{
    std::array<int, 5> arr;
    S(std::initializer_list<int> il)
#if USE_MAKE_ARRAY
      : arr(make_array<int, 5>(il)){}   // OK
#else
      : arr(il){}                       // FAILS
#endif
};

// clang-format off

int main()
{
    S s = {1, 2, 3, 4, 5};
}