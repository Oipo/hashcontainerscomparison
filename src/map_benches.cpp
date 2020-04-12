#include <iostream>
#include <wyhash.h>
#include <tsl/robin_map.h>
#include <folly/hash/FarmHash.h>
#include <folly/container/F14Map.h>
#include <absl/hash/hash.h>
#include <absl/container/flat_hash_map.h>
#include <benchmark/benchmark.h>
#include <sstream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <xxh3.h>
#include <robin_hood.h>
#include "macros.h"

using namespace std;

std::vector<std::string> string_numbers;

template<class Key>
class wyhash_function
{
public:
    size_t operator()(Key const &t) const
    {
        return wyhash(&t, sizeof(t), 1);
    }
};
template<>
class wyhash_function<std::string>
{
public:
    size_t operator()(std::string const &t) const
    {
        return wyhash(t.data(), t.size(), 1);
    }
};

template<class Key>
class farmhash_function
{
public:
    size_t operator()(Key const &t) const
    {
        return folly::external::farmhash::Hash64WithSeed(reinterpret_cast<char const *>(&t), sizeof(t), 1);
    }
};
template<>
class farmhash_function<std::string>
{
public:
    size_t operator()(std::string const &t) const
    {
        return folly::external::farmhash::Hash64WithSeed(t.data(), t.size(), 1);
    }
};

template<class Key>
class abslhash_function
{
public:
    size_t operator()(Key const &t) const
    {
        return absl::hash_internal::CityHash64WithSeed(reinterpret_cast<char const *>(&t), sizeof(t), 1);
    }
};
template<>
class abslhash_function<std::string>
{
public:
    size_t operator()(std::string const &t) const
    {
        return absl::hash_internal::CityHash64WithSeed(t.data(), t.size(), 1);
    }
};

template<class Key>
class xxhash_function
{
public:
    size_t operator()(Key const &t) const
    {
        return XXH3_64bits(&t, sizeof(t));
    }
};
template<>
class xxhash_function<std::string>
{
public:
    size_t operator()(std::string const &t) const
    {
        return XXH3_64bits(t.data(), t.size());
    }
};

// hash has optimalization for uint64_t
static void unordered_nohash(benchmark::State& state) {
    for (auto _ : state) {
        unordered_map<uint64_t, uint64_t, hash<uint64_t>> m{};
        m.reserve(1'000'000);
        for(uint64_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(unordered_nohash);

static void robinmap_nohash(benchmark::State& state) {
    for (auto _ : state) {
        tsl::robin_map<uint64_t, uint64_t, hash<uint64_t>> m{};
        m.reserve(1'000'000);
        for(uint64_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(robinmap_nohash);

static void f14map_nohash(benchmark::State& state) {
    for (auto _ : state) {
        folly::F14FastMap<uint64_t, uint64_t, hash<uint64_t>> m{};
        m.reserve(1'000'000);
        for(uint64_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(f14map_nohash);

static void abslmap_nohash(benchmark::State& state) {
    for (auto _ : state) {
        absl::flat_hash_map<uint64_t, uint64_t, hash<uint64_t>> m{};
        m.reserve(1'000'000);
        for(uint64_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(abslmap_nohash);

static void robinmap2_nohash(benchmark::State& state) {
    for (auto _ : state) {
        robin_hood::unordered_flat_map<uint64_t, uint64_t, hash<uint64_t>> m{};
        m.reserve(1'000'000);
        for(uint64_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(robinmap2_nohash);


HASH_PUSH_BENCH(unordered_put_wyhash, unordered_map, wyhash_function, 0)
HASH_PUSH_BENCH(unordered_put_farmhash, unordered_map, farmhash_function, 0)
HASH_PUSH_BENCH(unordered_put_abslhash, unordered_map, abslhash_function, 0)
HASH_PUSH_BENCH(unordered_put_xxhash, unordered_map, xxhash_function, 0)
HASH_PUSH_BENCH(unordered_put_stdhash, unordered_map, hash, 0)
HASH_PUSH_BENCH(robinmap_put_wyhash, tsl::robin_map, wyhash_function, 0)
HASH_PUSH_BENCH(robinmap_put_farmhash, tsl::robin_map, farmhash_function, 0)
HASH_PUSH_BENCH(robinmap_put_abslhash, tsl::robin_map, abslhash_function, 0)
HASH_PUSH_BENCH(robinmap_put_xxhash, tsl::robin_map, xxhash_function, 0)
HASH_PUSH_BENCH(robinmap_put_stdhash, tsl::robin_map, hash, 0)
HASH_PUSH_BENCH(f14map_put_wyhash, folly::F14FastMap, wyhash_function, 0)
HASH_PUSH_BENCH(f14map_put_farmhash, folly::F14FastMap, farmhash_function, 0)
HASH_PUSH_BENCH(f14map_put_abslhash, folly::F14FastMap, abslhash_function, 0)
HASH_PUSH_BENCH(f14map_put_xxhash, folly::F14FastMap, xxhash_function, 0)
HASH_PUSH_BENCH(f14map_put_stdhash, folly::F14FastMap, hash, 0)
HASH_PUSH_BENCH(abslmap_put_wyhash, absl::flat_hash_map, wyhash_function, 0)
HASH_PUSH_BENCH(abslmap_put_farmhash, absl::flat_hash_map, farmhash_function, 0)
HASH_PUSH_BENCH(abslmap_put_abslhash, absl::flat_hash_map, abslhash_function, 0)
HASH_PUSH_BENCH(abslmap_put_xxhash, absl::flat_hash_map, xxhash_function, 0)
HASH_PUSH_BENCH(abslmap_put_stdhash, absl::flat_hash_map, hash, 0)
HASH_PUSH_BENCH(robinmap2_put_wyhash, robin_hood::unordered_flat_map, wyhash_function, 0)
HASH_PUSH_BENCH(robinmap2_put_farmhash, robin_hood::unordered_flat_map, farmhash_function, 0)
HASH_PUSH_BENCH(robinmap2_put_abslhash, robin_hood::unordered_flat_map, abslhash_function, 0)
HASH_PUSH_BENCH(robinmap2_put_xxhash, robin_hood::unordered_flat_map, xxhash_function, 0)
HASH_PUSH_BENCH(robinmap2_put_stdhash, robin_hood::unordered_flat_map, hash, 0)
HASH_PUSH_BENCH(unordered_put_wyhash_reserve, unordered_map, wyhash_function, 1'000'000)
HASH_PUSH_BENCH(unordered_put_farmhash_reserve, unordered_map, farmhash_function, 1'000'000)
HASH_PUSH_BENCH(unordered_put_abslhash_reserve, unordered_map, abslhash_function, 1'000'000)
HASH_PUSH_BENCH(unordered_put_xxhash_reserve, unordered_map, xxhash_function, 1'000'000)
HASH_PUSH_BENCH(unordered_put_stdhash_reserve, unordered_map, hash, 1'000'000)
HASH_PUSH_BENCH(robinmap_put_wyhash_reserve, tsl::robin_map, wyhash_function, 1'000'000)
HASH_PUSH_BENCH(robinmap_put_farmhash_reserve, tsl::robin_map, farmhash_function, 1'000'000)
HASH_PUSH_BENCH(robinmap_put_abslhash_reserve, tsl::robin_map, abslhash_function, 1'000'000)
HASH_PUSH_BENCH(robinmap_put_xxhash_reserve, tsl::robin_map, xxhash_function, 1'000'000)
HASH_PUSH_BENCH(robinmap_put_stdhash_reserve, tsl::robin_map, hash, 1'000'000)
HASH_PUSH_BENCH(f14map_put_wyhash_reserve, folly::F14FastMap, wyhash_function, 1'000'000)
HASH_PUSH_BENCH(f14map_put_farmhash_reserve, folly::F14FastMap, farmhash_function, 1'000'000)
HASH_PUSH_BENCH(f14map_put_abslhash_reserve, folly::F14FastMap, abslhash_function, 1'000'000)
HASH_PUSH_BENCH(f14map_put_xxhash_reserve, folly::F14FastMap, xxhash_function, 1'000'000)
HASH_PUSH_BENCH(f14map_put_stdhash_reserve, folly::F14FastMap, hash, 1'000'000)
HASH_PUSH_BENCH(abslmap_put_wyhash_reserve, absl::flat_hash_map, wyhash_function, 1'000'000)
HASH_PUSH_BENCH(abslmap_put_farmhash_reserve, absl::flat_hash_map, farmhash_function, 1'000'000)
HASH_PUSH_BENCH(abslmap_put_abslhash_reserve, absl::flat_hash_map, abslhash_function, 1'000'000)
HASH_PUSH_BENCH(abslmap_put_xxhash_reserve, absl::flat_hash_map, xxhash_function, 1'000'000)
HASH_PUSH_BENCH(abslmap_put_stdhash_reserve, absl::flat_hash_map, hash, 1'000'000)
HASH_PUSH_BENCH(robinmap2_put_wyhash_reserve, robin_hood::unordered_flat_map, wyhash_function, 1'000'000)
HASH_PUSH_BENCH(robinmap2_put_farmhash_reserve, robin_hood::unordered_flat_map, farmhash_function, 1'000'000)
HASH_PUSH_BENCH(robinmap2_put_abslhash_reserve, robin_hood::unordered_flat_map, abslhash_function, 1'000'000)
HASH_PUSH_BENCH(robinmap2_put_xxhash_reserve, robin_hood::unordered_flat_map, xxhash_function, 1'000'000)
HASH_PUSH_BENCH(robinmap2_put_stdhash_reserve, robin_hood::unordered_flat_map, hash, 1'000'000)
HASH_GET_BENCH(unordered_get_wyhash, unordered_map, wyhash_function)
HASH_GET_BENCH(unordered_get_farmhash, unordered_map, farmhash_function)
HASH_GET_BENCH(unordered_get_abslhash, unordered_map, abslhash_function)
HASH_GET_BENCH(unordered_get_xxhash, unordered_map, xxhash_function)
HASH_GET_BENCH(unordered_get_stdhash, unordered_map, hash)
HASH_GET_BENCH(robinmap_get_wyhash, tsl::robin_map, wyhash_function)
HASH_GET_BENCH(robinmap_get_farmhash, tsl::robin_map, farmhash_function)
HASH_GET_BENCH(robinmap_get_abslhash, tsl::robin_map, abslhash_function)
HASH_GET_BENCH(robinmap_get_xxhash, tsl::robin_map, xxhash_function)
HASH_GET_BENCH(robinmap_get_stdhash, tsl::robin_map, hash)
HASH_GET_BENCH(f14map_get_wyhash, folly::F14FastMap, wyhash_function)
HASH_GET_BENCH(f14map_get_farmhash, folly::F14FastMap, farmhash_function)
HASH_GET_BENCH(f14map_get_abslhash, folly::F14FastMap, abslhash_function)
HASH_GET_BENCH(f14map_get_xxhash, folly::F14FastMap, xxhash_function)
HASH_GET_BENCH(f14map_get_stdhash, folly::F14FastMap, hash)
HASH_GET_BENCH(abslmap_get_wyhash, absl::flat_hash_map, wyhash_function)
HASH_GET_BENCH(abslmap_get_farmhash, absl::flat_hash_map, farmhash_function)
HASH_GET_BENCH(abslmap_get_abslhash, absl::flat_hash_map, abslhash_function)
HASH_GET_BENCH(abslmap_get_xxhash, absl::flat_hash_map, xxhash_function)
HASH_GET_BENCH(abslmap_get_stdhash, absl::flat_hash_map, hash)
HASH_GET_BENCH(robinmap2_get_wyhash, robin_hood::unordered_flat_map, wyhash_function)
HASH_GET_BENCH(robinmap2_get_farmhash, robin_hood::unordered_flat_map, farmhash_function)
HASH_GET_BENCH(robinmap2_get_abslhash, robin_hood::unordered_flat_map, abslhash_function)
HASH_GET_BENCH(robinmap2_get_xxhash, robin_hood::unordered_flat_map, xxhash_function)
HASH_GET_BENCH(robinmap2_get_stdhash, robin_hood::unordered_flat_map, hash)

static void spdlog_bench_json(benchmark::State& state) {
    auto time_since_epoch = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
    auto file_sink = make_shared<spdlog::sinks::basic_file_sink_mt>(fmt::format("logs/log-{}.txt", time_since_epoch.count()), true);

    auto logger = make_shared<spdlog::logger>("multi_sink"s, spdlog::sinks_init_list{file_sink});
    spdlog::set_default_logger(logger);
    spdlog::set_pattern("[%C-%m-%d %H:%M:%S.%e] [%L] %v");

    for (auto _ : state) {
        spdlog::info( R"({ "test": {"key": 1}})");
    }

    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(spdlog_bench_json)->Iterations(1'000'000);