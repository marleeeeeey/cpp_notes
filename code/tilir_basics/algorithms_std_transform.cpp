#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

int main()
{
    std::string s = "hello";
#if 0
  std::transform(s.begin(), s.end(), s.begin(), std::toupper); // FAIL
#endif
    std::transform(s.begin(), s.end(), s.begin(), ::toupper); // FAIL-ISH style: C function used
    std::cout << s << std::endl;
    std::transform(s.begin(), s.end(), s.begin(), [](auto&& c) { return std::tolower(c); }); // OK
    std::cout << s << std::endl;
}
