# Sergey Slotin - CPU Cache and Memory Latency

- [ABOUT AUTHOR](#about-author)
- [Pointer Chasing Pattern (шаблон следования по указателям) - измерения латентности доступа к памяти](#pointer-chasing-pattern-шаблон-следования-по-указателям---измерения-латентности-доступа-к-памяти)
- [Custom page size (пользовательский размер страницы) - управление размером страницы памяти](#custom-page-size-пользовательский-размер-страницы---управление-размером-страницы-памяти)

### ABOUT AUTHOR

- [Sergey Slotin](https://github.com/sslotin)
- Публикации:
  - https://ru.algorithmica.org/cs/
  - https://en.algorithmica.org/hpc/
- Видео конференции
  - https://youtu.be/Lrjjqc1bRHo
- GitHub:
  - https://github.com/sslotin/amh-code/tree/main/cpu-cache
- Contacts:
  - @bydlokoder
  - @sergey_slotin
  - me@sereja.me

### Pointer Chasing Pattern (шаблон следования по указателям) - измерения латентности доступа к памяти

- **Pointer Chasing Pattern** (шаблон следования по указателям) используется для измерения латентности доступа к памяти.
- Этот шаблон основан на случайной перестановке и обходе указателей в массиве, что затрудняет процессору предсказание последовательности чтений. Давайте рассмотрим, как это работает:

```cpp
int p[N], q[N];

// 1. Генерация случайной перестановки
// Здесь массив `p` заполняется числами от 0 до N-1, а затем они случайным образом перемешиваются. Это создает случайную перестановку элементов массива `p`.
std::iota(p, p + N, 0);
std::random_shuffle(p, p + N);

// 2. Создание полного цикла
// В этом цикле создается полный цикл, который охватывает все элементы массива `p`.
// Здесь переменная `k` указывает на следующий элемент в массиве.
// По сути, программа перемещается по случайной цепочке указателей в массиве.
// Эта цепочка представляет собой цикл, который посещает каждый элемент ровно один раз.
// Цель этого цикла — зафиксировать точку начала обхода.
int k = p[p[1]];
for (int i = 0; i < N; i++)
    k = p[k];

// 3. Основной цикл для измерения латентности. Cледование по указателям
// Здесь программа начинает с любого элемента и продолжает перемещаться по массиву, следуя указателям (индексам).
// Этот процесс продолжается до тех пор, пока программа не сделает полный оборот по массиву.
// Поскольку порядок следования полностью зависит от случайной перестановки, процессору трудно предсказать последовательность чтений, что делает измерение латентности более точным.
for (int i = 0; i < k; i++)
    k = p[k];
```

### Custom page size (пользовательский размер страницы) - управление размером страницы памяти

- Увеличение размера страницы памяти — это один из способов оптимизации производительности программ, особенно тех, которые интенсивно работают с памятью. Правильная настройка этого параметра может значительно сократить задержки доступа к памяти и улучшить общую производительность системы.
- https://youtu.be/Lrjjqc1bRHo
- На слайде рассматривается возможность увеличения размера страницы памяти, которая выделяется операционной системой для программы.
- График показывает, что с увеличением размера страницы задержки уменьшаются, что подтверждает выгоду от использования больших страниц для определенных типов задач.
- По умолчанию размер страницы составляет 4 КБ, но в определенных ситуациях, особенно на серверных системах, можно увеличить размер страницы до 2 МБ или даже 1 ГБ.

**Зачем это нужно:**

1. **Улучшение производительности:**
   - Увеличение размера страницы позволяет уменьшить количество TLB (Translation Lookaside Buffer) пропусков.
   - TLB - это кэш, используемый для ускорения преобразования виртуальных адресов в физические.
   - При большем размере страницы требуется меньше записей в TLB, что позволяет более эффективно использовать кэш и ускоряет доступ к памяти.

2. **Снижение затрат на управление:**
   - При меньшем размере страниц системе приходится управлять большим количеством страниц, что добавляет накладные расходы.
   - Увеличение размера страниц снижает эти расходы.

**Использование увеличенного размера страниц:**

- В Linux можно использовать `madvise` или `transparent huge pages`, чтобы подсказать ОС использовать большие страницы (например, 2 МБ).
- В Windows можно использовать `VirtualAlloc` с флагом `MEM_LARGE_PAGES` для выделения страниц большего размера.