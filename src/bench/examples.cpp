// Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
// Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#include <bench/bench.h>
#include <validation.h>
#include <utiltime.h>

// Sanity test: this should loop ten times, and
// min/max/average should be close to 100ms.
static void Sleep100ms(benchmark::State& state)
{
    while (state.KeepRunning()) {
        MilliSleep(100);
    }
}

BENCHMARK(Sleep100ms, 10);

// Extremely fast-running benchmark:
#include <math.h>

volatile double sum = 0.0; // volatile, global so not optimized away

static void Trig(benchmark::State& state)
{
    double d = 0.01;
    while (state.KeepRunning()) {
        sum += sin(d);
        d += 0.000001;
    }
}

BENCHMARK(Trig, 12 * 1000 * 1000);
