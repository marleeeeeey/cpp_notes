#include <iomanip>
#include <iostream>
#include <unordered_map>

int main()
{
    std::unordered_map<int, int> m;
    m.reserve(10); // Резервируем 10 элементов (бакетов).
    m.max_load_factor(10.0); // Разрешеаем коллизии.
    for (int i = 0; i < 100; ++i) // Ожидаем каждый бакет где то по 10 элементов.
        m.insert(std::make_pair(i, i));

    for (auto it = m.begin(); it != m.end(); ++it)
        std::cout << it->first << " ";
    std::cout << std::endl;

    for (size_t i = 0; i < m.bucket_count(); ++i)
    {
        std::cout << "Bucket #" << std::setw(2) << i << ": ";
        for (auto it = m.begin(i); it != m.end(i); ++it)
            std::cout << it->first << " ";
        std::cout << std::endl;
    }
}