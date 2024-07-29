cmake_minimum_required(VERSION 3.15)
project(cpp_file_example VERSION 1.0)

# #################### Setup compiler options #######################
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json.

# Read the sources file into a variable
set(SOURCES_FILE "${CMAKE_SOURCE_DIR}/file_to_build.txt")
file(STRINGS ${SOURCES_FILE} cpp_file_example_SOURCES)

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
)
