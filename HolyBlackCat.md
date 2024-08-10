### `c++filt` и `llvm-cxxfilt`

Долго не мог понять, почему `c++filt` и `llvm-cxxfilt` не осиливают определенные имена. Думал, что они просто кривые, а оказывается имена типов без --types не обрабатываются.

```bash
$ llvm-cxxfilt-18 St17integral_constantIiLin1EE
St17integral_constantIiLin1EE
$ llvm-cxxfilt-18 --types St17integral_constantIiLin1EE
std::integral_constant<int, -1>
```