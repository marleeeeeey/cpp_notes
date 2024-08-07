#include <vector>

// clang-format off

// Как бы вы написали remove функцию?
template <typename Iter, typename T>
Iter my_remove(Iter first, Iter last, const T& val)
{
    // Невозможно удалять элемент по итератору!
    // Поэтому remove собирает все не "удаленные" элементы в начале диапазона и
    // Возвращает итератор на конец этого уменьшенного диапазона.
    // Поэтому существует идиома erase(remove).
}

int main()
{
    std::vector<int> vec {1, 2, 3, 4, 5, 6, 7, 8, 9};
    my_remove(vec.begin(), vec.end(), 3);
}

// clang-format on