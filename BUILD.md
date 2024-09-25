# How to build examples

- [Build](#build)
  - [Prerequisites](#prerequisites)
  - [Clone the repository](#clone-the-repository)
  - [Build examples with VSCode (preferred)](#build-examples-with-vscode-preferred)
  - [Build examples with CMake](#build-examples-with-cmake)
  - [Build examples manually](#build-examples-manually)
- [Troubleshooting](#troubleshooting)
  - [Forward `python3` to `python` to make VSCode tasks works on Ubuntu](#forward-python3-to-python-to-make-vscode-tasks-works-on-ubuntu)
  - [Connect to vagrant box from VSCode](#connect-to-vagrant-box-from-vscode)

## Build

### Prerequisites

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

### Clone the repository

```bash
git clone --recurse-submodules https://github.com/marleeeeeey/cpp_notes.git
```

### Build examples with VSCode (preferred)

CMake build preferred before manual build because it generates `compile_commands.json` for better integration with VSCode.

1. Open the repository in VSCode.
2. Open `code/*.cpp` file you want to build and start task `010. Set Current File As Source`.
3. Start task `040. + Run` to build and run the program. See settings in [.vscode/tasks.json](.vscode/tasks.json).
4. For debugging press `F5`. It will build the program and start debugging with `lldb`. See settings in [.vscode/launch.json](.vscode/launch.json).

Video example of usage VSCode with My Task Runner setup for C++ development: [YouTube](https://www.youtube.com/watch?v=-Tg7pT-8Rhc).

### Build examples with CMake

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

### Build examples manually

To build the examples, you may use any C++ compiler. Every file is a separate program. For example:

```
clang -O2 -g code/hello_world.cpp -o build/hello_world.exe
```

## Troubleshooting

### Forward `python3` to `python` to make VSCode tasks works on Ubuntu

```bash
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 1
```

### Connect to vagrant box from VSCode

1. `echo "ssh-rsa ..." >> ~/.ssh/authorized_keys` to add your public key to the `vagrant` user.
1. Install the [Remote - SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh) extension.
2. Press `F1` and type `Remote-SSH: Connect to Host...`.
3. Enter `vagrant@127.0.0.1 -p 2222`.
