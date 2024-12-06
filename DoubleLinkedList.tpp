#ifndef HIDDER_DOUBLE
#define HIDDER_DOUBLE

#include <iostream>
#include <iterator>
#include <cassert>
#include <utility>

template <typename Item>
class double_linked_list 
{
public:
    using value_type = Item;
    using size_type = size_t;
    using dirrefernce_type = ptrdiff_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = value_type &;

private:
    struct node {
        node* next;
        node* prev;
        value_type data;
        node (value_type item) 
            : next{nullptr}, prev{nullptr}, data{item}
        {
        }
    };

public:
    class const_iterator
    {
    private:
        friend class double_linked_list;
    
    public:
        explicit const_iterator(const node* ptr) noexcept
                    : m_current {ptr}
        {
        }
    
    public:
        using value_type = double_linked_list::value_type;
        using dirrefernce_type = double_linked_list::dirrefernce_type;
        using pointer = double_linked_list::pointer;
        using reference = double_linked_list::reference;
        using iterator_category = std::bidirectional_iterator_tag;

        const_reference operator*() const noexcept {
            assert(m_current != nullptr);
            return m_current->data;
        }

        const_iterator& operator++() noexcept {
            assert(m_current != nullptr);
            m_current = m_current->next;
            return *this;
        }

        const_iterator& operator--() noexcept {
            assert(m_current != nullptr);
            m_current = m_current->prev;
            return *this;
        }

        const_iterator operator++(int) noexcept {
            assert(m_current != nullptr);
            auto copy = *this;
            m_current = m_current->next;
            return copy;
        }

        const_iterator operator--(int) noexcept {
            assert(m_current != nullptr);
            auto copy = *this;
            m_current = m_current->prev;
            return copy;
        }

        bool operator==(const_iterator other) const noexcept {
            return m_current == other.m_current;
        }

        bool operator!=(const_iterator other) const noexcept {
            return !(*this == other);
        }

    protected:
        const node* Get() const noexcept {
            return m_current;
        }

    protected:
        const node* m_current;
    };

    class iterator : public const_iterator 
    {
    private:
        friend class double_linked_list;
    
    public:
        explicit iterator(node* ptr) noexcept
                    : const_iterator(ptr)
        {
        }
    
    public:
        using value_type = double_linked_list::value_type;
        using dirrefernce_type = double_linked_list::dirrefernce_type;
        using pointer = double_linked_list::pointer;
        using reference = double_linked_list::reference;
        using iterator_category = std::bidirectional_iterator_tag;

        reference operator*() const noexcept {
            return const_cast<reference>(const_iterator::operator*());
        }

        iterator& operator++() noexcept {
            const_iterator::operator++();
            return *this;
        }

        iterator& operator--() noexcept {
            const_iterator::operator--();
            return *this;
        }

        iterator operator++(int) noexcept {
            auto res = const_iterator::operator++(0);
            return iterator{const_cast<node*>(res.Get())};
        }

        iterator operator--(int) noexcept {
            auto res = const_iterator::operator--(0);
            return iterator {const_cast<node*>(res.Get())};
        }
    };
    
public:
    double_linked_list() = default;
    double_linked_list(std::initializer_list<Item> items);
    ~double_linked_list();
    void clear() noexcept;

public:
    void push_front(value_type item) noexcept;
    void push_back(value_type item) noexcept;
    void insert(const_iterator place, value_type item);
    void erase(const_iterator place) noexcept;

public:
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator find(const_reference item) const noexcept;
    iterator find(const_reference item) noexcept;

private:
    node* m_head;
    node* m_tail;
};

#endif