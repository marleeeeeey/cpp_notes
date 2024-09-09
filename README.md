# C++ theory and code examples

- [Overview](#overview)
- [Courses and materials](#courses-and-materials)
- [How to build the examples](#how-to-build-the-examples)
- [Troubleshooting](#troubleshooting)

### Overview

This repository includes my notes about C++, taken after watching presentations from CppCon and other conferences, as well as reading books. The complete list of references is available in this file [LINKS.md](/LINKS.md).

In the [code folder](/code), there are examples of my programs illustrating the intricacies of the C++ language.

*The notes are made in a single file, mixed in both English and Russian.

### Courses and materials

- [Konstantin Vladimirov](https://github.com/tilir) - "C++ базовый курс, MIPT" - 2021-2022
  - [Youtube playlist](https://www.youtube.com/playlist?list=PL3BR09unfgciJ1_K_E914nohpiOiHnpsK)
  - [Original Code Samples](submodules/cpp-graduate/)
  - [Slides](https://sourceforge.net/projects/cpp-lects-rus/files/cpp-graduate/)
  - [My Code Samples](/code/tilir_basics/)
  - [**My Full Notes**](2024-07-18_0010_TILIR_BASICS_FULL.md)
  - [**MY Mini Notes**](2024-07-18_0020_TILIR_BASICS_MINI.md)
- [Konstantin Vladimirov](https://github.com/tilir) - "Магистерский курс C++, MIPT" - 2022-2023
  - [Youtube playlist](https://www.youtube.com/playlist?list=PL3BR09unfgcgf7R88ZQRQqWOdLy4pRW2h)
  - [Original Code Samples](submodules/cpp-masters/)
  - [My Code Samples](/code/tilir_masters/)
  - [**My Full Notes**](2024-08-09_0010_TILIR_MASTERS_FULL.md)
  - [**MY Mini Notes**](2024-08-09_0020_TILIR_MASTERS_MINI.md)
- [HolyBlackCat](https://github.com/HolyBlackCat)
  - [My Notes](2024-08-08_0010_HolyBlackCat.md)
- [Fedr](https://github.com/Fedr)
  - [My Code Samples](/code/fedr/)
- [Antony Polukhin](https://github.com/apolukhin)
  - [My Notes](2024-08-10_0010_POLUKHIN.md)
  - [Boost Code Samples](submodules/apolukhin_boost_code/)
- [Sergey Slotin](https://github.com/sslotin)
  - [My Notes](2024-08-12_0010_SERGEY_SLOTIN_FULL.md)
- [Torjo](https://github.com/jtorjo) - Boost.Asio C++ Network Programming
  - [My Notes](2024-09-04_0300_Torjo_Boost_Asio.md)
  - [Code Samples](code/torjo_boost_asio/)
- [Sonmez](https://simpleprogrammer.com) - Soft Skills: The software developer's life manual
  - [My Notes](2024-09-09_0046_Sonmez_Soft_Skills.md)

### How to build the examples

#### Prerequisites

- C++ compiler with C++23 support ([Clang](https://clang.llvm.org), [GCC](https://gcc.gnu.org), [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/))
- [CMake](https://cmake.org) (optional*)
- [Ninja](https://ninja-build.org) (optional*)
- [VSCode](https://code.visualstudio.com) (optional*)
- lldb (optional*)
- [python](https://www.python.org) (optional*) - for VSCode task automation.
- [Deleaker](https://www.deleaker.com) (optional*) - for memory leak detection on Windows (analog of Valgrind).
- [Google Benchmark](https://github.com/google/benchmark) (optional* as submodule) - for performance testing.
- [Google Test](https://google.github.io/googletest/) (optional* loaded via CMake) - for unit testing.

_* Optional tools are used for better integration with VSCode and debugging._

#### Clone the repository

```bash
git clone --recurse-submodules https://github.com/marleeeeeey/cpp_notes.git
```

#### Build examples with VSCode (preferred)

CMake build preferred before manual build because it generates `compile_commands.json` for better integration with VSCode.

1. Open the repository in VSCode.
2. Open `code/*.cpp` file you want to build and start task `010. Set Current File As Source`.
3. Start task `040. + Run` to build and run the program. See settings in [.vscode/tasks.json](.vscode/tasks.json).
4. For debugging press `F5`. It will build the program and start debugging with `lldb`. See settings in [.vscode/launch.json](.vscode/launch.json).

Video example of usage VSCode with My Task Runner setup for C++ development: [YouTube](https://www.youtube.com/watch?v=-Tg7pT-8Rhc).

#### Build examples with CMake

To build the examples with CMake, you may use the following commands:

```
mkdir build && cd build
mkdir debug && cd debug
cmake -E echo ../../code/hello_world.cpp > file_to_build.txt
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug -GNinja -DCMAKE_CXX_COMPILER=clang++
cmake --build build/debug -- -k 0
./build/debug/cpp_file_example.exe
```

*You have to choose which file to build by editing the `file_to_build.txt` file.

#### Build examples manually

To build the examples, you may use any C++ compiler. Every file is a separate program. For example:

```
clang -O2 -g code/hello_world.cpp -o build/hello_world.exe
```

### Troubleshooting

#### Connect to vagrant box from VSCode

1. `echo "ssh-rsa ..." >> ~/.ssh/authorized_keys` to add your public key to the `vagrant` user.
1. Install the [Remote - SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh) extension.
2. Press `F1` and type `Remote-SSH: Connect to Host...`.
3. Enter `vagrant@127.0.0.1 -p 2222`.
