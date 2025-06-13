cmake_minimum_required(VERSION 3.10)
project(conkey)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE
     Sources
     src/lexer/*.cpp
     src/parser/*.cpp
)

file(GLOB_RECURSE
     Test_Sources
     test/*.cpp
)
enable_testing()

add_executable(conkey src/main.cpp ${Sources})
add_executable(conkey_test ${Test_Sources} ${Sources})

target_link_libraries(
    conkey_test
    GTest::gtest_main
    GTest::gmock_main
)
include(GoogleTest)
gtest_discover_tests(conkey_test)
