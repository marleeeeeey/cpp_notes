#include "gtest/gtest.h"
#include <functional>
#include <iostream>

// clang-format off


struct Leaf {};
struct Node; // fw declaration
using Tree = std::variant<Leaf, Node*>;
struct Node { Tree left, right; };

template<typename ... F> struct overloaded : F... { using F::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>; // deduction hint

int num_leaves(Tree const& tree)
{
    return std::visit(overloaded{
        [](Leaf const&) { return 1; },
        [](this auto const& self, Node* n)
        {
            return std::visit(self, n->left) +
                   std::visit(self, n->right);
        }
    }, tree);
}

TEST(deducing_this_and_variant_pattern, basics)
{

}