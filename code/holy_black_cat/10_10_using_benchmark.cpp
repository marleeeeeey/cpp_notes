#include <benchmark/benchmark.h>

// extern std::size_t n; // = 10000
constexpr std::size_t n = 10000;

static void VecOfVec(benchmark::State& state)
{
    const std::size_t n = ::n;

    std::vector<std::vector<int>> vec;
    vec.resize(n);
    for (auto& a : vec)
        a.resize(n);

    std::size_t x = 0, y = 0;

    for (auto _ : state)
    {
        int& target = vec[y][x];
        target = x + y;
        benchmark::DoNotOptimize(target);

        x++;
        if (x == n)
        {
            x = 0;
            y++;
            if (y == n)
                y = 0;
        }
    }
}
BENCHMARK(VecOfVec);

static void FlatArray(benchmark::State& state)
{
    const std::size_t n = ::n;

    std::vector<int> vec(n * n);

    std::size_t x = 0, y = 0;

    for (auto _ : state)
    {
        int& target = vec[y * n + x];
        target = x + y;
        benchmark::DoNotOptimize(target);

        x++;
        if (x == n)
        {
            x = 0;
            y++;
            if (y == n)
                y = 0;
        }
    }
}
// Register the function as a benchmark
BENCHMARK(FlatArray);

static void VecOfVecCont(benchmark::State& state)
{
    const std::size_t n = ::n;

    std::vector<char> vec(n * n * sizeof(int) + n * sizeof(int*));

    int* start = (int*)(vec.data() + sizeof(int*) * n);
    for (std::size_t i = 0; i < n; i++)
        ((int**)vec.data())[i] = start + i;

    std::size_t x = 0, y = 0;

    for (auto _ : state)
    {
        int& target = ((int**)vec.data())[y][x];
        target = x + y;
        benchmark::DoNotOptimize(target);

        x++;
        if (x == n)
        {
            x = 0;
            y++;
            if (y == n)
                y = 0;
        }
    }
}
// Register the function as a benchmark
BENCHMARK(VecOfVecCont);

BENCHMARK_MAIN();