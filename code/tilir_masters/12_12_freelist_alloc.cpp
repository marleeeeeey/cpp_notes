#include <cstdio>
#include <limits>
#include <list>
#include <memory>
#include <vector>

#include "gtest/gtest.h"

template <typename T>
class freelist_alloc
{
    using storage_type = typename std::aligned_storage<sizeof(T), alignof(T)>::type;

    union node
    {
        node* next;
        storage_type storage;
    };

    node* list = nullptr;

    void clear() noexcept
    {
        printf("clear\n");
        auto p = list;
        while (p)
        {
            auto tmp = p;
            p = p->next;
            delete tmp;
        }
        list = nullptr;
    }
public:
    using value_type = T;
    using size_type = size_t;
    using propagate_on_container_move_assignment = std::true_type;

    freelist_alloc() = default;
    freelist_alloc(const freelist_alloc&) {}

    template <typename U>
    freelist_alloc(const freelist_alloc<U>&)
    {}

    freelist_alloc(freelist_alloc&& other) noexcept : list(other.list) { other.list = nullptr; }

    freelist_alloc& operator=(const freelist_alloc&) { return *this; }

    freelist_alloc& operator=(freelist_alloc&& other) noexcept
    {
        if (this == &other)
            return *this;
        clear();
        list = other.list;
        other.list = nullptr;
        return *this;
    }

    ~freelist_alloc()
    {
        printf("freelist dtor\n");
        clear();
    }

    T* allocate(size_type n)
    {
        printf("allocate %zu from: ", n);
        if (n == 1)
        {
            auto ptr = list;
            if (ptr)
            {
                printf("freelist\n");
                list = list->next;
            }
            else
            {
                printf("new node\n");
                ptr = new node;
            }
            return reinterpret_cast<T*>(ptr);
        }

        printf("new memory\n");
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* ptr, size_type n) noexcept
    {
        printf("deallocate %zu to: ", n);
        if (n == 1)
        {
            printf("freelist\n");
            auto node_ptr = reinterpret_cast<node*>(ptr);
            node_ptr->next = list;
            list = node_ptr;
        }
        else
        {
            printf("global delete\n");
            ::operator delete(ptr);
        }
    }
};

template <typename T, typename U>
bool operator==(const freelist_alloc<T>&, const freelist_alloc<U>&)
{
    return true;
}

template <typename T, typename U>
bool operator!=(const freelist_alloc<T>&, const freelist_alloc<U>&)
{
    return false;
}

TEST(allocs, freelist)
{
    std::vector<int, freelist_alloc<int>> v;
    for (int i = 0; i < 16; ++i)
        v.push_back(i);
    printf("---\n");
    std::list<int, freelist_alloc<int>> l(v.begin(), v.end());
    printf("---\n");
    l.remove(2);
    l.remove(6);
    l.insert(l.begin(), -1);
    l.insert(l.begin(), -3);
    l.insert(l.begin(), -5);
    printf("---\n");
}