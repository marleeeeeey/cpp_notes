#include <cassert>
#include <cmath>
#include <iostream>

// clang-format off

template<typename... Args>
auto sum_all(Args... args)
{
    return (args + ...);
}


template<typename... Args>
auto print_all(Args... args)
{
    //  init   op ... op pack
    (std::cout << ... << args) << std::endl;
}


// *****************************************

// Шаблон для перемещения по дереву, указывая левый или правый указатель.
template <typename T>
struct Node
{
    T data;
    Node* left;
    Node* right;
};

template <typename Node, typename First>
Node* get_tree(Node* node, First first)
{
    return node->*first;
}

template <typename Node, typename First, typename... Rest>
Node* get_tree(Node* node, First first, Rest... rest)
{
    return get_tree(node->*first, rest...);
}

// *****************************************

// Метод, который печатает произвольное число аргументов через пробел

// print_all_space(10, 20, 30, 40); => 10_20_30_40
template <typename Arg, typename... Args>
void print_all_space(Arg&& first, Args&&... args)
{
    std::cout << first;

    // RULE: ( pack op ... ) -> pack1 op (pack2 op (... op packN))

    // (             pack                 op  ... )
       (     (std::cout << "_" << args)    ,  ... );

    // => std::cout << "_" << x , ( std::cout << "_" << y , std::cout << "_" << z );

    std::cout << std::endl;
}

template <typename... Values>
auto sum(Values const&... values)
{
    return (0 + ... + values);
}

// clang-format on

Node<int>* createTree()
{
    // 0
    // 1     2
    // 3 4   5 6

    Node<int>* root = new Node<int>{0, nullptr, nullptr};

    root->left = new Node<int>{1, nullptr, nullptr};
    root->right = new Node<int>{2, nullptr, nullptr};
    root->left->left = new Node<int>{3, nullptr, nullptr};
    root->left->right = new Node<int>{4, nullptr, nullptr};
    root->right->left = new Node<int>{5, nullptr, nullptr};
    root->right->right = new Node<int>{6, nullptr, nullptr};

    return root;
}

int main()
{
    std::cout << sum_all(10, 20, 30) << std::endl;
    print_all(10, 20, 30, 40);
    print_all_space(10, "qwerqw", 30, 40);
    assert(sum(10, 20, 30) == 60);
    assert(sum() == 0);

    Node<int>* root = createTree();
    auto subTree = get_tree(root, &Node<int>::left, &Node<int>::right);
    assert(subTree->data == 4);
}