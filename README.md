```
2019-12-15 22:17:09
Running ./hashcontainerscomparison
Run on (24 X 3800 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 512 KiB (x12)
  L3 Unified 16384 KiB (x4)
Load Average: 3.27, 1.87, 1.41
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
wyhash                   1.25 ns         1.25 ns    572208054
wyhash_large           188236 ns       188201 ns         3707
farmhash                 3.61 ns         3.61 ns    193468953
farmhash_large         199820 ns       199784 ns         3505
abslhash                 3.05 ns         3.04 ns    230604692
abslhash_large         197011 ns       196980 ns         3460
xxhash                   1.94 ns         1.94 ns    358991244
xxhash_large           106293 ns       106233 ns         6616
stdhash                  3.12 ns         3.12 ns    224562873
stdhash_large          453851 ns       453528 ns         1539
unordered_wyhash    211774222 ns    211417053 ns            4
unordered_farmhash  205877064 ns    205529537 ns            3
unordered_abslhash  204440419 ns    204097655 ns            3
unordered_xxhash    204853124 ns    204500158 ns            3
unordered_stdhash    34924595 ns     34862314 ns           20
robinmap_wyhash      30364019 ns     30310119 ns           23
robinmap_farmhash    46630956 ns     46553275 ns           15
robinmap_abslhash    43951365 ns     43873909 ns           17
robinmap_xxhash      33947286 ns     33888855 ns           20
robinmap_stdhash      8226324 ns      8211349 ns           86
f14map_wyhash        29132463 ns     29083718 ns           24
f14map_farmhash      41935244 ns     41863723 ns           17
f14map_abslhash      39962076 ns     39894520 ns           17
f14map_xxhash        33119835 ns     33061425 ns           21
f14map_stdhash       24374492 ns     24330579 ns           30
abslmap_wyhash       36785221 ns     36725510 ns           19
abslmap_farmhash     48092284 ns     48014428 ns           15
abslmap_abslhash     46332648 ns     46262451 ns           15
abslmap_xxhash       41258379 ns     41190146 ns           17
abslmap_stdhash    1021044467 ns   1020010426 ns            1
robinmap2_wyhash     39249166 ns     39176890 ns           18
robinmap2_farmhash   51167798 ns     51070758 ns           14
robinmap2_abslhash   49976111 ns     49964992 ns           13
robinmap2_xxhash     46862275 ns     46850012 ns           15
robinmap2_stdhash    22499119 ns     22490111 ns           32
spdlog_bench_json         129 ns          129 ns      5158873 items_per_second=7.7239M/s

```
