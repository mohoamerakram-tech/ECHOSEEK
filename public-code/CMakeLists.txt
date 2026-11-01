cmake_minimum_required(VERSION 3.20)

project(echoseek_public_safe LANGUAGES CXX)

add_library(echoseek_analysis STATIC
    src/pe_observer.cpp
)

target_include_directories(echoseek_analysis
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(echoseek_analysis PUBLIC cxx_std_20)

if(MSVC)
    target_compile_options(echoseek_analysis PRIVATE /W4 /permissive-)
else()
    target_compile_options(echoseek_analysis PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(echoseek_analysis_self_test
    tests/self_test.cpp
)

target_link_libraries(echoseek_analysis_self_test PRIVATE echoseek_analysis)

enable_testing()
add_test(NAME public_safe_analysis COMMAND echoseek_analysis_self_test)
