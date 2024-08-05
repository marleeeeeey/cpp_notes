#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>

int main()
{
    std::ostream_iterator<int> icout{std::cout, " "};
    std::forward_list<int> first = {1, 2, 3};
    std::forward_list<int> second = {10, 20, 30};
    auto it = first.begin();

    // splice second to first: note special before_begin insert position
    first.splice_after(first.before_begin(), second);
    std::cout << "1." << std::endl;
    std::copy(first.begin(), first.end(), icout);
    std::cout << std::endl;

    second.splice_after(second.before_begin(), first, first.begin(), it);
    std::cout << "2." << std::endl;
    std::copy(first.begin(), first.end(), icout);
    std::cout << std::endl;
    std::copy(second.begin(), second.end(), icout);
    std::cout << std::endl;

    first.splice_after(first.before_begin(), second, second.begin());
    std::cout << "3." << std::endl;
    std::copy(first.begin(), first.end(), icout);
    std::cout << std::endl;
    std::copy(second.begin(), second.end(), icout);
    std::cout << std::endl;

    std::cout << "\n-------------------------------------\n" << std::endl;

    std::forward_list<int> a = {100, 200, 300, 400};
    std::forward_list<int> b = {1000, 2000, 3000, 4000};

    // a.splice_after(a.before_begin(), b); // move b to a
    // a.splice_after(a.before_begin(), b, b.begin()); // move second element of b to a before begin
    a.splice_after(a.begin(), b, b.begin()); // move second element of b to a second
    std::copy(a.begin(), a.end(), icout);
    std::cout << std::endl;
    std::copy(b.begin(), b.end(), icout);
    std::cout << std::endl;
}
