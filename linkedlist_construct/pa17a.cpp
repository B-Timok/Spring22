/// @file pa17a.cpp
/// @author Brandon Timok
/// @date 03/23/2022
/// @brief Construction of a linked list that is mutatable with several
/// standalone functions.

#include <iostream>
#include "simple_list.h"

void merge_lists(Node* first1, Node* last1, Node* first2, Node* last2,
                 Node*& first3, Node*& last3);

int main() {
    Node* first1 {};
    Node* last1 {};
    Node* first2 {};
    Node* last2 {};
    Node* first3 {};
    Node* last3 {};

    list_insert_first(first1, last1, 50);
    list_insert_first(first2, last2, 50);

    while (list_size(first1, last1) < 15) {
        int random_num = rand() % 100;

        if (random_num <= list_front(first1, last1)) {
            list_insert_first(first1, last1, random_num);
        } else if (random_num >= list_back(first1, last1)) {
            list_insert_last(first1, last1, random_num);
        }
    }
    while (list_size(first2, last2) < 15) {
        int random_num = rand() % 100;

        if (random_num <= list_front(first2, last2)) {
            list_insert_first(first2, last2, random_num);
        } else if (random_num >= list_back(first2, last2)) {
            list_insert_last(first2, last2, random_num);
        }
    }

    std::cout << std::endl;
    std::cout << "First list: ";
    list_print(first1, last1);
    std::cout << std::endl;

    std::cout << "Second list: ";
    list_print(first2, last2);
    std::cout << std::endl;

    merge_lists(first1, last1, first2, last2, first3, last3);

    std::cout << "Merged lists: ";
    list_print(first3, last3);
    std::cout << std::endl;

    return 0;
}

/// merges two lists into one sorted list with all unique numbers
void merge_lists(Node* first1, Node* last1, Node* first2, Node* last2,
                 Node*& first3, Node*& last3) {
    while (first1 != nullptr && first2 != nullptr) {
        if (first1->info == first2->info) {
            first1 = first1->link;
        } else if (first1->info < first2->info) {
            if (first1->info == last3->info) {
                first1 = first1->link;
            } else {
                list_insert_last(first3, last3, first1->info);
                first1 = first1->link;
            }
        } else {
            list_insert_last(first3, last3, first2->info);
            first2 = first2->link;
        }
    }
    while (first1 != nullptr) {
        if (first1->info == last3->info) {
            first1 = first1->link;
        } else {
            list_insert_last(first3, last3, first1->info);
        }
    }
    while (first2 != nullptr) {
        if (first2->info == last3->info) {
            first2 = first2->link;
        } else {
            list_insert_last(first3, last3, first2->info);
        }
    }
}
