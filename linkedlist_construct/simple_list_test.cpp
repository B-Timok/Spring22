/// @file simple_list_test.cpp

#include <sstream>

#include "simple_list.h"

#define CATCH_CONFIG_MAIN
#if defined __linux__
#include <catch.hpp>
#elif defined __MACH__
#include </opt/local/include/catch2/catch.hpp>
#else
#include "catch.hpp"
#endif

TEST_CASE("void list_init(Node*&, Node*&)") {
    Node* head{};
    Node* tail{};

    list_init(head, tail);

    CHECK(head == nullptr);
    CHECK(tail == nullptr);

    list_insert_first(head, tail, 65);

    CHECK(head != nullptr);
    CHECK(tail != nullptr);

    list_init(head, tail);

    CHECK(head == nullptr);
    CHECK(tail == nullptr);
}

TEST_CASE("bool list_is_empty(const Node*, const Node*)") {
    Node* head{};
    Node* tail{};

    CHECK(list_is_empty(head, tail) == true);

    head = tail = new Node{ 65, nullptr };

    CHECK(list_is_empty(head, tail) == false);

    delete head;
}

TEST_CASE("void list_print(const Node*, const Node*)") {
    std::ostringstream local;
    auto cout_buff = std::cout.rdbuf();  // save pointer to std::cout buffer

    Node* head{};
    Node* tail{};

    std::cout.rdbuf(local.rdbuf());  // substitute internal buffer

    list_print(head, tail);

    CHECK(local.str() == "{}\n");

    head = tail = new Node{65, nullptr};

    for (int i = 66; i <= 70; ++i) {
        tail = tail->link = new Node{i, nullptr};
    }

    local.str("");
    list_print(head, tail);

    CHECK(local.str() == "{65,66,67,68,69,70}\n");

    std::cout.rdbuf(cout_buff);  // restore old buffer

    while (head) { auto temp = head; head = head->link; delete temp; }
}

TEST_CASE("size_t list_size(const Node*, const Node*)") {
    Node* head{};
    Node* tail{};

    CHECK(list_size(head, tail) == 0);

    head = tail = new Node{ 1, nullptr };

    CHECK(list_size(head, tail) == 1);

    for (int i = 2; i <= 10; ++i) {
        head = new Node{ i, head };
        CHECK(list_size(head, tail) == static_cast<size_t>(i));
    }

    CHECK(list_size(head, tail) == 10U);

    while (head) { auto temp = head; head = head->link; delete temp; }
}

TEST_CASE("void list_destroy(Node*&, Node*&)") {
    Node* head{};
    Node* tail{};

    list_destroy(head, tail);

    CHECK(head == nullptr);
    CHECK(tail == nullptr);

    head = tail = new Node{0, nullptr};

    for (int i = 1; i < 10; ++i) {
        head = new Node{i, head};
    }

    list_destroy(head, tail);

    CHECK(head == nullptr);
    CHECK(tail == nullptr);
}

TEST_CASE("int list_front(const Node*, const Node*)") {
    Node* head{};
    Node* tail{};

    head = tail = new Node{0, nullptr};

    CHECK(list_front(head, tail) == 0);

    for (int i = 1; i <= 5; ++i) {
        head = new Node{i, head};
        CHECK(list_front(head, tail) == i);
    }

    while (head) { auto temp = head; head = head->link; delete temp; }
}

TEST_CASE("int list_back(const Node*, const Node*)") {
    Node* head{};
    Node* tail{};

    head = tail = new Node{0, nullptr};

    CHECK(list_back(head, tail) == 0);

    head = new Node{1, head};

    CHECK(list_back(head, tail) == 0);

    while (head) { auto temp = head; head = head->link; delete temp; }
}

TEST_CASE("bool list_search(const Node*, const Node*, int)") {
    Node* head{};
    Node* tail{};

    CHECK(list_search(head, tail, 42) == false);

    head = tail = new Node{65, nullptr};

    for (int i = 66; i <= 70; ++i) {
        tail = tail->link = new Node{i, nullptr};
    }

    CHECK(list_search(head, tail, 42) == false);

    for (int i = 65; i <= 70; ++i) {
        CHECK(list_search(head, tail, i) == true);
    }

    while (head) { auto temp = head; head = head->link; delete temp; }
}

TEST_CASE("void list_insert_first(Node*&, Node*&, int)") {
    Node* head{};
    Node* tail{};

    list_insert_first(head, tail, 65);

    CHECK(head != nullptr);
    CHECK(tail == head);
    CHECK(head->info == 65);
    CHECK(tail->info == 65);

    list_insert_first(head, tail, 66);

    CHECK(head != tail);
    CHECK(head->info == 66);
    CHECK(tail->info == 65);

    for (int i = 2; i <= 26; ++i) {
        list_insert_first(head, tail, i + 65);
        CHECK(head->info == i + 65);
    }

    while (head) { auto temp = head; head = head->link; delete temp; }
}

TEST_CASE("void list_insert_last(Node*&, Node*&, int)") {
    Node* head{};
    Node* tail{};

    list_insert_last(head, tail, 65);

    CHECK(head != nullptr);
    CHECK(tail == head);
    CHECK(head->info == 65);
    CHECK(tail->info == 65);

    list_insert_last(head, tail, 66);

    CHECK(head != tail);
    CHECK(head->info == 65);
    CHECK(tail->info == 66);

    for (int i = 2; i <= 26; ++i) {
        list_insert_last(head, tail, i + 65);
        CHECK(tail->info == i + 65);
    }

    while (head) { auto temp = head; head = head->link; delete temp; }
}

TEST_CASE("void list_delete_first(Node*&, Node*&)") {
    Node* head{};
    Node* tail{};
    int i{};

    head = tail = new Node{65, nullptr};

    for (i = 66; i <= 70; ++i) {
        head = new Node{i, head};
    }

    while (head != nullptr) {
        CHECK(head->info == --i);
        list_delete_first(head, tail);
    }
}

TEST_CASE("void list_delete_last(Node*&, Node*&)") {
    Node* head{};
    Node* tail{};
    int i{};

    head = tail = new Node{65, nullptr};

    for (i = 66; i <= 70; ++i) {
        tail = tail->link = new Node{i, nullptr};
    }

    while (head != nullptr) {
        CHECK(tail->info == --i);
        list_delete_last(head, tail);
    }

    CHECK(tail == nullptr);
}

TEST_CASE("void list_copy(const Node*, const Node*, Node*&, Node*&)") {
    Node* head1{};
    Node* tail1{};
    Node* head2{};
    Node* tail2{};

    head1 = tail1 = new Node{65, nullptr};

    for (int i = 66; i <= 70; ++i) {
        tail1 = tail1->link = new Node{i, nullptr};
    }

    list_copy(head1, tail1, head2, tail2);

    CHECK(head2 != nullptr);
    CHECK(tail2 != nullptr);
    CHECK(head1 != head2);
    CHECK(tail1 != tail2);

    Node* first1 = head1;
    Node* first2 = head2;

    while (first1 != nullptr && first2 != nullptr) {
        CHECK(first1->info == first2->info);
        first1 = first1->link;
        first2 = first2->link;
    }

    CHECK(first1 == nullptr);
    CHECK(first2 == nullptr);

    while (head1) { auto temp = head1; head1 = head1->link; delete temp; }
    while (head2) { auto temp = head2; head2 = head2->link; delete temp; }
}

/* EOF */

