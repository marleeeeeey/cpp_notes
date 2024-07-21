#include <cassert>
#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

void AskToThrowException()
{
    std::cout << "Should I throw?" << std::endl;
    std::string line;
    while (line.length() == 0)
    {
        std::getline(std::cin, line);
    }
    if (line[0] == 'y')
    {
        std::cout << "Throwing exception" << std::endl;
        throw std::runtime_error("User decided to throw exception");
    }
    else
    {
        std::cout << "Not throwing exception" << std::endl;
    }
}

class A
{
    static size_t counter_;
    static size_t incrementOnlyCounter_;
    size_t objectNumber_ = incrementOnlyCounter_++;
public:
    A()
    {
        std::cout << "A ctor " << this << std::endl;
        counter_++;
    }
    ~A()
    {
        std::cout << "A destructor " << this << std::endl;
        counter_--;
    }
    A([[maybe_unused]] const A& other)
    {
        std::cout << "A copy ctor " << this << std::endl;
        counter_++;
    }
    A([[maybe_unused]] A&& other)
    {
        std::cout << "A move ctor " << this << std::endl;
        counter_++;
    }
    A& operator=([[maybe_unused]] const A& other)
    {
        std::cout << "A copy assigment from=" << &other << " to=" << this << std::endl;
        return *this;
    }
    A& operator=([[maybe_unused]] A&& other)
    {
        std::cout << "A move assigment from=" << &other << " to=" << this << std::endl;
        return *this;
    }
public: // Helpers
    static size_t counter() { return counter_; }
    size_t objectNumber() const { return objectNumber_; }
};

size_t A::counter_ = 0;
size_t A::incrementOnlyCounter_ = 0;

std::ostream& operator<<(std::ostream& os, const A& val)
{
    return os << val.objectNumber() << "(" << &val << ")";
}

template <typename T>
class vector
{
    char* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
public:
    ~vector()
    {
        for (size_t i = 0; i < size; ++i)
        {
            placementDestroy(i);
        }
        delete[] data;
    }

    void push_back(const T& value)
    {
        if (!data)
        {
            assert(size == 0);
            assert(capacity == 0);
            capacity = 1;
            data = new char[sizeof(T) * capacity];
        }

        assert(data);
        assert(size <= capacity);
        if (size == capacity)
        {
            capacity *= 2;
            char* newdata = new char[sizeof(T) * capacity];
            std::memcpy(newdata, data, sizeof(T) * size);
            delete[] data;
            data = newdata;
        }

        placementConstruct(size, value);
        size++;
    }

    void pop_back()
    {
        if (size == 0)
        {
            throw std::logic_error("Vector is empty");
        }
        placementDestroy(size - 1);
        size--;
    }
    T& operator[](size_t index) { return const_cast<T&>(get(index)); }
    const T& operator[](size_t index) const { return get(index); }

    T& back() { return operator[](size - 1); }
    const T& back() const { return operator[](size - 1); }
public: // **************************  DEBUG ONLY **************************
    std::string dumpToString() const
    {
        std::ostringstream oss;
        oss << "size=" << size << " | capacity=" << capacity << " | data:";
        for (size_t i = 0; i < size; ++i)
        {
            oss << " " << get(i);
        }
        return oss.str();
    }

    std::vector<T> dumpToStdVector() const
    {
        std::vector<T> result;
        for (size_t i = 0; i < size; ++i)
        {
            result.push_back(get(i));
        }
        return result;
    }
private: // ************************** HELPERS **************************
    const T& get(size_t index) const
    {
        if (index >= size)
        {
            throw std::logic_error("Index out of range");
        }

        char* charPtr = data + (index) * sizeof(T);
        T* objPtr = reinterpret_cast<T*>(charPtr);
        return *objPtr;
    }

    void placementDestroy(size_t index)
    {
        if (index >= size)
        {
            throw std::logic_error("Index out of range");
        }
        (*this)[index].~T();
    }

    template <typename E>
    void placementConstruct(size_t pos, E&& element)
    {
        assert(pos == size);
        new (data + sizeof(T) * size) T(std::forward<E>(element));
    }
};

int main()
try
{
    {
        vector<int> vec;
        assert(vec.dumpToStdVector() == std::vector<int>({}));
        vec.push_back(10);
        assert(vec.dumpToStdVector() == std::vector<int>({10}));
        assert(vec.back() == 10);
        vec.push_back(100);
        assert(vec.back() == 100);
        vec.push_back(200);
        assert(vec.dumpToStdVector() == std::vector<int>({10, 100, 200}));
        vec.pop_back();
        assert(vec.back() == 100);

        vector<A> veca;
        veca.push_back(A());
        // veca.push_back(A());
        // veca.push_back(A());
        // veca.push_back(A());
        std::cout << veca.dumpToString() << std::endl;
    }
    std::cout << "counter=" << A::counter() << std::endl;
    assert(A::counter() == 0);
    std::cout << "test sucsessfull" << std::endl;
}
catch (const std::exception& e)
{
    std::cout << "Caught an exception: " << e.what() << std::endl;
}
catch (...)
{
    std::cout << "Caught an unknown exception" << std::endl;
}