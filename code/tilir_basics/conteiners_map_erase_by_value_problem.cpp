#include <map>

#define BAD_CODE 0

int main()
{
    std::map<int, int> m = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};

#if BAD_CODE
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        if (it->second == 4)
            m.erase(it);
    }
#else
    for (auto it = m.begin(); it != m.end();)
    {
        if (it->second == 4)
            it = m.erase(it);
        else
            ++it;
    }
#endif
}