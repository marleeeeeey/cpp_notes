#include <cassert>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// Script options
#define REPLACE_MY_VECTOR_WITH_STD_VECTOR 1
#define VERBOSE_CLASS_A 0

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

template <typename VectorType>
std::string convertToString(const VectorType& object)
{
    std::ostringstream oss;
    oss << "size=" << object.size() << " | capacity=" << object.capacity() << " | data:";
    for (size_t i = 0; i < object.size(); ++i)
    {
        oss << " " << object[i];
    }
    return oss.str();
}

template <typename VectorType>
std::vector<typename VectorType::value_type> convertToStdVector(const VectorType& object)
{
    std::vector<typename VectorType::value_type> result;
    for (size_t i = 0; i < object.size(); ++i)
    {
        result.push_back(object[i]);
    }
    return result;
}

class A
{
    static const bool verbose_ = VERBOSE_CLASS_A;
    static size_t objectsCounter_;
    static size_t incrementOnlyCounter_;
    size_t objectNumber_ = incrementOnlyCounter_++;
public:
    A()
    {
        if (verbose_)
            std::cout << "A ctor " << this << std::endl;
        objectsCounter_++;
    }
    ~A()
    {
        if (verbose_)
            std::cout << "A destructor " << this << std::endl;
        objectsCounter_--;
    }
    A([[maybe_unused]] const A& other)
    {
        if (verbose_)
            std::cout << "A copy ctor " << this << std::endl;
        objectsCounter_++;
    }
    A([[maybe_unused]] A&& other)
    {
        if (verbose_)
            std::cout << "A move ctor " << this << std::endl;
        objectsCounter_++;
    }
    A& operator=([[maybe_unused]] const A& other)
    {
        if (verbose_)
            std::cout << "A copy assigment from=" << &other << " to=" << this << std::endl;
        return *this;
    }
    A& operator=([[maybe_unused]] A&& other)
    {
        if (verbose_)
            std::cout << "A move assigment from=" << &other << " to=" << this << std::endl;
        return *this;
    }
public: // Helpers
    static size_t objectsCounter() { return objectsCounter_; }
    static void resetObjectsCounter() { A::objectsCounter_ = 0; }
    size_t objectNumber() const { return objectNumber_; }
};

size_t A::objectsCounter_ = 0;
size_t A::incrementOnlyCounter_ = 0;

std::ostream& operator<<(std::ostream& os, const A& val)
{
    return os << val.objectNumber() << "(" << &val << ")";
}

template <typename T>
class MyVector
{
private: // ************************** STATE **************************
    char* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
public: //************************** TEMPLATE STUFF **************************
    using value_type = T;
public:
    MyVector() {}

    MyVector(const MyVector<T>& other)
    {
        data_ = new char[sizeof(T) * other.capacity_];
        // --- Kalb's line here ---
        std::memcpy(data_, other.data_, sizeof(T) * other.size_);
        capacity_ = other.capacity_;
        size_ = other.size_;
    }

    MyVector& operator=(const MyVector<T>& other)
    {
        MyVector<T> temp(other);
        // --- Kalb's line here ---
        this->swap(temp);
        return *this;
    }

    ~MyVector()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            placementDestroy(i);
        }
        delete[] data_;
    }

    void push_back(const T& value)
    {
        if (!data_)
        {
            assert(size_ == 0);
            assert(capacity_ == 0);
            size_t newCapacity = 1;
            data_ = new char[sizeof(T) * newCapacity];
            capacity_ = newCapacity;
        }

        assert(data_);
        assert(size_ <= capacity_);
        if (size_ == capacity_)
        {
            size_t newCapacity = capacity_ * 2;
            char* newdata = new char[sizeof(T) * newCapacity];
            capacity_ = newCapacity;
            std::memcpy(newdata, data_, sizeof(T) * size_);
            delete[] data_;
            data_ = newdata;
        }

        placementConstruct(size_, value);
        size_++;
        assert(size_ <= capacity_);
    }

    void pop_back()
    {
        if (size_ == 0)
        {
            throw std::logic_error("Vector is empty");
        }
        placementDestroy(size_ - 1);
        size_--;
    }
    T& operator[](size_t index) { return const_cast<T&>(get(index)); }
    const T& operator[](size_t index) const { return get(index); }

    T& back() { return operator[](size_ - 1); }
    const T& back() const { return operator[](size_ - 1); }

    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }

    void swap(const MyVector<T>& other) noexcept
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    friend void swap(const MyVector<T>& a, const MyVector<T>& b) noexcept { a.swap(b); }
private: // ************************** HELPERS **************************
    const T& get(size_t index) const
    {
        if (index >= size_)
        {
            throw std::logic_error("Index out of range");
        }

        char* charPtr = data_ + (index) * sizeof(T);
        T* objPtr = reinterpret_cast<T*>(charPtr);
        return *objPtr;
    }

    void placementDestroy(size_t index)
    {
        assert(index < size_);
        (*this)[index].~T();
    }

    template <typename E>
    void placementConstruct(size_t pos, E&& element)
    {
        assert(pos == size_);
        new (data_ + sizeof(T) * size_) T(std::forward<E>(element));

        std::vector<int> vec;
    }
};

template <typename T>
void test()
{
    A::resetObjectsCounter();
    {
        // T<int> vecInt;
        // assert(convertToStdVector(vecInt) == std::vector<int>({}));
        // vecInt.push_back(10);
        // assert(convertToStdVector(vecInt) == std::vector<int>({10}));
        // assert(vecInt.back() == 10);
        // vecInt.push_back(100);
        // assert(vecInt.back() == 100);
        // vecInt.push_back(200);
        // assert(convertToStdVector(vecInt) == std::vector<int>({10, 100, 200}));
        // vecInt.pop_back();
        // assert(vecInt.back() == 100);

        using Type = T::value_type;

        T vecA;
        vecA.push_back(Type());
        vecA.push_back(Type());
        vecA.push_back(Type());
        vecA.push_back(Type());
        std::cout << convertToString(vecA) << std::endl;

        T vecB(vecA);
        std::cout << convertToString(vecB) << std::endl;
        assert(vecB.size() == vecA.size());
    }
    std::cout << "counter=" << A::objectsCounter() << std::endl;
    assert(A::objectsCounter() == 0);
    std::cout << "test sucsessfull" << std::endl;
}

int main()
try
{
    std::cout << "\nStarting tests with std::vector" << std::endl;
    test<std::vector<A>>();
    std::cout << "\nStarting tests with MyVector" << std::endl;
    test<MyVector<A>>();
}
catch (const std::exception& e)
{
    std::cout << "Caught an exception: " << e.what() << std::endl;
}
catch (...)
{
    std::cout << "Caught an unknown exception" << std::endl;
}