#include <string>
#include <utility>

#define ENABLE_FAILS 0

template <typename T, typename U>
    requires requires(T t, U u) { t == u; }
bool check_eq(T&& lhs, U&& rhs)
{
    return (lhs == rhs);
}

int main()
{
    check_eq(1, 2);
    check_eq(std::string{"1"}, std::string{"2"});
#if ENABLE_FAILS
    check_eq(std::string{"1"}, 1); // error: no matching function for call to 'check_eq'
                                   // because 't == u' would be invalid: invalid operands to binary expression
                                   // ('std::basic_string<char>' and 'int')
#endif
}