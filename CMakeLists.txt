cmake_minimum_required(VERSION 3.15)
project(cpp_file_example VERSION 1.0)

# ######################### User options ############################
option(LINK_GOOGLE_TEST "Link Google Test" OFF)
option(LINK_GOOGLE_BENCHMARK "Link Google Benchmark" OFF)
option(LINK_BOOST "Link Boost Libraries" OFF)
option(LINK_OPENSSL "Link OpenSSL" OFF)
option(LINK_LIBPNG "Link libpng" OFF)
option(PROJECT_BOOST_BEAST_CHAT_MULTI "Project Boost Beast Chat Multi" OFF)

# #################### Setup compiler options #######################
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json.

if(PROJECT_BOOST_BEAST_CHAT_MULTI)
    file(GLOB cpp_file_example_SOURCES code/boost_beast_chat_multi/*.cpp)
else()
    # Read the sources file into a variable
    set(SOURCES_FILE "${CMAKE_SOURCE_DIR}/file_to_build.txt")
    file(STRINGS ${SOURCES_FILE} cpp_file_example_SOURCES)
endif()

# Create an executable with the collected source files.
add_executable(cpp_file_example ${cpp_file_example_SOURCES})

target_compile_options(cpp_file_example PRIVATE

    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Werror -Wpedantic -Wdeprecated -Wextra-semi -Wimplicit-fallthrough -Wconversion>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Werror -Wpedantic -Wdeprecated -Wextra-semi -Wimplicit-fallthrough -Wconversion>

    # ################### Disable some warnings temporarily. ##################
    # TODO: Disable later.
    # $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-declarations>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-copy-with-user-provided-dtor>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-copy-with-dtor>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-parameter>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-variable>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-but-set-variable>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-switch>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-sign-conversion>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-unneeded-internal-declaration>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-function>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-missing-braces>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-literal-conversion>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-uninitialized>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-c99-extensions>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-lambda-capture>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-shorten-64-to-32>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-gnu-anonymous-struct>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-nested-anon-types>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-implicit-int-float-conversion>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-writable-strings>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-implicit-fallthrough>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-declarations>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-implicit-int-conversion>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-parentheses>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-vexing-parse>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-result>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-float-conversion>
)

if(LINK_GOOGLE_TEST)
    # #################### Adding Google Test #######################
    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(cpp_file_example PRIVATE GTest::gtest GTest::gtest_main)
    add_test(NAME cpp_file_example_test COMMAND cpp_file_example)
endif()

if(LINK_GOOGLE_BENCHMARK)
    # #################### Adding Google Benchmark #######################
    # https://github.com/google/benchmark
    add_subdirectory(thirdparty/benchmark)
    target_link_libraries(cpp_file_example benchmark::benchmark)
endif()

if(LINK_BOOST)
    # #################### Adding Boost Libraries #######################
    # https://cmake.org/cmake/help/latest/module/FindBoost.html
    if(POLICY CMP0167)
        cmake_policy(SET CMP0167 NEW)
    endif()

    find_package(Boost REQUIRED COMPONENTS program_options asio headers thread
        timer filesystem system random unit_test_framework)
    target_link_libraries(cpp_file_example PRIVATE
        Boost::program_options Boost::asio Boost::headers Boost::thread
        Boost::timer Boost::filesystem Boost::system Boost::random Boost::unit_test_framework)
endif()

if(LINK_OPENSSL)
    # #################### Adding OpenSSL #######################
    find_package(OpenSSL REQUIRED)
    target_link_libraries(cpp_file_example PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

if(LINK_LIBPNG)
    # #################### Adding libpng #######################
    find_package(PNG REQUIRED)
    target_link_libraries(cpp_file_example PRIVATE PNG::PNG)
endif()