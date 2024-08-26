cmake_minimum_required(VERSION 3.18)
project(gxhash-cpp)

add_executable(gxhash-cpp-bm
  src/gxhash.cc
  src/gxhash-bm.cc)
target_link_libraries(gxhash-cpp-bm
  benchmark)
target_compile_options(gxhash-cpp-bm
  PUBLIC "-march=armv8.2-a+crypto" "-mtune=native")

add_executable(gxhash-cpp-test
  src/gxhash.cc
  src/gxhash-test.cc)
target_link_libraries(gxhash-cpp-test
  gtest)
target_compile_options(gxhash-cpp-test
  PUBLIC "-march=armv8.2-a+crypto" "-mtune=native")
