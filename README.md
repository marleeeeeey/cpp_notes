# C++ theory and code examples

- [Overview](#overview)
- [Courses and materials](#courses-and-materials)
- [How to build the examples](#how-to-build-the-examples)

### Overview

This repository includes my notes about C++, taken after watching presentations from CppCon and other conferences, as well as reading books. The complete list of references is available in this file [LINKS.md](/LINKS.md).

In the [code folder](/code), there are examples of my programs illustrating the intricacies of the C++ language.

*The notes are made in a single file, mixed in both English and Russian.

### Courses and materials

- [Konstantin Vladimirov](https://github.com/tilir)
  - "C++ базовый курс, MIPT" - 2021-2022
    - [Youtube playlist](https://www.youtube.com/playlist?list=PL3BR09unfgciJ1_K_E914nohpiOiHnpsK)
    - [Original Code Samples Repository](https://github.com/tilir/cpp-graduate)
    - [Slides](https://sourceforge.net/projects/cpp-lects-rus/files/cpp-graduate/)
    - [My Code Samples](/code/tilir_basics/)
    - [**My Full Notes**](2024-07-18_0010_TILIR_BASICS_FULL.md)
    - [**MY Mini Notes**](2024-07-18_0020_TILIR_BASICS_MINI.md)
  - "Магистерский курс C++, MIPT" - 2022-2023
    - [Youtube playlist](https://www.youtube.com/playlist?list=PL3BR09unfgcgf7R88ZQRQqWOdLy4pRW2h)
    - [Original Code Samples Repository](https://github.com/tilir/cpp-masters)
    - [My Code Samples](/code/tilir_masters/)
    - [**My Full Notes**](2024-08-09_0010_TILIR_MASTERS_FULL.md)
    - [**MY Mini Notes**](2024-08-09_0020_TILIR_MASTERS_MINI.md)
- [HolyBlackCat](https://github.com/HolyBlackCat)
  - [My Notes](2024-08-08_0010_HolyBlackCat.md)
- [Fedr](https://github.com/Fedr)
  - [My Code Samples](/code/fedr/)
- [Antony Polukhin](https://github.com/apolukhin)
  - [My Notes](2024-08-10_0010_POLUKHIN.md)
- [Sergey Slotin](https://github.com/sslotin)
  - [My Notes](2024-08-12_0010_SERGEY_SLOTIN_FULL.md)

### How to build the examples

#### Prerequisites

- C++ compiler with C++23 support (Clang, GCC, MSVC)
- CMake (optional*)
- Ninja (optional*)
- VSCode (optional*)
- lldb (optional*)
- python (optional*) - for VSCode task automation.
- Deleaker (optional*) - for memory leak detection on Windows (analog of Valgrind).

_* Optional tools are used for better integration with VSCode and debugging._

#### Build examples with VSCode (preferred)

CMake build preferred before manual build because it generates `compile_commands.json` for better integration with VSCode.

1. Open the repository in VSCode.
2. Open `code/*.cpp` file you want to build and start task `010. Set Current File As Source`.
3. Start task `040. + Run` to build and run the program. See settings in [.vscode/tasks.json](.vscode/tasks.json).
4. For debugging press `F5`. It will build the program and start debugging with `lldb`. See settings in [.vscode/launch.json](.vscode/launch.json).

#### Build examples with CMake

To build the examples with CMake, you may use the following commands:

```
mkdir build && cd build
mkdir Debug && cd Debug
cmake -E echo ../../code/hello_world.cpp > file_to_build.txt
cmake -S . -B build/Debug -DCMAKE_BUILD_TYPE=Debug -GNinja -DCMAKE_CXX_COMPILER=clang++
cmake --build build/Debug -- -k 0
./build/Debug/cpp_file_example.exe
```

*You have to choose which file to build by editing the `file_to_build.txt` file.

#### Build examples manually

To build the examples, you may use any C++ compiler. Every file is a separate program. For example:

```
clang -O2 -g code/hello_world.cpp -o build/hello_world.exe
```
