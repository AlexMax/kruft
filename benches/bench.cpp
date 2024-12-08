//
// Copyright (c) 2024 Lexi Mayfield
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(_WIN32)
#define _CRT_SECURE_NO_WARNINGS // [LM] Say the line!
#endif

#include "krstr.h"

#include <benchmark/benchmark.h>

//------------------------------------------------------------------------------

static void Bench_strcpy(benchmark::State &state)
{
    char buffer[32];
    for (auto _ : state)
    {
        char *r = strcpy(buffer, "hello, world");
        benchmark::DoNotOptimize(r);
    }
}

BENCHMARK(Bench_strcpy);

static void Bench_strncpy(benchmark::State &state)
{
    char buffer[32];
    for (auto _ : state)
    {
        char *r = strncpy(buffer, "hello, world", sizeof(buffer) - 1);
        benchmark::DoNotOptimize(r);
    }
}

BENCHMARK(Bench_strncpy);

static void Bench_kr_strlcpy(benchmark::State &state)
{
    char buffer[32];
    for (auto _ : state)
    {
        size_t r = kr_strlcpy(buffer, "hello, world", sizeof(buffer));
        benchmark::DoNotOptimize(r);
    }
}

BENCHMARK(Bench_kr_strlcpy);

static void Bench_kr_strscpy(benchmark::State &state)
{
    char buffer[32];
    for (auto _ : state)
    {
        ptrdiff_t r = kr_strscpy(buffer, "hello, world", sizeof(buffer));
        benchmark::DoNotOptimize(r);
    }
}

BENCHMARK(Bench_kr_strscpy);

static void Bench_strlen(benchmark::State &state)
{
    const char buffer[] = "The quick brown fox jumps over the lazy dog.";
    for (auto _ : state)
    {
        size_t r = strlen(buffer);
        benchmark::DoNotOptimize(r);
    }
}

BENCHMARK(Bench_strlen);

static void Bench_kr_strlen(benchmark::State &state)
{
    const char buffer[] = "The quick brown fox jumps over the lazy dog.";
    for (auto _ : state)
    {
        size_t r = kr_strlen(buffer);
        benchmark::DoNotOptimize(r);
    }
}

BENCHMARK(Bench_kr_strlen);

static void Bench_strnlen(benchmark::State &state)
{
    const char buffer[] = "The quick brown fox jumps over the lazy dog.";
    for (auto _ : state)
    {
        size_t r = strnlen(buffer, sizeof(buffer));
        benchmark::DoNotOptimize(r);
    }
}

BENCHMARK(Bench_strnlen);

static void Bench_kr_strnlen(benchmark::State &state)
{
    const char buffer[] = "The quick brown fox jumps over the lazy dog.";
    for (auto _ : state)
    {
        size_t r = kr_strnlen(buffer, sizeof(buffer));
        benchmark::DoNotOptimize(r);
    }
}

BENCHMARK(Bench_kr_strnlen);

BENCHMARK_MAIN();
