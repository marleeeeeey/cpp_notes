#include <cassert>
#include <cstddef>
#include <cstring>
#include <exception>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// Script options
#define VERBOSE_CLASS_A 1

// TODO LIST
// 1. Fix differences berween std::vector and MyVector in runtime

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
std::string ConvertToString(const VectorType& object)
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
std::vector<typename VectorType::value_type> ConvertToStdVector(const VectorType& object)
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
            std::cout << "A#" << objectNumber_ << " ctor " << this << std::endl;
        objectsCounter_++;
    }
    ~A()
    {
        if (verbose_)
            std::cout << "A#" << objectNumber_ << " destructor " << this << std::endl;
        objectsCounter_--;
    }
    A([[maybe_unused]] const A& other)
    {
        if (verbose_)
            std::cout << "A#" << objectNumber_ << " copy ctor " << this << std::endl;
        objectsCounter_++;
    }
    A([[maybe_unused]] A&& other)
    {
        if (verbose_)
            std::cout << "A#" << objectNumber_ << " move ctor " << this << std::endl;
        objectsCounter_++;
    }
    A& operator=([[maybe_unused]] const A& other)
    {
        if (verbose_)
            std::cout << "A#" << objectNumber_ << " copy assigment from=" << &other << " to=" << this << std::endl;
        return *this;
    }
    A& operator=([[maybe_unused]] A&& other)
    {
        if (verbose_)
            std::cout << "A#" << objectNumber_ << " move assigment from=" << &other << " to=" << this << std::endl;
        return *this;
    }
public: // Helpers
    static size_t ObjectsCounter() { return objectsCounter_; }
    static void ResetObjectsCounter() { A::objectsCounter_ = 0; }
    size_t ObjectNumber() const { return objectNumber_; }
};

size_t A::objectsCounter_ = 0;
size_t A::incrementOnlyCounter_ = 0;

std::ostream& operator<<(std::ostream& os, const A& val)
{
    return os << val.ObjectNumber() << "(" << &val << ")";
}

template <typename T>
class MyVector
{
private: // ************************** STATE **************************
    char* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
public: // ************************** TEMPLATE STUFF **************************
    using value_type = T;
public: // ************************ RULE OF FIVE IMPL ************************
    MyVector() {}

    MyVector(const MyVector<T>& other)
    {
        data_ = new char[sizeof(T) * other.capacity_]; // May throw exception.
        capacity_ = other.capacity_;

        // --------------------------------------------------------------------------------------
        // This way of copying is not correct, because it doesn't call the copy constructor of T.
        // The memory is copied, but the object T may have side effects in its constructor.
        // std::memcpy(data_, other.data_, sizeof(T) * other.size_);
        // --------------------------------------------------------------------------------------

        try
        {
            for (size_t i = 0; i < other.size_; ++i)
            {
                PlacementConstruct(i, other[i]); // May throw exception.
                size_++;
            }
        }
        catch (...)
        {
            DestroyAllElementsAndFree();
            throw;
        }
    }

    MyVector(MyVector<T>&& other) noexcept
      : data_(std::exchange(other.data_, nullptr)), size_(std::exchange(size_, 0)),
        capacity_(std::exchange(capacity_, 0))
    {}

    MyVector& operator=(const MyVector<T>& other)
    {
        MyVector<T> temp(other); // May throw exception.
        // --- Kalb's line here ---
        this->swap(temp);
        return *this;
    }

    MyVector& operator=(MyVector<T>&& other) noexcept
    {
        MyVector<T> temp(std::move(other));
        this->swap(temp);
        return *this;
    }

    ~MyVector() { DestroyAllElementsAndFree(); }
public: // ******************* STD VECTOR LIKE INTERFACE IMPL *******************
    template <typename Args>
    void push_back(Args&& value)
    {
        char* oldData = nullptr;

        if (!data_)
        {
            assert(size_ == 0);
            assert(capacity_ == 0);
            size_t newCapacity = 1;
            data_ = new char[sizeof(T) * newCapacity];
            // --- Kalb's line here ---
            capacity_ = newCapacity;
        }

        assert(data_);
        assert(size_ <= capacity_);
        if (size_ == capacity_)
        {
            size_t newCapacity = capacity_ * 2;
            char* newdata = new char[sizeof(T) * newCapacity];
            // --- Kalb's line here ---
            capacity_ = newCapacity;
            std::memcpy(newdata, data_, sizeof(T) * size_);
            oldData = data_;
            data_ = newdata;
        }

        try
        {
            // Remove old data after element is created to support cases like this:
            // `std::vector<int> foo = {1,2,3,4}; foo.push_back(foo[2]);`
            PlacementConstruct(size_, std::forward<Args>(value));
            size_++;
        }
        catch (...)
        {
            delete[] oldData;
            throw;
        }

        delete[] oldData;
        oldData = nullptr;

        assert(size_ <= capacity_);
    }

    void pop_back()
    {
        if (size_ == 0)
        {
            throw std::logic_error("Vector is empty");
        }
        PlacementDestroy(size_ - 1);
        size_--;
    }

    T& operator[](size_t index) { return const_cast<T&>(Get(index)); }
    const T& operator[](size_t index) const { return Get(index); }

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
    const T& Get(size_t index) const
    {
        if (index >= size_)
        {
            throw std::logic_error("Index out of range");
        }

        char* charPtr = data_ + (index) * sizeof(T);
        T* objPtr = reinterpret_cast<T*>(charPtr);
        return *objPtr;
    }

    void DestroyAllElementsAndFree() noexcept
    {
        for (size_t i = 0; i < size_; ++i)
            PlacementDestroy(i);
        delete[] data_;
    }

    void PlacementDestroy(size_t index) noexcept
    {
        assert(index < size_);
        (*this)[index].~T();
    }

    template <typename E>
    void PlacementConstruct(size_t pos, E&& element)
    {
        assert(pos == size_);
        new (data_ + sizeof(T) * size_) T(std::forward<E>(element));
    }
};

template <typename T>
void Test()
{
    A::ResetObjectsCounter();
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
        std::cout << ConvertToString(vecA) << std::endl;

        T vecB(vecA);
        std::cout << ConvertToString(vecB) << std::endl;
        assert(vecB.size() == vecA.size());

        vecA.push_back(vecA[0]);
    }
    std::cout << "counter=" << A::ObjectsCounter() << std::endl;
    assert(A::ObjectsCounter() == 0);
    std::cout << "test sucsessfull" << std::endl;
}

int main()
try
{
    std::cout << "\nStarting tests with std::vector" << std::endl;
    Test<std::vector<A>>();
    std::cout << "\nStarting tests with MyVector" << std::endl;
    Test<MyVector<A>>();
}
catch (const std::exception& e)
{
    std::cout << "Caught an exception: " << e.what() << std::endl;
}
catch (...)
{
    std::cout << "Caught an unknown exception" << std::endl;
}