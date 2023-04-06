/// @file simple_list.cpp
/// @author Brandon Timok
/// @date 03/23/2022
/// @brief Construction of a linked list that is mutatable with several
/// standalone functions.

#include <iostream>
#include <cassert>
#include "simple_list.h"

/// initializes a list to empty
void list_init(Node*& first, Node*& last) {
    while (first != nullptr) {
        Node* temp = first;
        first = first->link;
        delete temp;
    }
    first = nullptr;
    last = nullptr;
}

/// checks whether a list is empty
bool list_is_empty(const Node* first, const Node* last) {
    return (first == nullptr);
}

/// prints a list in order using {1,2,3} format
void list_print(const Node* first, const Node* last) {
    const Node* current = first;
    size_t i = 0;

    std::cout << '{';

    while (current != nullptr) {
        std::cout << current->info;
        i++;
        if (i < list_size(first, last)) {
            std::cout << ',';
        }
        current = current->link;
    }
    std::cout << '}' << '\n';
}

/// returns the number of elements (nodes) in a list
size_t list_size(const Node* first, const Node* last) {
    size_t size = 0;
    const Node* current = first;

    while (current != nullptr) {
        ++size;
        current = current->link;
    }
    return size;
}

/// destroys a list
void list_destroy(Node*& first, Node*& last) {
    while (first != nullptr) {
        Node* temp = first;
        first = first->link;
        delete temp;
    }
    last = nullptr;
}

/// accesses the front element of a list
int list_front(const Node* first, const Node* last) {
    assert (first != nullptr);
    // if (first == nullptr) {
    //     throw ()
    // };
    return first->info;
}

/// accesses the back element of a list
int list_back(const Node* first, const Node* last) {
    assert (last != nullptr);
    // if (last == nullptr) {
    //     throw ()
    // }:
    return last->info;
}

/// searches a list for an item, returning true if found
bool list_search(const Node* first, const Node* last, int item) {
    bool found = false;
    const Node* current = first;

    while (current != nullptr) {
        if (current->info == item) {
            found = true;
        }
        current = current->link;
    }
    return found;
}

// inserts an element to the beginning of a list
void list_insert_first(Node*& first, Node*& last, int item) {
    // allocate memory for new node to insert
    Node* newNode = new Node;
    newNode->info = item;
    // put new node in front of first node
    newNode->link = first;
    // set front node to be new node
    first = newNode;
    if (last == nullptr) {
        last = newNode;
    }
}

/// inserts an element to the end of a list
void list_insert_last(Node*& first, Node*& last, int item) {
    Node* newNode = new Node;
    newNode->info = item;
    // if empty list
    if (first == nullptr) {
        first = last = newNode;
    } else {
        last->link = newNode;
        last = newNode;
    }
}

/// removes the first element from a list
void list_delete_first(Node*& first, Node*& last) {
    if (first != nullptr) {
        Node* temp = first;
        first = first->link;
        delete temp;

        if (first == nullptr) {
            last = nullptr;
        }
    }
}

/// removes the last element from a list
void list_delete_last(Node*& first, Node*& last) {
    if (last != nullptr) {
        Node* current = first;

        while (current != nullptr && current->link != last) {
            current = current->link;
        }

        Node* temp = last;
        last = current;
        last->link = nullptr;
        delete temp;
    }
    if (first == last) {
        first = last = nullptr;
    }
}

/// creates of copy of the nodes from first1 to last1,
/// the copy begins at first2 and ending at last2 
void list_copy(const Node* first1, const Node* last1, 
               Node*& first2, Node*& last2) {
    if (first1 == nullptr) {
        list_destroy(first2, last2);
    }
    const Node* current = first1;

    while (current != nullptr) {
        list_insert_last(first2, last2, current->info);
        current = current->link;
    }
}
