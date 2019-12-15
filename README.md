```
2019-12-15 22:03:41
Running ./hashcontainerscomparison
Run on (24 X 3800 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 512 KiB (x12)
  L3 Unified 16384 KiB (x4)
Load Average: 2.61, 1.55, 1.29
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
wyhash                   1.21 ns         1.21 ns    583149287
wyhash_large           184333 ns       184302 ns         3815
farmhash                 3.58 ns         3.58 ns    194247196
farmhash_large         194791 ns       194772 ns         3590
abslhash                 2.97 ns         2.97 ns    238881890
abslhash_large         192815 ns       192791 ns         3624
xxhash                   1.90 ns         1.90 ns    369353127
xxhash_large           107062 ns       107051 ns         6487
unordered_wyhash    220322867 ns    220270314 ns            4
unordered_farmhash  212389212 ns    212339366 ns            3
unordered_abslhash  213475814 ns    213415397 ns            3
unordered_xxhash    210994495 ns    210937476 ns            3
robinmap_wyhash      31752381 ns     31739365 ns           22
robinmap_farmhash    47934357 ns     47916568 ns           14
robinmap_abslhash    46138042 ns     46122762 ns           15
robinmap_xxhash      36029535 ns     36016829 ns           20
f14map_wyhash        27676754 ns     27668044 ns           26
f14map_farmhash      42466715 ns     42455802 ns           16
f14map_abslhash      39903046 ns     39892705 ns           18
f14map_xxhash        32264962 ns     32255496 ns           22
abslmap_wyhash       36376623 ns     36367241 ns           19
abslmap_farmhash     49085251 ns     49073417 ns           15
abslmap_abslhash     47832787 ns     47822329 ns           15
abslmap_xxhash       39027675 ns     39017696 ns           18
robinmap2_wyhash     40663519 ns     40650446 ns           17
robinmap2_farmhash   52510290 ns     52494846 ns           13
robinmap2_abslhash   50557739 ns     50543587 ns           14
robinmap2_xxhash     47007936 ns     46994604 ns           15
spdlog_bench_json         128 ns          128 ns      5474513 items_per_second=7.78787M/s
```
