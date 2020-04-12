#include <iostream>
#include <wyhash.h>
#include <folly/hash/FarmHash.h>
#include <absl/hash/hash.h>
#include <benchmark/benchmark.h>
#include <sstream>
#include <xxh3.h>
#include "macros.h"

using namespace std;

static void wyhash_small(benchmark::State& state) {
    string hash = "hash";
    uint64_t res = 0;
    for (auto _ : state) {
        res += wyhash(hash.c_str(), hash.size(), 1);
    }

    PREVENT_OPT(res);
}
BENCHMARK(wyhash_small);

static void wyhash_large(benchmark::State& state) {
    stringstream hashbuilder{};
    for(uint64_t i = 0; i < 1'000'000; i++) {
        hashbuilder << "hash";
    }
    string hash = hashbuilder.str();
    uint64_t res = 0;
    for (auto _ : state) {
        res += wyhash(hash.c_str(), hash.size(), 1);
    }

    PREVENT_OPT(res);
}
BENCHMARK(wyhash_large);

static void farmhash_small(benchmark::State& state) {
    string hash = "hash";
    uint64_t res = 0;
    for (auto _ : state) {
        res += folly::external::farmhash::Hash64WithSeed(hash.c_str(), hash.size(), 1);
    }

    PREVENT_OPT(res);
}
BENCHMARK(farmhash_small);

static void farmhash_large(benchmark::State& state) {
    stringstream hashbuilder{};
    for(uint64_t i = 0; i < 1'000'000; i++) {
        hashbuilder << "hash";
    }
    string hash = hashbuilder.str();
    uint64_t res = 0;
    for (auto _ : state) {
        res += folly::external::farmhash::Hash64WithSeed(hash.c_str(), hash.size(), 1);
    }

    PREVENT_OPT(res);
}
BENCHMARK(farmhash_large);

static void abslhash_small(benchmark::State& state) {
    string hash = "hash";
    uint64_t res = 0;
    for (auto _ : state) {
        res += absl::hash_internal::CityHash64WithSeed(hash.c_str(), hash.size(), 1);
    }

    PREVENT_OPT(res);
}
BENCHMARK(abslhash_small);

static void abslhash_large(benchmark::State& state) {
    stringstream hashbuilder{};
    for(uint64_t i = 0; i < 1'000'000; i++) {
        hashbuilder << "hash";
    }
    string hash = hashbuilder.str();
    uint64_t res = 0;
    for (auto _ : state) {
        res += absl::hash_internal::CityHash64WithSeed(hash.c_str(), hash.size(), 1);
    }

    PREVENT_OPT(res);
}
BENCHMARK(abslhash_large);

static void xxhash_small(benchmark::State& state) {
    string hash = "hash";
    uint64_t res = 0;
    for (auto _ : state) {
        res += XXH3_64bits(hash.c_str(), hash.size());
    }

    PREVENT_OPT(res);
}
BENCHMARK(xxhash_small);

static void xxhash_large(benchmark::State& state) {
    stringstream hashbuilder{};
    for(uint64_t i = 0; i < 1'000'000; i++) {
        hashbuilder << "hash";
    }
    string hash = hashbuilder.str();
    uint64_t res = 0;
    for (auto _ : state) {
        res += XXH3_64bits(hash.c_str(), hash.size());
    }

    PREVENT_OPT(res);
}
BENCHMARK(xxhash_large);

static void stdhash_small(benchmark::State& state) {
    string hashstr = "hash";
    uint64_t res = 0;
    for (auto _ : state) {
        res += hash<string>{}(hashstr);
    }

    PREVENT_OPT(res);
}
BENCHMARK(stdhash_small);

static void stdhash_large(benchmark::State& state) {
    stringstream hashbuilder{};
    for(uint64_t i = 0; i < 1'000'000; i++) {
        hashbuilder << "hash";
    }
    string hashstr = hashbuilder.str();
    uint64_t res = 0;
    for (auto _ : state) {
        res += hash<string>{}(hashstr);
    }

    PREVENT_OPT(res);
}
BENCHMARK(stdhash_large);