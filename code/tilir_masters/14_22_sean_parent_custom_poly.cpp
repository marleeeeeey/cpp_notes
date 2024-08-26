#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// clang-format off

template <typename T>
void draw(const T& x, std::ostream& out, size_t position)               // <=== OVERLOAD для любого типа, который умеет выводиться в поток

{
    out << std::string(position, ' ') << x << std::endl;
}

class myclass_t
{};

void draw(const myclass_t&, std::ostream& out, size_t position)         // <=== OVERLOAD для myclass_t
{
    out << std::string(position, ' ') << "myclass_t" << std::endl;
}

class object_t;
using document_t = std::vector<object_t>;

void draw(const document_t& x, std::ostream& out, size_t position);

// Идея Parent reversal
class object_t
{
    struct concept_t                                                // <=== Является деталью реализации object_t
    {
        virtual ~concept_t() = default;
        virtual std::unique_ptr<concept_t> copy_() const = 0;       // <=== Виртуальный конструктор копирования
        virtual void draw_(std::ostream&, size_t) const = 0;        // <=== Виртуальная функция draw_, которая переопределяется в потомках
    };

    template <typename T>
    struct model final : concept_t                                  // <=== Модель будет создаваться в шаблонном конструкторе.
    {                                                               //      Наследует чисто асбтрактный класс concept_t.
        T data_;
        model(T x) : data_(std::move(x)) {}

        std::unique_ptr<concept_t> copy_() const override           // <=== Умеет делать copy
        { return std::make_unique<model>(*this); }

        void draw_(std::ostream& out, size_t position) const override   // <=== Умеет делать draw
        { ::draw(data_, out, position); }                               // <=== ДЕЛЕГИРОВАНИЕ К ПЕРЕГРУЗКЕ!!!
    };

    std::unique_ptr<concept_t> self_;                               // <=== Может хранить объект любого типа.
public:                                                             //      CRTP наоборот - шаблонный класс наследуем от нешаблонного, чтобы унифицировать type erasure.
    template <typename T>
    object_t(T x) : self_(std::make_unique<model<T>>(std::move(x)))
    {}

    // copy ctor, move ctor and assignment
public:
    object_t(const object_t& x) : self_(x.self_->copy_()) {}
    object_t(object_t&& x) noexcept = default;
    object_t& operator=(object_t x) noexcept
    {
        self_ = std::move(x.self_);
        return *this;
    }
public:
    friend void draw(const object_t& x, std::ostream& out, size_t position)     // <=== OVERLOAD для самого object_t
    { x.self_->draw_(out, position); }
};

void draw(const document_t& x, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << "<document>" << std::endl;
    for (const auto& e : x)
        draw(e, out, position + 2);
    out << std::string(position, ' ') << "</document>" << std::endl;
}

int main()
{
    document_t document;
    document.emplace_back(0);
    document.emplace_back(std::string("Hello"));
    document.emplace_back(document);
    document.emplace_back(myclass_t{});
    document.emplace_back(50);
    draw(document, std::cout, 0);
}
