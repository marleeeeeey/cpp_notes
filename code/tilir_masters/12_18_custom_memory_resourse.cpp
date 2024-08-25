#include <algorithm>
#include <iostream>
#include <memory_resource>
#include <random>
#include <string>
#include <vector>


#include "gtest/gtest.h"

namespace
{

class test_resource : public std::pmr::memory_resource
{
    struct allocation_rec
    {
        void* ptr_;
        size_t nbytes_, nalign_;
    };

    std::pmr::memory_resource* parent_;
    std::pmr::vector<allocation_rec> blocks_;
public:
    explicit test_resource(std::pmr::memory_resource* parent = std::pmr::get_default_resource())
      : parent_(parent), blocks_(parent)
    {}

    std::pmr::memory_resource* parent() const { return parent_; }

    ~test_resource()
    {
        std::cout << "leaked " << blocks_.size() << " blocks" << std::endl;
        for (auto&& b : blocks_)
        {
            std::cout << "\t ptr:" << b.ptr_ << std::endl;
            parent_->deallocate(b.ptr_, b.nbytes_, b.nalign_);
        }
    }
protected:
    void* do_allocate(size_t bytes, size_t alignment) override
    {
        void* ret = parent_->allocate(bytes, alignment);
        std::cout << "a: " << bytes << "\t to: " << ret << std::endl;
        blocks_.push_back(allocation_rec{ret, bytes, alignment});
        return ret;
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override
    {
        auto i = find_if(blocks_.begin(), blocks_.end(), [p](const allocation_rec& r) { return r.ptr_ == p; });
        if (i == blocks_.end())
            throw std::invalid_argument("deallocate: Invalid pointer");
        blocks_.erase(i);
        parent_->deallocate(p, bytes, alignment);
    }

    bool do_is_equal(const memory_resource& other) const noexcept override { return this == &other; }
};

auto mtgen()
{
    static std::random_device rd;
    static std::mt19937 g(rd());
    return g;
}

} // namespace

TEST(allocs, memres)
{
    std::cout << "--- pmr::vector + test resource test ---" << std::endl;
    test_resource talloc;

    // allocate smth to leak
    (void)talloc.allocate(10, 4);

    double start = 0.0;
    std::pmr::vector<double> v1(&talloc);
    std::generate_n(back_inserter(v1), 100, [start]() mutable { return (start += 1.1); });

    std::pmr::vector<double> v2(&talloc);
    v2.assign(v1.begin(), v1.end());
    std::shuffle(v2.begin(), v2.end(), mtgen());

    std::cout << "v1[42] = " << v1[42] << " v2[42] = " << v2[42] << std::endl;
    std::cout << "---" << std::endl;
}
