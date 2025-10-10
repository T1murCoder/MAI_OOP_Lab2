cmake_minimum_required(VERSION 3.10)

set(LAB_NAME "lab2")

project(${LAB_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(${LAB_NAME}_lib src/bit_string.cpp)
add_executable(${LAB_NAME}_exe main.cpp)

target_link_libraries(${LAB_NAME}_exe PRIVATE ${LAB_NAME}_lib)

# Добавление тестов
enable_testing()

add_executable(tests_bit_string test/bit_string_test.cpp)
target_link_libraries(tests_bit_string ${LAB_NAME}_lib gtest_main)
add_test(NAME BitStringTests COMMAND tests_day)