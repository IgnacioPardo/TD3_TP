cmake_minimum_required(VERSION 3.0)

project(TP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

include (CTest)

add_executable(red_social red_social_main.cpp RedSocial.cpp)
add_executable(red_social_tests red_social_tests.cpp RedSocial.cpp)

target_link_libraries(
  red_social_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(red_social_tests)
