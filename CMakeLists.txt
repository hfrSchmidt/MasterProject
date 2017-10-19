cmake_minimum_required(VERSION 3.3)
project(MasterProjekt)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/math_bigint.cpp)
set(HEADER_FILES include/math_bigint.h)
set(TEST_FILES tests/bigint_tests.cpp)

add_executable(MasterProjekt ${SOURCE_FILES} ${TEST_FILES} ${HEADER_FILES})
include_directories(./googletest/googletest/include)

target_link_libraries(MasterProjekt
        /home/hs/CLionProjects/MasterProjekt/googletest/googletest/build/libgtest.a
        /home/hs/CLionProjects/MasterProjekt/googletest/googletest/build/libgtest_main.a
        )
target_link_libraries(MasterProjekt Threads::Threads)
