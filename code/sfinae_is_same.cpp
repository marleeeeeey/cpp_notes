// https://godbolt.org/z/6GdndGKzM
#include <cassert>

// clang-format off

template <typename T, T v> struct integral_constant
{
    static const T value = v;
    using value_type = T;
    using type = integral_constant;
    operator value_type() const noexcept { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <typename T, typename U>
struct is_same : false_type {};

template<typename T>
struct is_same<T, T> : true_type {};    // for T == T

template<typename T, typename U>
using is_same_t = typename is_same<T, U>::type;

// *** is_reference (определитель) ***

template<typename T> struct is_reference : false_type {};
template<typename T> struct is_reference<T&> : true_type {};
template<typename T> struct is_reference<T&&> : true_type {};

// *** remove_reference (модификатор) ***

template <typename T> struct remove_reference { using type = T; };
template <typename T> struct remove_reference<T&> { using type = T; };
template <typename T> struct remove_reference<T&&> { using type = T; };

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

// clang-format on

int main()
{
    assert(!(is_same<char, double>::value));
    assert((is_same<char, char>::value));

    assert(is_reference<int&>::value == true);
    assert(is_reference<int&&>::value == true);
    assert(is_reference<int>::value == false);

    remove_reference_t<int&> r = 5;
    (void)r;
}