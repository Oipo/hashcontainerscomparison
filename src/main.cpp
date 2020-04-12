#include <iostream>
#include <folly/hash/FarmHash.h>
#include <benchmark/benchmark.h>
#include "macros.h"

using namespace std;

extern std::vector<std::string> string_numbers;

int main(int argc, char** argv) {
    string hash = "hash";
    uint64_t res = 0;
    for(uint64_t i = 0; i < 1'000'000; i++) {
        res += folly::external::farmhash::Hash32WithSeed(hash.c_str(), hash.size(), 1);
    }
    PREVENT_OPT(res);


    string_numbers.reserve(1'000'000);
    for(uint64_t i = 0; i < 1'000'000; i++) {
        string_numbers.emplace_back(std::to_string(i));
    }

    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
  }