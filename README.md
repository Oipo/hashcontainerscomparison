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
unordered_nohash                       29284459 ns     29276919 ns           23
robinmap_nohash                        15116214 ns     14696009 ns           48
f14map_nohash                          54423221 ns     54410284 ns           10
abslmap_nohash                        537770897 ns    537712113 ns            1
robinmap2_nohash                       12354439 ns     12351018 ns           55
unordered_put_wyhash                  290343366 ns    290273542 ns            2
unordered_put_farmhash                296246271 ns    296178511 ns            2
unordered_put_abslhash                295404240 ns    295327290 ns            2
unordered_put_xxhash                  293432604 ns    293363694 ns            2
unordered_put_stdhash                 293623768 ns    293542034 ns            2
robinmap_put_wyhash                   141808113 ns    140631748 ns            5
robinmap_put_farmhash                 141708542 ns    140755552 ns            5
robinmap_put_abslhash                 143455475 ns    142326781 ns            5
robinmap_put_xxhash                   151827215 ns    151009155 ns            5
robinmap_put_stdhash                  161744641 ns    161093530 ns            4
f14map_put_wyhash                      71808133 ns     71299609 ns           10
f14map_put_farmhash                    74038678 ns     73568342 ns           10
f14map_put_abslhash                    74810101 ns     74440530 ns            9
f14map_put_xxhash                      72548056 ns     72308854 ns           10
f14map_put_stdhash                     78199867 ns     77784029 ns            9
abslmap_put_wyhash                    126883882 ns    126139984 ns            5
abslmap_put_farmhash                  128160100 ns    126780520 ns            6
abslmap_put_abslhash                  127649405 ns    126593162 ns            6
abslmap_put_xxhash                    129274841 ns    128522679 ns            5
abslmap_put_stdhash                   132983882 ns    131242171 ns            5
robinmap2_put_wyhash                  147445910 ns    146918007 ns            5
robinmap2_put_farmhash                155373025 ns    154113229 ns            5
robinmap2_put_abslhash                153128073 ns    151975447 ns            4
robinmap2_put_xxhash                  150282388 ns    148829681 ns            5
robinmap2_put_stdhash                 158357292 ns    156727767 ns            4
unordered_put_wyhash_reserve          190249689 ns    190184520 ns            4
unordered_put_farmhash_reserve        192642360 ns    192566671 ns            4
unordered_put_abslhash_reserve        192398521 ns    192333994 ns            4
unordered_put_xxhash_reserve          191013018 ns    190951753 ns            4
unordered_put_stdhash_reserve         191899032 ns    191829359 ns            4
robinmap_put_wyhash_reserve           104843548 ns    104366242 ns            6
robinmap_put_farmhash_reserve         100601534 ns     99974674 ns            7
robinmap_put_abslhash_reserve         105703079 ns    105217978 ns            7
robinmap_put_xxhash_reserve           119844405 ns    119081956 ns            5
robinmap_put_stdhash_reserve          136530437 ns    136250426 ns            5
f14map_put_wyhash_reserve              48571491 ns     47901797 ns           15
f14map_put_farmhash_reserve            47447954 ns     47141157 ns           15
f14map_put_abslhash_reserve            48270207 ns     47706671 ns           14
f14map_put_xxhash_reserve              47622961 ns     47154651 ns           15
f14map_put_stdhash_reserve             51198313 ns     50994866 ns           13
abslmap_put_wyhash_reserve            127053635 ns    126492232 ns            5
abslmap_put_farmhash_reserve          125110636 ns    123960027 ns            6
abslmap_put_abslhash_reserve          128012016 ns    127548585 ns            5
abslmap_put_xxhash_reserve            131468229 ns    130573124 ns            6
abslmap_put_stdhash_reserve           126597232 ns    126516742 ns            6
robinmap2_put_wyhash_reserve          118333060 ns    117583829 ns            6
robinmap2_put_farmhash_reserve        109460344 ns    108801724 ns            6
robinmap2_put_abslhash_reserve        110934214 ns    109857216 ns            6
robinmap2_put_xxhash_reserve          118681259 ns    117326492 ns            5
robinmap2_put_stdhash_reserve         126812076 ns    126446650 ns            6
unordered_get_wyhash                   85157267 ns     85128735 ns            8
unordered_get_farmhash                 89013228 ns     88984014 ns            8
unordered_get_abslhash                 88156452 ns     88127683 ns            8
unordered_get_xxhash                   86746724 ns     86715933 ns            8
unordered_get_stdhash                  88835863 ns     88805833 ns            8
robinmap_get_wyhash                    44315435 ns     44297179 ns           16
robinmap_get_farmhash                  57658999 ns     57638353 ns           12
robinmap_get_abslhash                  56434451 ns     56412922 ns           12
robinmap_get_xxhash                    54684389 ns     54661336 ns           13
robinmap_get_stdhash                   58424766 ns     58404230 ns           12
f14map_get_wyhash                      24398275 ns     24389330 ns           29
f14map_get_farmhash                    28422310 ns     28412379 ns           24
f14map_get_abslhash                    27800180 ns     27790040 ns           25
f14map_get_xxhash                      25534238 ns     25524035 ns           27
f14map_get_stdhash                     27646153 ns     27636451 ns           26
abslmap_get_wyhash                     54368622 ns     54349684 ns           13
abslmap_get_farmhash                   59032652 ns     59014756 ns           12
abslmap_get_abslhash                   57591878 ns     57570470 ns           12
abslmap_get_xxhash                     55073526 ns     55054925 ns           13
abslmap_get_stdhash                    58769776 ns     58751838 ns           12
robinmap2_get_wyhash                   48928932 ns     48909478 ns           14
robinmap2_get_farmhash                 52456596 ns     52436418 ns           13
robinmap2_get_abslhash                 51010745 ns     50991033 ns           14
robinmap2_get_xxhash                   50718958 ns     50700373 ns           14
robinmap2_get_stdhash                  54179504 ns     54163029 ns           13
spdlog_bench_json/iterations:1000000        195 ns          195 ns      1000000 items_per_second=5.13081M/s
wyhash_small                               1.24 ns         1.24 ns    559776958
wyhash_large                             189764 ns       189739 ns         3689
farmhash_small                             3.71 ns         3.71 ns    188176881
farmhash_large                           201435 ns       201404 ns         3476
abslhash_small                             3.05 ns         3.05 ns    228753235
abslhash_large                           199912 ns       199883 ns         3495
xxhash_small                               1.94 ns         1.94 ns    359118242
xxhash_large                             109377 ns       109361 ns         6414
stdhash_small                              3.22 ns         3.22 ns    217174117
stdhash_large                            466353 ns       466280 ns         1502


```
