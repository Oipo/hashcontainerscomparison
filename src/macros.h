#pragma once

#define PREVENT_OPT(VAR) \
    volatile auto copy1 = *((char*)&VAR); \
    volatile auto copy2 = *((char*)&VAR); \
    if (copy1 != copy2) { \
        cout << "cannot happen\n"; \
        throw runtime_error("Cannot happen, but compiler cannot know this"); \
    }

#define HASH_PUSH_BENCH(NAME, MAP_TYPE, HASH, RESERVE_MEM_COUNT) \
static void NAME (benchmark::State& state) {\
    for (auto _ : state) {\
        MAP_TYPE<std::string, uint64_t, HASH<std::string>> m{};\
        m.reserve(RESERVE_MEM_COUNT);\
        for(uint64_t i = 0; i < 1'000'000; i++) {\
            m[string_numbers[i]] = i;\
        }\
    }\
}\
BENCHMARK(NAME);

#define HASH_GET_BENCH(NAME, MAP_TYPE, HASH) \
static void NAME (benchmark::State& state) {\
    MAP_TYPE<std::string, uint64_t, HASH<std::string>> m{};\
    m.reserve(1'000'000);\
    for(uint64_t i = 0; i < 1'000'000; i++) {\
        m[string_numbers[i]] = i;\
    }\
    uint64_t res = 0; \
    for (auto _ : state) {\
        for(uint64_t i = 0; i < 1'000'000; i++) {\
            res += m[string_numbers[i]];\
        }\
    }\
    PREVENT_OPT(res); \
}\
BENCHMARK(NAME);

