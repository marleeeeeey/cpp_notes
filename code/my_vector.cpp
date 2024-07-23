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
#define OBJECTS_COUNTER 1
#define CLASS_A_VERBOSE 1
#define CLASS_A_VERBOSE_SHOW_ADDRS 0
#define CLASS_A_THROW_EXCEPTION_ON_CONSTRUCT_EVERY_X_OBJECT 40
#define VERBOSE_CLASS_MY_VECTOR 0

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
    static const bool verbose_ = CLASS_A_VERBOSE;
    static size_t objectsCounter_;
    static size_t incrementOnlyCounter_;
    size_t objectNumber_ = incrementOnlyCounter_++;
    static const size_t exceptionOnConstructEveryXElement = CLASS_A_THROW_EXCEPTION_ON_CONSTRUCT_EVERY_X_OBJECT;
public:
    A()
    {
        PrintToConsole("default constructor");
        objectsCounter_++;
    }
    ~A()
    {
        PrintToConsole("destructor");
        objectsCounter_--;
    }
    A([[maybe_unused]] const A& other)
    {
        PrintToConsole("copy constructor", &other);
        objectsCounter_++;
    }
    A& operator=([[maybe_unused]] const A& other)
    {
        PrintToConsole("copy assigment", &other);
        return *this;
    }
    A([[maybe_unused]] A&& other) noexcept(true)
    {
        PrintToConsole("move constructor", &other);
        objectsCounter_++;
    }
    A& operator=([[maybe_unused]] A&& other) noexcept(true)
    {
        PrintToConsole("move assigment", &other);
        return *this;
    }
public: // Helpers
    static size_t ObjectsCounter() { return objectsCounter_; }
    static void ResetCounters()
    {
        A::objectsCounter_ = 0;
        A::incrementOnlyCounter_ = 0;
    }
    size_t ObjectNumber() const { return objectNumber_; }
    void PrintToConsole(const std::string& methodName, const A* const other = nullptr) const
    {
        if (verbose_)
        {
            std::cout << "A#" << ObjectNumber() << " " << methodName;
            if (other)
                std::cout << " from A#" << other->ObjectNumber();
            std::cout << std::endl;
        }

        if (exceptionOnConstructEveryXElement && objectNumber_)
        {
            if (objectNumber_ % exceptionOnConstructEveryXElement == 0)
            {
                std::ostringstream oss;
                oss << "Throwing exception on construct of A#" << objectNumber_;
                std::cout << oss.str() << std::endl;
                throw std::runtime_error(oss.str());
            }
        }
    }
};

size_t A::objectsCounter_ = 0;
size_t A::incrementOnlyCounter_ = 0;

std::ostream& operator<<(std::ostream& os, const A& val)
{
    return os << "A#" << val.ObjectNumber()
#if CLASS_A_VERBOSE_SHOW_ADDRS
              << "(" << &val << ")"
#endif
        ;
}

template <typename T>
class MyVector
{
private: // ****************************** STATE ******************************
    char* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
public: // ************************** TEMPLATE STUFF **************************
    using value_type = T;
public: // *************************** CONSTRUCTORS ***************************
    MyVector() {}
    explicit MyVector(size_t capacity)
    {
        data_ = new char[sizeof(T) * capacity]; // May throw exception.
        size_ = 0;
        capacity_ = capacity;
    }
public: // ************************ RULE OF FIVE IMPL ************************
    MyVector(const MyVector<T>& other)
    {
        MyVector tmp(other.size_); // May throw exception.

        // --------------------------------------------------------------------------------------
        // This way of copying is not correct, because it doesn't call the copy constructor of T.
        // The memory is copied, but the object T may have side effects in its constructor.
        // std::memcpy(data_, other.data_, sizeof(T) * other.size_);
        // --------------------------------------------------------------------------------------

        for (size_t i = 0; i < other.size_; ++i)
            tmp.PlacementPush(other[i]); // May throw exception.
        // --- Kalb's line here ---
        swap(tmp);
    }

    MyVector(MyVector<T>&& other) noexcept
      : data_(std::exchange(other.data_, nullptr)), size_(std::exchange(size_, 0)),
        capacity_(std::exchange(capacity_, 0))
    {}

    MyVector& operator=(const MyVector<T>& other)
    {
        MyVector<T> temp(other); // May throw exception.
        // --- Kalb's line here ---
        swap(temp);
        return *this;
    }

    MyVector& operator=(MyVector<T>&& other) noexcept
    {
        MyVector<T> temp(std::move(other));
        swap(temp);
        return *this;
    }

    ~MyVector()
    {
        for (size_t i = size_; i > 0; --i)
            PlacementDestroy(i - 1);
        delete[] data_;
    }
public: // ******************* STD VECTOR LIKE INTERFACE IMPL *******************
    template <typename Args>
    void push_back(Args&& value)
    {
        // Commit/rollback strategy
        // Remove old data after element is created to support cases like this:
        // `std::vector<int> foo = {1,2,3,4}; foo.push_back(foo[2]);`
        if (size_ == capacity_)
        {
            MyVector<T> tmp(capacity_ * 2 + 1);
            for (size_t i = 0; i < size_; ++i)
            {
                // TODO: this line may use move if std::is_nothrow_move_constructible<Arg>}
                tmp.PlacementPush((*this)[i]);
            }
            tmp.PlacementPush(std::forward<Args>(value));
            // --- Kalb's line here ---
            swap(tmp);
        }
        else // size < capacity
        {
            PlacementPush(std::forward<Args>(value));
            // --- Kalb's line here ---
        }
    }

    void pop_back()
    {
        if (size_ == 0)
            throw std::logic_error("Vector is empty");

        PlacementDestroy(size_ - 1);
        size_--;
    }

    T& operator[](size_t index) { return const_cast<T&>(Get(index)); }
    const T& operator[](size_t index) const { return Get(index); }

    T& back() { return operator[](size_ - 1); }
    const T& back() const { return operator[](size_ - 1); }

    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }

    void swap(MyVector<T>& other) noexcept
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    friend void swap(MyVector<T>& a, MyVector<T>& b) noexcept { a.swap(b); }
private: // ************************** HELPERS **************************
    const T& Get(size_t index) const
    {
        if (index >= size_)
            throw std::logic_error("Index out of range");

        char* charPtr = data_ + (index) * sizeof(T);
        T* objPtr = reinterpret_cast<T*>(charPtr);
        return *objPtr;
    }

    void PlacementDestroy(size_t index) noexcept
    {
        assert(index < size_);
        (*this)[index].~T();
    }

    template <typename E>
    void PlacementPush(E&& element)
    {
        new (data_ + sizeof(T) * size_) T(std::forward<E>(element));
        size_++;
    }
};

template <typename T>
void Test()
{
    using Type = T::value_type;

    T vecA;
    for (size_t i = 0; i < OBJECTS_COUNTER; ++i)
    {
        vecA.push_back(Type());
    }
    std::cout << "Test: " << ConvertToString(vecA) << std::endl;

    T vecB(vecA);
    std::cout << "Test: " << ConvertToString(vecB) << std::endl;
    assert(vecB.size() == vecA.size());

    vecA.push_back(vecA[0]);
}

int main()
try
{
    try
    {
        A::ResetCounters();
        std::cout << "\nStarting tests with std::vector" << std::endl;
        Test<std::vector<A>>();
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught an exception: " << e.what() << std::endl;
    }

    std::cout << "counter=" << A::ObjectsCounter() << std::endl;
    assert(A::ObjectsCounter() == 0);
    std::cout << "test sucsessfull" << std::endl;

    try
    {
        A::ResetCounters();
        std::cout << "\nStarting tests with MyVector" << std::endl;
        Test<MyVector<A>>();
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught an exception: " << e.what() << std::endl;
    }

    std::cout << "counter=" << A::ObjectsCounter() << std::endl;
    assert(A::ObjectsCounter() == 0);
    std::cout << "test sucsessfull" << std::endl;
}
catch (...)
{
    std::cout << "Caught an unknown exception" << std::endl;
}