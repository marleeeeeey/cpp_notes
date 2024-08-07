#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::ostream_iterator<int> os(std::cout, " ");
    std::vector<int> a = {1, 2, 4, 9};
    std::vector<int> b = {1, 2, 4, 8};

    // BAD
    auto [ita, itb] = std::mismatch(a.begin(), a.end(), b.begin());
    if (ita != a.end() && itb != b.end())
        std::cout << "Not equal\n";

    // GOOD
    if (!std::equal(a.begin(), a.end(), b.begin()))
        std::cout << "Not equal\n";
}
