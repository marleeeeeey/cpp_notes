#include <array>
#include <benchmark/benchmark.h>
#include <list>
#include <memory_resource>


std::string_view s = "abcdefghjik";

static void Std(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::set<int> uniqs;
        uniqs.insert(s.begin(), s.end());
        benchmark::DoNotOptimize(uniqs);
    }
}
// Register the function as a benchmark
BENCHMARK(Std);

static void Pmr(benchmark::State& state)
{
    std::array<std::byte, 1024> buffer;
    for (auto _ : state)
    {
        std::pmr::monotonic_buffer_resource mem_resource(buffer.data(), buffer.size());
        std::pmr::set<int> uniqs(&mem_resource);
        uniqs.insert(s.begin(), s.end());
        benchmark::DoNotOptimize(uniqs);
    }
}
// Register the function as a benchmark
BENCHMARK(Pmr);

BENCHMARK_MAIN();