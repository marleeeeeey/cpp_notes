#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <sys/stat.h>

namespace c_api
{

using A = int;
using B = std::string;

namespace details
{
std::map<A, int> ref_count_a;
std::map<B, int> ref_count_b;
} // namespace details

void debug_msg(const std::string& msg)
{
    std::cout << msg << std::endl;
}

A createA()
{
    static int id = 2000;
    details::ref_count_a[id] = 1;
    debug_msg("A create " + std::to_string(id) + " (" + std::to_string(details::ref_count_a[id]) + ")");
    return id++;
}

int releaseA(A a)
{
    if (--details::ref_count_a[a] == 0)
    {
        details::ref_count_a.erase(a);
        debug_msg("A release " + std::to_string(a) + " erased");
        return 0;
    }
    else
    {
        debug_msg("A release " + std::to_string(a) + " (" + std::to_string(details::ref_count_a[a]) + ")");
    }
    return details::ref_count_a[a];
}

int retainA(A a)
{
    details::ref_count_a[a]++;
    debug_msg("A retain " + std::to_string(a) + " (" + std::to_string(details::ref_count_a[a]) + ")");
    return details::ref_count_a[a];
}

bool aliveA(A a)
{
    return details::ref_count_a.size() > 0;
}

B createB()
{
    static int id = 1000;
    details::ref_count_b[std::to_string(id)] = 1;
    debug_msg("B create " + std::to_string(id) + " (" + std::to_string(details::ref_count_b[std::to_string(id)]) + ")");
    return std::to_string(id++);
}

int releaseB(B b)
{
    if (--details::ref_count_b[b] == 0)
    {
        details::ref_count_b.erase(b);
        debug_msg("B release " + b + " erased");
        return 0;
    }
    else
    {
        debug_msg("B release " + b + " (" + std::to_string(details::ref_count_b[b]) + ")");
    }
    return details::ref_count_b[b];
}

int retainB(B b)
{
    details::ref_count_b[b]++;
    debug_msg("B retain " + b + " (" + std::to_string(details::ref_count_b[b]) + ")");
    return details::ref_count_b[b];
}

bool aliveB(B b)
{
    return details::ref_count_b.size() > 0;
}

void c_api_test()
{
    assert(details::ref_count_a.empty());
    auto a = createA();
    assert(retainA(a) == 2);
    assert(releaseA(a) == 1);
    assert(releaseA(a) == 0);
    assert(details::ref_count_a.empty());

    assert(details::ref_count_b.empty());
    auto b = createB();
    assert(retainB(b) == 2);
    assert(releaseB(b) == 1);
    assert(releaseB(b) == 0);
    assert(details::ref_count_b.empty());
}

} // namespace c_api

namespace details
{

template <typename T>
struct ReferenceHandler
{};

template <>
struct ReferenceHandler<c_api::A>
{
    static int retain(c_api::A a) { return c_api::retainA(a); }
    static int release(c_api::A a) { return c_api::releaseA(a); }
    static int alive(c_api::A a) { return c_api::aliveA(a); }
};

template <>
struct ReferenceHandler<c_api::B>
{
    static int retain(c_api::B b) { return c_api::retainB(b); }
    static int release(c_api::B b) { return c_api::releaseB(b); }
    static int alive(c_api::B b) { return c_api::aliveB(b); }
};

template <typename CApiType>
class Wrapper
{
    CApiType obj_;
public:
    Wrapper(CApiType obj) : obj_(obj) {}
    ~Wrapper()
    {
        if (ReferenceHandler<CApiType>::alive(obj_))
            release();
    }

    Wrapper(const Wrapper& other)
    {
        obj_ = other.obj_;
        retain();
    }

    Wrapper& operator=(const Wrapper& other)
    {
        if (this != &other)
        {
            release();
            obj_ = other.obj_;
            retain();
        }
        return *this;
    }

    // TODO: here may be the move semantic. But for my classes it doesn't make sence.

    const CApiType& operator()() const { return obj_; }
    CApiType& operator()() { return obj_; }
    CApiType get() { return obj_; }
private:
    int release() const { return ReferenceHandler<CApiType>::release(obj_); }
    int retain() const { return ReferenceHandler<CApiType>::retain(obj_); }
};

} // namespace details

class Device : public details::Wrapper<c_api::A>
{
    // Device is a wrapper. This means we can create base class with the same type as Device.
    Device(const Device& other) : details::Wrapper<c_api::A>(other) {}

    Device& operator=(const Device& other)
    {
        details::Wrapper<c_api::A>::operator=(other);
        return *this;
    }
};

int main()
{
    c_api::c_api_test();
    for (int i = 0; i < 1; ++i)
    {
        details::Wrapper objectA1(c_api::createA());
        details::Wrapper objectA2(c_api::createA());
        auto objectA1copy1 = objectA1;
        auto objectA1copy2 = objectA1;
        auto objectA1copy3 = objectA1;
        auto objectA1copy4 = objectA1;
        std::cout << "Copy assigment: objectA1copy4 = objectA2" << std::endl;
        objectA1copy4 = objectA2;
        details::Wrapper<std::string> object2(c_api::createB());
        auto object2Copy = object2;
    }
    assert(c_api::details::ref_count_a.empty());
    assert(c_api::details::ref_count_b.empty());
}