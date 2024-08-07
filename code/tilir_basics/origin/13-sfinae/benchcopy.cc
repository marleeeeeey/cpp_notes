//-----------------------------------------------------------------------------
//
// Source code for MIPT ILab
// Slides: https://sourceforge.net/projects/cpp-lects-rus/files/cpp-graduate/
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Benchmark for naive copy vs memcpy
//
// Homebrew std::copy
// > g++ -O2 benchcopy.cc -o bench
// > cl /std:c++20 /O2 /EHsc benchcopy.cc
// > bench 300000000
//
// Real std::copy
// > g++ -O2 -DSTANDARD benchcopy.cc -o bench
// > cl /std:c++20 /O2 /DSTANDARD /EHsc benchcopy.cc
// > bench 300000000
//
//-----------------------------------------------------------------------------

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

#define NAIVE 1

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

const int IMAX = 9;

template <typename InputIt, typename OutputIt>
OutputIt naive_copy(InputIt first, InputIt last, OutputIt d_first)
{
    while (first != last)
        *d_first++ = *first++;
    return d_first;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " nelts" << std::endl;
        return -1;
    }

    auto nelts = std::stoi(argv[1]);
    std::vector<int> arr(nelts);
    std::vector<int> arrcopy(nelts);
    std::vector<int> arrcopy2(nelts);

    std::random_device rd;
    std::default_random_engine reng(rd());
    std::uniform_int_distribution<int> dist(0, IMAX);

    std::generate(arr.begin(), arr.end(), [&dist, &reng] { return dist(reng); });

    auto tstart = high_resolution_clock::now();
    std::memcpy(arrcopy.data(), arr.data(), nelts * sizeof(int));
    auto tfin = high_resolution_clock::now();

    std::cout << "memcpy: " << duration_cast<milliseconds>(tfin - tstart).count() << std::endl;

    tstart = high_resolution_clock::now();
#if NAIVE
    naive_copy(arr.begin(), arr.end(), arrcopy2.begin());
#else
    std::copy(arr.begin(), arr.end(), arrcopy2.begin());
#endif
    tfin = high_resolution_clock::now();

#if NAIVE
    std::cout << "naive copy: "
#else
    std::cout << "std copy: "
#endif
              << duration_cast<milliseconds>(tfin - tstart).count() << std::endl;

    // sanity: do we have mismatch (we shall not)
    auto mism = std::mismatch(arrcopy.begin(), arrcopy.end(), arrcopy2.begin());
    if (mism.first != arrcopy.end() || mism.second != arrcopy2.end())
    {
        std::cout << "mismatch: " << *mism.first << " vs " << *mism.second << std::endl;
        std::cout << "at: " << std::distance(arrcopy.begin(), mism.first) << std::endl;
    }
}
