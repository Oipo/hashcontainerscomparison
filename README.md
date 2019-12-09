```
2019-12-09 22:16:40
Running ./hashcontainerscomparison
Run on (24 X 3800 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 512 KiB (x12)
  L3 Unified 16384 KiB (x4)
Load Average: 1.37, 1.02, 0.93
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
wyhash                   1.19 ns         1.19 ns    587837703
wyhash_large           181802 ns       181779 ns         3856
farmhash                 3.51 ns         3.51 ns    198804305
farmhash_large         192941 ns       192919 ns         3623
abslhash                 2.89 ns         2.89 ns    235052752
abslhash_large         190311 ns       190291 ns         3677
unordered_wyhash    212327044 ns    212258938 ns            4
unordered_farmhash  207496174 ns    207437167 ns            3
unordered_abslhash  208667617 ns    208610625 ns            3
robinmap_wyhash      31131652 ns     31118509 ns           24
robinmap_farmhash    48749865 ns     48735174 ns           14
robinmap_abslhash    44615053 ns     44601077 ns           16
f14map_wyhash        27266223 ns     27258496 ns           25
f14map_farmhash      39968322 ns     39958795 ns           18
f14map_abslhash      38219090 ns     38209450 ns           18
abslmap_wyhash       36503267 ns     36492979 ns           19
abslmap_farmhash     44067344 ns     44057352 ns           16
abslmap_abslhash     40772994 ns     40762504 ns           16
```
