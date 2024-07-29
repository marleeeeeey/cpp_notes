#include <iostream>
#include <string>

// clang-format off

enum class ReturnTypeTag { String, Int, Double };

// Empty primary template to generate an error by default
template <ReturnTypeTag tag> struct TypeTraits {};

// Specialization #1 for ReturnTypeTag::String returns std::string.
template<> struct TypeTraits<ReturnTypeTag::String>
{
    ReturnTypeTag tag = ReturnTypeTag::String;
    using type = std::string;
};

// Specialization #2 for ReturnTypeTag::Int returns int.
template<> struct TypeTraits<ReturnTypeTag::Int>
{
    ReturnTypeTag tag = ReturnTypeTag::Int;
    using type = int;
};

// Return type of method depeds on templates non-type parameter.
template<ReturnTypeTag tag>
typename TypeTraits<tag>::type getType() { return {}; }

// clang-format on

int main()
{
    auto shouldBeStdString = getType<ReturnTypeTag::String>();
    std::cout << typeid(shouldBeStdString).name() << std::endl; // std::string

    auto shouldBeInt = getType<ReturnTypeTag::Int>();
    std::cout << typeid(shouldBeInt).name() << std::endl; // int
}