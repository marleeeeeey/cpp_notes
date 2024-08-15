// clang-format off

int foo(int);

template <typename T> T maxcollatz(T n) {
  T cmax = 0, xmax = 0;
  for (T x = 2; x < n; ++x) {
    T y = x;
    T c = 0;
    while (y > 1) {
      c += 1;
      if ((y % 2) == 0)
        y = y / 2;
      else
        y = 3 * y + 1;
    }
    if (c > cmax) {
      cmax = c;
      xmax = x;
    }
  }
  return xmax;
}

#if defined(SP)

template <> int maxcollatz(int n) {
  int cmax = 0, xmax = 0;
  for (int x = 2; x < n; ++x) {
    int y = x;
    int c = 0;
    while (y > 1) {
      c += 1;
      if ((y % 2) == 0)
        y = y / 2;
      else
        y = 3 * y + 1;
    }
    if (c > cmax) {
      cmax = c;
      xmax = x;
    }
  }
  return xmax;
}

#endif

#if defined(SPI)

template <> inline int maxcollatz(int n) {
  int cmax = 0, xmax = 0;
  for (int x = 2; x < n; ++x) {
    int y = x;
    int c = 0;
    while (y > 1) {
      c += 1;
      if ((y % 2) == 0)
        y = y / 2;
      else
        y = 3 * y + 1;
    }
    if (c > cmax) {
      cmax = c;
      xmax = x;
    }
  }
  return xmax;
}

#endif