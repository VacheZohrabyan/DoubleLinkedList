#include "DoubleLinkedList.tpp"

template<typename Item>
double_linked_list<Item>::double_linked_list(std::initializer_list<Item> items) 
                                            : m_head{nullptr}, m_tail{nullptr}{
    for (auto item: items) {
        push_back(item);
    }
}

template<typename Item>
double_linked_list<Item>::~double_linked_list() {
    clear();
}

template <typename Item>
void double_linked_list<Item>::push_front(value_type item) noexcept {
    auto newnode = new node {std::move(item)};
    if (m_head) {
        m_head->prev = newnode;
        newnode->next = m_head;
        m_head = newnode;
    } else {
        m_head = m_tail = newnode;
    }
}

template <typename Item>
void double_linked_list<Item>::push_back(value_type item) noexcept {
    auto newnode = new node {std::move(item)};
    if (m_head) {
        newnode->prev = m_tail;
        m_tail->next = newnode;
        m_tail = newnode;
    } else {
        m_head = m_tail = newnode;
    }
}

template <typename Item>
void double_linked_list<Item>::insert(const_iterator place, value_type item) {
    auto ptr = const_cast<node*>(place.Get());
    if (!ptr) {
        push_back(item);
        return;
    }
    auto newnode = new node {std::move(item)};

    newnode->next = ptr;
    newnode->prev = ptr->prev;

    if (ptr->prev) {
        ptr->prev->next = newnode;
    }

    ptr->prev = newnode;
}

template <typename Item>
void double_linked_list<Item>::erase(const_iterator place) noexcept {
    auto ptr = const_cast<node*>(place.Get());
    assert(ptr != nullptr);

    if (ptr->prev) {
        ptr->prev->next = ptr->next;
    } else {
        m_head = ptr->next;
    }

    if (ptr->next) {
        ptr->next->prev = ptr->prev;
    } else {
        m_tail = ptr->prev;
    }

    delete ptr;
}

template <typename Item>
void double_linked_list<Item>::clear() noexcept {
    while (m_head) {
        delete std::exchange(m_head, m_head->next);
    }
}

template<typename Item>
typename double_linked_list<Item>::const_iterator double_linked_list<Item>::begin() const noexcept {
    return const_iterator {m_head};
}

template <typename Item>
typename double_linked_list<Item>::const_iterator double_linked_list<Item>::end() const noexcept {
    return const_iterator {nullptr};
}

template <typename Item>
typename double_linked_list<Item>::const_iterator double_linked_list<Item>::cbegin() const noexcept {
    return const_iterator {m_head};
}

template <typename Item>
typename double_linked_list<Item>::const_iterator double_linked_list<Item>::cend() const noexcept {
    return const_iterator {nullptr};
}

template <typename Item>
typename double_linked_list<Item>::iterator double_linked_list<Item>::begin() noexcept {
    return iterator{m_head};
}

template <typename Item>
typename double_linked_list<Item>::iterator double_linked_list<Item>::end() noexcept {
    return iterator{nullptr};
}

template <typename Item>
typename double_linked_list<Item>::const_iterator double_linked_list<Item>::find(const_reference item) const noexcept {
    for (auto it = begin(); it != end(); ++it) {
        if (*it == item) {
            return it;
        }
    }
    return const_iterator{nullptr};
}

template <typename Item>
typename double_linked_list<Item>::iterator double_linked_list<Item>::find(const_reference item) noexcept {
    const auto& const_ref = static_cast<const double_linked_list<Item>&>(*this);
    const_iterator it = const_ref.find(item);
    return iterator{const_cast<node*>(it.Get())};
}