cmake_minimum_required(VERSION 3.3)
project(MasterProjekt)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmakeModules/")

find_package(Threads REQUIRED)
find_package(GMP REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/math_bigint.cpp
        src/crypto_diffieHellman.cpp)
set(HEADER_FILES include/math_bigint.h
        include/crypto_diffieHellman.h)
set(MEASUREMENT_FILES src/profiler.cpp
        include/profiler.h
        src/main_measurement.cpp)
set(DEMONSTRATOR_FILES src/main.cpp)
set(TEST_FILES tests/math_bigint_assignment.cpp
        tests/math_bigint_constructor.cpp
        tests/math_bigint_comparison.cpp
        tests/math_bigint_unary.cpp
        tests/math_bigint_arithmetic.cpp
        tests/math_bigint_utility.cpp
        src/main_test.cpp)

add_executable(MasterProjekt ${SOURCE_FILES} ${DEMONSTRATOR_FILES} ${HEADER_FILES})
add_executable(MasterProjekt_Test ${SOURCE_FILES} ${TEST_FILES} ${HEADER_FILES})
add_executable(MasterProjekt_Measurement ${SOURCE_FILES} ${HEADER_FILES} ${MEASUREMENT_FILES})
include_directories(./googletest/googletest/include)

target_link_libraries(MasterProjekt_Test
        ${CMAKE_SOURCE_DIR}/googletest/googletest/build/libgtest.a
        ${CMAKE_SOURCE_DIR}/googletest/googletest/build/libgtest_main.a
        gmp
        gmpxx
        )
target_link_libraries(MasterProjekt_Test Threads::Threads)

target_link_libraries(MasterProjekt_Measurement gmp gmpxx)
target_link_libraries(MasterProjekt gmp gmpxx)