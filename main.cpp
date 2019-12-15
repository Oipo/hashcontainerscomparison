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

using namespace std;

template<class Key>
class wyhash_function
{
public:
    size_t operator()(Key t) const
    {
        return wyhash(&t, sizeof(t), 1);
    }
};

template<class Key>
class farmhash_function
{
public:
    size_t operator()(Key t) const
    {
        return folly::external::farmhash::Hash64WithSeed(reinterpret_cast<char*>(&t), sizeof(t), 1);
    }
};

template<class Key>
class abslhash_function
{
public:
    size_t operator()(Key t) const
    {
        return absl::hash_internal::CityHash64WithSeed(reinterpret_cast<char*>(&t), sizeof(t), 1);
    }
};

template<class Key>
class xxhash_function
{
public:
    size_t operator()(Key t) const
    {
        return XXH3_64bits(&t, sizeof(t));
    }
};

#define PREVENT_OPT(VAR) \
    volatile auto copy1 = *((char*)&VAR); \
    volatile auto copy2 = *((char*)&VAR); \
    if (copy1 != copy2) { \
        cout << "cannot happen\n"; \
        throw runtime_error("Cannot happen, but compiler cannot know this"); \
    }

#define ENABLE_HASH_BENCHES

#ifdef ENABLE_HASH_BENCHES
static void wyhash(benchmark::State& state) {
    string hash = "hash";
    uint64_t res = 0;
    for (auto _ : state) {
        res += wyhash(hash.c_str(), hash.size(), 1);
    }

    PREVENT_OPT(res);
}
BENCHMARK(wyhash);

static void wyhash_large(benchmark::State& state) {
    stringstream hashbuilder{};
    for(uint32_t i = 0; i < 1'000'000; i++) {
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

static void farmhash(benchmark::State& state) {
    string hash = "hash";
    uint64_t res = 0;
    for (auto _ : state) {
        res += folly::external::farmhash::Hash64WithSeed(hash.c_str(), hash.size(), 1);
    }

    PREVENT_OPT(res);
}
BENCHMARK(farmhash);

static void farmhash_large(benchmark::State& state) {
    stringstream hashbuilder{};
    for(uint32_t i = 0; i < 1'000'000; i++) {
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

static void abslhash(benchmark::State& state) {
    string hash = "hash";
    uint64_t res = 0;
    for (auto _ : state) {
        res += absl::hash_internal::CityHash64WithSeed(hash.c_str(), hash.size(), 1);
    }

    PREVENT_OPT(res);
}
BENCHMARK(abslhash);

static void abslhash_large(benchmark::State& state) {
    stringstream hashbuilder{};
    for(uint32_t i = 0; i < 1'000'000; i++) {
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

static void xxhash(benchmark::State& state) {
    string hash = "hash";
    uint64_t res = 0;
    for (auto _ : state) {
        res += XXH3_64bits(hash.c_str(), hash.size());
    }

    PREVENT_OPT(res);
}
BENCHMARK(xxhash);

static void xxhash_large(benchmark::State& state) {
    stringstream hashbuilder{};
    for(uint32_t i = 0; i < 1'000'000; i++) {
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

static void unordered_wyhash(benchmark::State& state) {
    for (auto _ : state) {
        unordered_map<uint32_t, uint32_t, wyhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(unordered_wyhash);

static void unordered_farmhash(benchmark::State& state) {
    for (auto _ : state) {
        unordered_map<uint32_t, uint32_t, farmhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(unordered_farmhash);

static void unordered_abslhash(benchmark::State& state) {
    for (auto _ : state) {
        unordered_map<uint32_t, uint32_t, abslhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(unordered_abslhash);

static void unordered_xxhash(benchmark::State& state) {
    for (auto _ : state) {
        unordered_map<uint32_t, uint32_t, xxhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(unordered_xxhash);

static void robinmap_wyhash(benchmark::State& state) {
    for (auto _ : state) {
        tsl::robin_map<uint32_t, uint32_t, wyhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(robinmap_wyhash);

static void robinmap_farmhash(benchmark::State& state) {
    for (auto _ : state) {
        tsl::robin_map<uint32_t, uint32_t, farmhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(robinmap_farmhash);

static void robinmap_abslhash(benchmark::State& state) {
    for (auto _ : state) {
        tsl::robin_map<uint32_t, uint32_t, abslhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(robinmap_abslhash);

static void robinmap_xxhash(benchmark::State& state) {
    for (auto _ : state) {
        tsl::robin_map<uint32_t, uint32_t, xxhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(robinmap_xxhash);

static void f14map_wyhash(benchmark::State& state) {
    for (auto _ : state) {
        folly::F14FastMap<uint32_t, uint32_t, wyhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(f14map_wyhash);

static void f14map_farmhash(benchmark::State& state) {
    for (auto _ : state) {
        folly::F14FastMap<uint32_t, uint32_t, farmhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(f14map_farmhash);

static void f14map_abslhash(benchmark::State& state) {
    for (auto _ : state) {
        folly::F14FastMap<uint32_t, uint32_t, abslhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(f14map_abslhash);

static void f14map_xxhash(benchmark::State& state) {
    for (auto _ : state) {
        folly::F14FastMap<uint32_t, uint32_t, xxhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(f14map_xxhash);

static void abslmap_wyhash(benchmark::State& state) {
    for (auto _ : state) {
        absl::flat_hash_map<uint32_t, uint32_t, wyhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(abslmap_wyhash);

static void abslmap_farmhash(benchmark::State& state) {
    for (auto _ : state) {
        absl::flat_hash_map<uint32_t, uint32_t, farmhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(abslmap_farmhash);

static void abslmap_abslhash(benchmark::State& state) {
    for (auto _ : state) {
        absl::flat_hash_map<uint32_t, uint32_t, abslhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(abslmap_abslhash);

static void abslmap_xxhash(benchmark::State& state) {
    for (auto _ : state) {
        absl::flat_hash_map<uint32_t, uint32_t, xxhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(abslmap_xxhash);

static void robinmap2_wyhash(benchmark::State& state) {
    for (auto _ : state) {
        robin_hood::unordered_flat_map<uint32_t, uint32_t, wyhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(robinmap2_wyhash);

static void robinmap2_farmhash(benchmark::State& state) {
    for (auto _ : state) {
        robin_hood::unordered_flat_map<uint32_t, uint32_t, farmhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(robinmap2_farmhash);

static void robinmap2_abslhash(benchmark::State& state) {
    for (auto _ : state) {
        robin_hood::unordered_flat_map<uint32_t, uint32_t, abslhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(robinmap2_abslhash);

static void robinmap2_xxhash(benchmark::State& state) {
    for (auto _ : state) {
        robin_hood::unordered_flat_map<uint32_t, uint32_t, xxhash_function<uint32_t>> m{};
        for(uint32_t i = 0; i < 1'000'000; i++) {
            m[i] = i;
        }
    }
}
BENCHMARK(robinmap2_xxhash);
#endif

static void spdlog_bench_json(benchmark::State& state) {
    auto time_since_epoch = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
    auto file_sink = make_shared<spdlog::sinks::basic_file_sink_mt>(fmt::format("logs/log-{}.txt", time_since_epoch.count()), true);

    auto logger = make_shared<spdlog::logger>("multi_sink"s, spdlog::sinks_init_list{file_sink});
    spdlog::set_default_logger(logger);

    for (auto _ : state) {
        spdlog::info(R"({ "test": {"key": 1}})");
    }

    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(spdlog_bench_json);

int main(int argc, char** argv) {
    string hash = "hash";
    uint64_t res = 0;
    for(uint32_t i = 0; i < 1'000'000; i++) {
        res += folly::external::farmhash::Hash32WithSeed(hash.c_str(), hash.size(), 1);
    }
    PREVENT_OPT(res);

    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
  }