/// @file List.hpp
/// @author Brandon Timok
/// @date 04/12/2022
/// @brief Header file for dynamic list class functions.

#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <cassert>
#include <algorithm>
#include <utility>
#include <initializer_list>
#include <iterator>
#include <cstdlib>

template <class T>
class List {
private:
    struct Node {
        T     data{};  ///< value stored in the Node
        Node* prev{};  ///< pointer to the previous Node
        Node* next{};  ///< pointer to the next Node
    };
public:
    class Iterator {
    public:
        // member types
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = Node*;
        using reference         = value_type&;

        Iterator(pointer ptr = nullptr)
        : current(ptr)
        {}

        reference operator*() const {
            if (current == nullptr) {
                throw std::logic_error("error: dereferencing nullptr");
            }
            return current->data;
        }

        pointer operator->() {
            return current;
        }

        Iterator& operator++() {
            if (current == nullptr) {
                throw std::logic_error("error: dereferencing nullptr");
            }
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            if (current == nullptr) {
                throw std::logic_error("error: dereferencing nullptr");
            }
            Iterator tmp = *this;
            current = current->next;
            return tmp;
        }

        Iterator& operator--() {
            if (current == nullptr) {
                throw std::logic_error("error: dereferencing nullptr");
            }
            current = current->prev;
            return *this;
        }

        Iterator operator--(int) {
            if (current == nullptr) {
                throw std::logic_error("error: dereferencing nullptr");
            }
            Iterator tmp = *this;
            current = current->prev;
            return tmp;
        }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.current == rhs.current;
        }

        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return lhs.current != rhs.current;
        }

    private:
        pointer current{};
    };

    // Member types
    using value_type = T;
    using size_type  = std::size_t;
    using reference  = value_type&;
    using iterator   = Iterator;

    List() = default;
    List(const List& other);
    List(List&& other);
    List(const std::initializer_list<value_type>& ilist);
    virtual ~List();
    List& operator=(const List& rhs);
    List& operator=(List&& rhs);
    reference front();
    reference back();
    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(); }
    bool empty() const { return begin() == end(); }
    size_type size() const { return count; }
    void clear();
    iterator insert(iterator pos, const value_type& value);
    iterator erase(iterator pos);
    void swap(List& other);

protected:
    Node*     head{};   ///< pointer to the head node
    Node*     tail{};   ///< pointer to the tail node
    size_type count{};  ///< number of nodes in list
};

/** NON-MEMBER TEMPLATE FUNCTIONS **/
template <class T>
bool operator==(const List<T>& lhs, const List<T>& rhs);

template <class T>
bool operator!=(const List<T>& lhs, const List<T>& rhs);

template <class T>
std::ostream& operator<<(std::ostream& output, const List<T>& list);

// copy constructor
template <class T>
List<T>::List(const List<T>& other) {
    *this = other;
}

// move constructor
template <class T>
List<T>::List(List<T>&& other) {
    head = (std::exchange(other.head, nullptr));
    tail = (std::exchange(other.tail, nullptr));
    count = (std::exchange(other.count, 0));
}

// list initializer
template <class T>
List<T>::List(const std::initializer_list<value_type>& ilist) {
    for (auto& itr : ilist) {
        List<T>::insert(end(), itr);
    }
}

// destructor
template <class T>
List<T>::~List() {
    clear();
}

// copy assignment operator
template <class T>
List<T>& List<T>::operator=(const List<T>& rhs) {
    if (this != &rhs) {
        clear();

        for (auto& itr : rhs) {
            insert(end(), itr);
        }
    }
    return *this;
}

// move assignment operator
template <class T>
List<T>& List<T>::operator=(List<T>&& rhs) {
    if (this != &rhs) {
        clear();

        head = std::exchange(rhs.head, nullptr);
        tail = std::exchange(rhs.tail, nullptr);
        count = std::exchange(rhs.count, 0);
    }
    return *this;
}

// returns first element of the list
template <class T>
typename List<T>::reference List<T>::front() {
    return !empty() ? head->data : throw std::logic_error("empty list");
}

// returns the last element of the list
template <class T>
typename List<T>::reference List<T>::back() {
    return !empty() ? tail->data : throw std::logic_error("empty list");
}

template <class T>
void List<T>::clear() {
    while (!empty()) {
        erase(begin());
    }
}

// inserts a new node into the list
template <class T>
typename List<T>::iterator
List<T>::insert(List<T>::iterator pos, const value_type& value) {
    Node* const newNode = new Node{value}; // new node to be inserted
    if (empty()) { // if empty, new node is the only node
        head = tail = newNode;
    } else if (pos == begin()) { // if inserting at beginning
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else if (pos == end()) { // if inserting at the end
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    } else { // if inserting anywhere else in the list
        newNode->next = pos->prev->next;
        newNode->prev = pos->prev;
        pos->prev->next = newNode;
        pos->prev = newNode;
    }
    ++count;
    return iterator(newNode);
}

// function to erase a specific node from the list
template <class T>
typename List<T>::iterator List<T>::erase(List<T>::iterator pos) {
    auto following = List<T>::iterator(); // iterator following pos

    if (!empty() && pos != end()) {
        if (pos == begin()) { // item to be deleted is first node
            head = head->next;
            
            if(head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            } 
        } else { // item to be deleted is somewhere else in list
            pos->prev->next = pos->next;

            if (pos->next != nullptr) {
                pos->next->prev = pos->prev;
            }

            if (pos == tail) {
                tail = pos->prev;
            }
        }
    }
    following = pos->next;
    delete pos.operator->();
    --count;
    return following;
}

template <class T>
void List<T>::swap(List<T>& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(count, other.count);
}

template <class T>
bool operator==(const List<T>& lhs, const List<T>& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T>
bool operator!=(const List<T>& lhs, const List<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
std::ostream& operator<<(std::ostream& output, const List<T>& list) {
    char separator[2]{};

    output << '{';

    for (auto& itr : list) {
        output << separator << itr;
        *separator = ',';
    }
    return output << '}';
}

#endif
