- [Fist sight of Dev Tools](#fist-sight-of-dev-tools)
  - [valgrind - memory leak detection](#valgrind---memory-leak-detection)
- [David Faure and Timo Buske - KDAB - Profiling and Debugging Tools](#david-faure-and-timo-buske---kdab---profiling-and-debugging-tools)
  - [Overview of Debugging Tools for C/C++ applications](#overview-of-debugging-tools-for-cc-applications)
  - [Overview of Profiling Tools for C/C++ applications](#overview-of-profiling-tools-for-cc-applications)
  - [Overview of Graphics Optimization Tools for OpenGL applications](#overview-of-graphics-optimization-tools-for-opengl-applications)
  - [KDAB training course: Debugging and Profiling C/C++ applications on Linux](#kdab-training-course-debugging-and-profiling-cc-applications-on-linux)
- [Mathieu Ropert - The Basics of Profiling - CppCon 2021](#mathieu-ropert---the-basics-of-profiling---cppcon-2021)
  - [About this talk](#about-this-talk)
  - [1. Profiling](#1-profiling)
  - [2. Profiling in Practice](#2-profiling-in-practice)
  - [3. Profiling analysis](#3-profiling-analysis)
  - [In conclusion](#in-conclusion)

## Fist sight of Dev Tools

### valgrind - memory leak detection

- https://www.youtube.com/watch?v=A5Rc4AwdaOA

```bash
# -g: include debugging information
# -Og: optimization level
# -std=gnu99: use C99 standard
gcc -g -Og -std=gnu99 memory_leak.c -o memory_leak
./memory_leak # no any error
valgrind ./memory_leak #                                                    <=== memory leak detected
valgrind --leak-check=full ./memory_leak # more detailed information
# example of leak detection
# ==12345== 1 bytes in 1 blocks are definitely lost in loss record 1 of 1
# ==12345==    at 0x4C2E0F3: malloc (vg_replace_malloc.c:299)
# ==12345==    by 0x4005A1: main (memory_leak.c:5)                          <=== line number
```

## David Faure and Timo Buske - KDAB - Profiling and Debugging Tools

- https://www.youtube.com/watch?v=2cAHLFM6IU0&list=PL6CJYn40gN6hLwcJ2cgLNtsbr6zUMZSEJ

### Overview of Debugging Tools for C/C++ applications

- https://www.kdab.com/c-cpp-debugging-tools/

- **Automated testing**: `TDD`(write test first, then write code), `QTestLib`, `GTest`, `Catch` + Integration to CI/CD.
- **Code coverage**: `gcov` for GCC/Clang, `Visual Studio` or `OpenCppCoverage`[TODO] for MSVC, `Squish Coco`, `BullseyeCoverage`.
- **Static code analysis**: All warnings enabled, PVS-Studio, Coverity, Use different compilers.
- **Logging**: `printf`, `cout`, `qDebug`, categorized logging: `log4cxx`... Allowed to on/off logging categories.
- **Assertions**:
  - Runtime assertions (`assert`): stop the application and allowed to debug.
  - Compile-time assertions: `static_assert`.
- **Tracing**:
  - Investigate linking libraries: `ldd` (Linux), `depends.exe` (Windows), `otool` (macOS).
  - Trace system calls: `strace` (Linux), `procmon` or `apimonitor` (Windows), `dtruss` (macOS).
- **Debuggers**:
  - Linux: `gdb`, `RR` (recording. Allow forwards and backwards debugging).
  - Windows: `Visual Studio Debugger`, `WinDbg`.
  - macOS: `lldb`.
- **Gammaray**: Introspect Qt applications. Inspect and manipulate Qt applications at runtime.
- **valgrind**: Support Linux and Mac. Check memory leaks, invalid memory access. Other tools:
  - memcheck: find memory leaks and detect related errors.
  - helgrind: find race conditions and lock order violations (prefer Sanitizers).
  - massif: profile stack and heap memory usage (prefer Heaptrack).
  - callgrind: profile CPU usage, detect cache misses and count instructions, funcion calls (in general, prefer Hotspot).
- **Sanitizers**: Linux: GCC4.9+, Clang 3.1+. Windows: Clang 6+, MSVC-2019-16.4+. Ask compiler to inject code to check for errors:
  - `address`: memory error detector.
  - `thread`: detect data races.
  - `undefined`: check code for undefined behavior.

### Overview of Profiling Tools for C/C++ applications

#### Steps

- **1. Assessment**: `Which` aspects of performance are most important for my project?
- **2. Tool Selection**: `How` to measure, which one tool to use?
- **3. Benchmarking**: Creating a reliable, repeatable infrustracture for running benchmarks. Measuaring the performance of specific task.
- **4. Profiling**: Identifying hotspots and performance issues.
- **5. Updates**: Suggesting code changes and assessing their ourcome. Go back to step 4.

#### Tool selection (for steps 2 - 5):

- **Performance and CPU measurments**
  - **Intel VTune**:
    - Very powerful, good UI, Linux and Windows.
    - Free as part of Intel System Studio.
    - Requires Intel hardware.
  - **Perf**
    - Very powerful, part of Linux kernel.
    - Works on x86, ARM, PPC and SH processors.
    - No GUI, hard to use.
  - **Hotspot**
    - Free, Open-source GUI for perf, written by KDAB.
    - Eeasy to use, supports the most common use cases: CPU cyclesm, off-CPU time.
    - Example of the kind of issues Hotspot can find and to download it: https://www.kdab.com/hotspot-to-fix-string-copy/
    - Demo of Hotspot: https://www.kdab.com/hotspot-video/

- **Measure Memory allocations**: when application use too much memory.
  - **valgrind massif**: slow.
  - **Heaptrack**:
    - Heap memory profiler for Linux.
      - Count allocations and find temporary memory allocations.
      - Aggregates requests memory sizes.
      - Backtraces for every allocation.
    - Less overhead than valgrind's `massif`.
    - Supports runtime attach/detach.
    - Better GUI then `massif-visualizer`.
      - Can diff two executions.

### Overview of Graphics Optimization Tools for OpenGL applications

- How it works
  - Record trace.
  - Open trace in 3D profiling tool.

- Common profiling tools:
  - **RenderDoc** - Open-source, cross-platform, supports OpenGL, Vulkan, D3D11, D3D12.
  - **apitrace** - record and replay OpenGL calls.
  - **Visual Studio Graphics Debugger / DXCap** - inspect DirectX calls.
  - **XCode GPU tools**
  - **GAPID**
  - **WebGL Inspector**
  - **Qt3D Profiler**

- Vendor tools
  - Intel: `Graphics Performance Analyzers Framework` / `VTune` - profiling multiframe streams and inspect CPU/GPU usage.
  - NVidia: `Nsight` - tool for OpenGL, Vulkan, D3D11, D3D12. Usefull for CUDA.
  - AMD: `GPU PerfStudio`, `CodeXL` .
  - ARM: `Mali Graphics Debugger`.

### KDAB training course: Debugging and Profiling C/C++ applications on Linux

- https://training.kdab.com/portfolio/debugging-and-profiling-cpp-applications-on-linux/

- Debugging C++ Applications
  - Debug Symbols, Compiler Optimizations
  - Testing
  - Code Coverage
  - Tracing
  - Debugger
  - RenderDoc
  - Valgrind
  - Sanitizers
  - Assertions
  - Static Code Analysis
  - Crash Reporting

- Profiling C++ Applications
  - Introduction
  - Profiling Setup for C++ Applications
  - Manual Timing
  - Linux Perf
  - VTune
  - Valgrind Profiling Tools
  - Heaptrack
  - LTTng
  - OpenGL
  - Conclusion

- Appendix
  - Tracing
  - Instrumentation
  - Sampling
  - Performance Counters
  - Backtraces
  - Other Notes

## Mathieu Ropert - The Basics of Profiling - CppCon 2021

- https://www.youtube.com/watch?v=dToaepIXW4s
- Here's how I found what was slow

### About this talk

- Profiling
- Tools for profiling (profiling in practice)
- Building an intuition

### 1. Profiling

- The real problem is that programmers have spent far too much time worrying about efficiency in the wrong places and at the wrong times;
- premature optimization is the root of all evil (Donald Knuth).

#### Why profiling

- Figuring why a program is slow is hard.
- Reading the code can easily mislead you.
- Modern CPUs are complex and unpredictable.
- Measure, measure, measure! Don't guess.

#### Tools for profiling

- Tools to help programmers measure and reason about the performance.
- Profiler helps with measuring but may have observable impact on the program.

```mermaid
graph TD
    O[Begin] --> A[Measure]
    A --> B{Happy?}
    B -- Yes --> C[Done!]
    B -- No --> D[Optimize]
    D --> A
```

#### Profiling vs Optimizations

- Profilers are one of the tools that can be used during an optimization iteraion cycle.
- Better used to investigate where to optimize.
- Can be used to measure if an optimiation was effective, within limits.

#### Profile usage

- Indentify hotspots and bottlenecks.
- Visualize execution timeline.
- Collect and compute metrics.

#### Sampling Profiling (Профилирование методом выборки)

- Attach to program, periodically interrupt and record the stack trace.
- Sampling frequency is customizable.
- Results are `statistical averages`.
- => where is program spending most of its time?
- Example tool: `VTune`.
- Only needs to be able to read stack trace.
- Symbol table is needed. Minimal debug info is enough.
- Not need to recompile the program.
- Works out of the box on any executable.
- Inline funcions are usually invisible.

#### Instrumentation profiling (подход с добавлением хуков в код)

- Add code hooks to explicitly record metrics.
- Can provide both: `averages` and `exact breakdown` by execution frame.
- Not affected by inlining or statistical anomalies.
- Example tool: `Optick`. https://github.com/bombomby/optick
- Requires programmers to add collection macros in tactical places in the code.
- Support adding extra business metadata. You may `match the business data with the code`.
- Can fallback on sampling: You may switch between sampling and instrumentation.
- Build implications. You have to link with 3rd party profiler library.

### 2. Profiling in Practice

#### Setting up goals

- Set up a reproducible scenario.
- Measure its performance.
- Define an objective (target) - ones I reached it, I'm good.

#### Using the right tool

- Instumentation (+some sampling) is recommended way to go.
- Sampling alone is cheaper to start with.
- Consider adding instrumentation as an investment.

#### Questions and Answers

(Author is more focusing on Windows infra and tools then Linux)
- `valgrind` is a profiler?
  - No, it's a memory checker.
  - `Callgrind` is closer to a profiler.
- If you unaware of `Optick` how did you do `instrumentation(frame) profiling` in VTune?
  - With great difficulty.
  - VTune supports to annotate frame, but it is slow and very heavy. Visulalization is not very good.
  - I convert the data between VTune and Optick.
- `perf` is a sampling profiler?
  - Yes, it is. But I am not sure.
- Any recomentations to profile `compilation time`?
  - Most compilers have a flag to profile compilation time.

#### Live Demo

- https://youtu.be/dToaepIXW4s?t=1855

#### Finding the needle

- first time look at profile, you may be overwhelmed.
- Look at what sticks out.
- Domain knowlage is key.

#### Know the program

- A profiler can tell `what takes the most time`.
- It can explain why: using a lot of CPU cycles, cache misses or ...
- It can't tell if it should.

#### Hunting disprecencies (Поиск несоотвествий)

- Performance regressions become easy to spot once the normal profile outline is known.
- `What takes time` vs `what should take time`.
- Practice example: https://youtu.be/dToaepIXW4s?t=2368

#### Best work is no work

- Most efficient code does nothing.
- Profiling can highlight useless computation.
- No need to dive deep into metrics.

#### Profiling for the first time

- Access the big picture.
- Understanding the domain is key to fidure our where to start digging.
- Get quick wins out of the way before deling deeper.

### 3. Profiling analysis

#### Profiling Metrix

- CPU Time
- Wait Time
- (System Time)

#### High CPU Time

- Inefficient algorithm or data structure.
- Spin locks.
- Single-threaded code.
- Branch misprediction, cache misses.

#### High Wait Time

- Disk I/O.
- Network calls.
- Locks.
- Syncronization primitives.

#### Example of VTune output

![vtune_summary_screenshot](screenshots/vtune_summary_screenshot.png)

В программе Intel VTune выделенные в рамку понятия относятся к различным временным показателям, которые помогают анализировать производительность приложения:

1. **Elapsed Time** (Общее время выполнения) — это общее время, которое прошло с начала выполнения программы до её завершения. Оно включает в себя все компоненты, такие как время работы процессора и время простоя.

2. **CPU Time** (Время процессора) — это время, в течение которого программа активно использовала процессор для выполнения задач. Здесь показано, сколько процентов от общего времени выполнения программы было потрачено на обработку данных процессором.

3. **Effective Time** (Эффективное время) — это время, когда процессор был реально занят выполнением полезных вычислений, в отличие от времени, которое могло быть потрачено впустую из-за блокировок или ожидания ресурсов.

4. **Spin Time** (Время ожидания) — это время, в течение которого потоки программы находятся в цикле ожидания (спинлоке), ожидая освобождения ресурса, не выполняя при этом никакой полезной работы.

5. **Overhead Time** (Накладные расходы) — это время, потраченное на дополнительные операции, не связанные с полезной работой программы, например, управление потоками или контекстные переключения.

#### Filtering Metrics

- Sampling views usually aggregate call stacks actoss threads.
- Consider filtering on main bottlenecks thread.
- 2D control flow view from instrumented prifilers helps a lot.

#### Inefficient Algorithms

- Time spent in loops and recursive calls.
- Check the Big O complexity.
- Can som computations be cached and reused?

#### Inefficient Data Structures

- Example: https://youtu.be/dToaepIXW4s?t=3097
- Time spent in `find`, `insert` or `operator[]`.
- Easier to spot without inlining. Легче заметить проблемы с производительностью, если не используются оптимизации компилятора, такие как инлайнинг.
- Know your data structures strengths and weaknesses. Необходимо хорошо понимать сильные и слабые стороны используемых структур данных. Например, одни структуры данных лучше подходят для быстрых вставок, другие — для быстрого поиска.

#### Spin Locks

- High spin time in profiler or equivalent tagget functions in instrumented profiler.
- Look at the bigger picture and threading model.
- Check out talks about concurrency.

#### Single-threaded Code

- Low core usage in timeline.
- Consider parallelizing.
- ... or a task scheduler.

#### Micro-arhitecture Usage

- High CPI (Cycles per Instruction) rate.
- More and more important on modern CPUs.
- Micro-optimization on large applications is tricky.
- Keep it for last. Don't start with it.

#### Blocking I/O

- High wait/system time in filesystem or network API.
- Can it be put in an async task instead?
- See CppCon talk: Making Games Start Fast - A Story About Concurrency.
- https://www.youtube.com/watch?v=TcuPIVKNSN0

#### Wait on Mutex or Semaphore

- High wait time or synchronization functions.
- Remember: "It should'n be called a mutex, it should be called a bottleneck".
- Consider changing concurrency model. Lock-Free?

#### Profiling Analysis (На что стоит обратить внимание в первую очередь)

- Profiling will show what stick out.
- Some filtering needs to be done by the deverloper to focus on the right part.
- Deal with inefficiencies algorithms, data structures and locks first.

### In conclusion

- Profilers help pinpointing performance bottlenecks.
- Domain knowledge can speed up the analisys by a lot.
- Add instrumentation support to your program.
