// fib.c
#include <stdio.h>
#include <stdlib.h>

int fib(int x) {
  if (x == 0) return 0;
  else if (x == 1) return 1;
  return fib(x - 1) + fib(x - 2);
}

int main(int argc, char *argv[]) {

  for (size_t i = 0; i < 45; ++i) {
    printf("%d\n", fib(i));
  }
  return 0;
}

// 1. Temporary upblock:
// sudo sysctl -w kernel.perf_event_paranoid=1
// sudo sysctl -w kernel.kptr_restrict=0

// 2. Permanent upblock:
// sudo nano /etc/sysctl.conf
// kernel.perf_event_paranoid = 1
// kernel.kptr_restrict = 0
// sudo sysctl -p

// 3. It should work after 1 or 2
// sudo cat /proc/kallsyms

// 4. Then record:
// perf record ./cpp_file_example

// 5. Then analize:
// perf report