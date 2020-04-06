#pragma once

#include "sorted_list_node.h"

template<typename T, typename C = std::less<>>
class sorted_list {
public:

    using value_type = T;
    using node_type = sorted_list_node<T>;

    sorted_list()
    : list_size{0},
      head{nullptr},
      tail{nullptr}
    {}

    ~sorted_list() {
        clear();
    }

    // checks if value is in list
    bool find(const T & value) const {
        node_type *tmp = head;
        while(tmp && tmp->value != value) tmp = tmp->next;
        return tmp != nullptr;
    }

    // inserts element into list
    void insert(const T & value) {
        node_type * node = new sorted_list_node(value);
        list_size++;

        // empty list
        if(!head) {
            head = node;
            tail = node;
            return;
        }

        // insert front
        if (value < head->value) {
            node->prev = nullptr;
            node->next = head;
            head->prev = node;
            head = node;
            return;
        }

        // insert back
        if(!(value < tail->value)) {
            node->next = nullptr;
            node->prev = tail;
            tail->next = node;
            tail = node;
            return;
        }

        // find position
        node_type *tmp = head;
        while (tmp->next) tmp = tmp->next;
        tmp->prev->next = node;
        node->prev = tmp->prev;
        tmp->prev = node;
        node->next = tmp;
    }

    // print list
    void print_list() {
        std::cout << "===== list ======\n";
        node_type *tmp = head;
        while(tmp) {
            std::cout << "value: " << tmp->value << "\n";
            tmp = tmp->next;
        }
    }

    // removes element and returns true
        // returns false if not found
    bool erase(const T & value) {
        node_type *tmp = head;
        while(tmp && tmp->value != value) tmp = tmp->next;
        if(!tmp) return false;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        delete tmp;
        return true;
    }

    // returns number of elements
    size_t size() const {
        return list_size;
    }

    // checks if there are any elements
    bool empty() const {
        return list_size == 0;
    }

    // returns smallest element
    T &front() const {
        return head->value;
    }

    // returns greatest element
    T &back() const {
        return tail->value;
    }

    // removes smallest element
    void pop_front() {
        list_size--;
        if(size() == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        node_type *tmp = head;
        head = head->next;
        head->prev = nullptr;
        delete tmp;
    }

    // removes greatest element
    void pop_back() {
        list_size--;
        if(size() == 1) {
            delete tail;
            head = nullptr;
            tail = nullptr;
            return;
        }
        node_type *tmp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete tmp;
    }

    // empties list
    void clear() {
        while(head) {
            pop_front();
        }
    }

private:
    // some private members
    node_type *head;
    node_type *tail;

    size_t list_size;
};