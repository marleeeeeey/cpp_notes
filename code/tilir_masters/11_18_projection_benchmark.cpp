#include <algorithm>
#include <array>
#include <benchmark/benchmark.h>
#include <random>
#include <ranges>
#include <vector>

namespace ranges = std::ranges;
namespace views = std::views;

struct S
{
    union
    {
        struct
        {
            int a1, a2, a3, a4, a5, a6, a7, a8, a9, a10;
            int b1, b2, b3, b4, b5, b6, b7, b8, b9, b10;
            int c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;
        };
        std::array<int, 30> arr;
    };
};

constexpr int N = 100;

std::random_device rnd_device;
std::mt19937 mersenne_engine{rnd_device()};
std::uniform_int_distribution<int> dist{0, 100};
auto gen = []() -> S
{
    S s;
    for (size_t i = 0; i < s.arr.size(); ++i)
        s.arr[i] = dist(mersenne_engine);
    return s;
};

static void TransformComparator(benchmark::State& state)
{
    std::vector<S> v(N);
    std::vector<int> w(N);
    std::generate(std::begin(v), std::end(v), gen);
    for (auto _ : state)
    {
        ranges::transform(v.begin(), v.end(), w.begin(), [](const auto& a) { return a.c4 * 2; });
    }
}
BENCHMARK(TransformComparator);

static void TransformProjector(benchmark::State& state)
{
    std::vector<S> v(N);
    std::vector<int> w(N);
    std::generate(std::begin(v), std::end(v), gen);
    for (auto _ : state)
    {
        ranges::transform(v.begin(), v.end(), w.begin(), [](auto x) { return x * 2; }, &S::c4);
    }
}
BENCHMARK(TransformProjector);

BENCHMARK_MAIN();