cmake_minimum_required(VERSION 3.15)
project(cpp_file_example VERSION 1.0)

# #################### Setup compiler options #######################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json.

# Read the sources file into a variable
set(SOURCES_FILE "${CMAKE_SOURCE_DIR}/file_to_build.txt")
file(STRINGS ${SOURCES_FILE} cpp_file_example_SOURCES)

# Create an executable with the collected source files.
add_executable(cpp_file_example ${cpp_file_example_SOURCES})

target_compile_options(cpp_file_example PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wpedantic

    # ################ Some warnings from HolyBlackCat's code. ################
    -Wdeprecated # search for deprecated functions.
    -Wextra-semi # search for unused `;` in the code.
    -Wimplicit-fallthrough # search for missing `break` and `cases` in switch cases.

    # -Wconversion # search for implicit conversions. Hard to fix everything if not applying from scratch.

    # ################### Disable some warnings temporarily. ##################
    # TODO: Disable later.
    # $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-declarations>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-copy-with-user-provided-dtor>
)
