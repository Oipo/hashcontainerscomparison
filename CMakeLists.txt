cmake_minimum_required(VERSION 3.13)
project(hashcontainerscomparison)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -mavx -mavx2 -DXXH_INLINE_ALL -DXXH_CPU_LITTLE_ENDIAN=1 -DSPDLOG_NO_EXCEPTIONS")

add_subdirectory(${CMAKE_SOURCE_DIR}/external/abseil-cpp)

add_executable(hashcontainerscomparison main.cpp ${CMAKE_SOURCE_DIR}/external/xxHash/xxhash.c)

include_directories("${CMAKE_SOURCE_DIR}/external/wyhash")
include_directories("${CMAKE_SOURCE_DIR}/external/robin-map/include")
include_directories("${CMAKE_SOURCE_DIR}/external/folly/")
include_directories("${CMAKE_SOURCE_DIR}/external/folly/_build")
include_directories("${CMAKE_SOURCE_DIR}/external/abseil-cpp")
include_directories("${CMAKE_SOURCE_DIR}/external/xxHash")
include_directories("${CMAKE_SOURCE_DIR}/external/robin-hood-hashing/src/include")
include_directories("${CMAKE_SOURCE_DIR}/external/benchmark/include")
include_directories("${CMAKE_SOURCE_DIR}/external/spdlog/include")

target_link_libraries(hashcontainerscomparison ${CMAKE_SOURCE_DIR}/external/benchmark/build/src/libbenchmark.a)
target_link_libraries(hashcontainerscomparison ${CMAKE_SOURCE_DIR}/external/folly/_build/libfolly.a)
target_link_libraries(hashcontainerscomparison absl::base absl::flat_hash_map absl::hash)
target_link_libraries(hashcontainerscomparison -lpthread)