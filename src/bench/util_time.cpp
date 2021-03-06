// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#include <bench/bench.h>

#include <utiltime.h>

static void BenchTimeDeprecated(benchmark::State& state)
{
    while (state.KeepRunning()) {
        (void)GetTime();
    }
}

static void BenchTimeMock(benchmark::State& state)
{
    SetMockTime(111);
    while (state.KeepRunning()) {
        (void)GetTime<std::chrono::seconds>();
    }
    SetMockTime(0);
}

static void BenchTimeMillis(benchmark::State& state)
{
    while (state.KeepRunning()) {
        (void)GetTime<std::chrono::milliseconds>();
    }
}

static void BenchTimeMillisSys(benchmark::State& state)
{
    while (state.KeepRunning()) {
        (void)GetTimeMillis();
    }
}

BENCHMARK(BenchTimeDeprecated, 100000000);
BENCHMARK(BenchTimeMillis, 6000000);
BENCHMARK(BenchTimeMillisSys, 6000000);
BENCHMARK(BenchTimeMock, 300000000);
