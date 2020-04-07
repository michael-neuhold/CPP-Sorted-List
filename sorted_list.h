#pragma once

#include "sorted_list_node.h"

template<typename T, typename C = std::less<>>
class sorted_list {
public:

    using value_type = T;
    using node_type = sorted_list_node<T>;


    struct sorted_list_iterator {

        using iterator = sorted_list_iterator;

        sorted_list_iterator();

        sorted_list_iterator(node_type *src)
        : current_node{src}
        {}

        sorted_list_iterator(iterator &src)
        : current_node{src.current_node}
        {}

        ~sorted_list_iterator() {
            // nothing to do
        }

        // compare operator
        friend bool operator==(iterator const & lhs,iterator const & rhs) {
            return {};
        }

        friend bool operator!=(iterator const & lhs,iterator const & rhs) {
            return {};
        }

        friend bool operator<=(iterator const & lhs,iterator const & rhs) {
            return {};
        }

        friend bool operator>=(iterator const & lhs,iterator const & rhs) {
            return {};
        }

        friend bool operator<(iterator const & lhs,iterator const & rhs) {
            return {};
        }

        friend bool operator>(iterator const & lhs,iterator const & rhs) {
            return {};
        }

        // other operators

        iterator &operator=(iterator const & src) {
            current_node = src;
            return *this;
        }

        value_type &operator*() {
            return current_node->value;
        }

        value_type operator->() {
            return current_node->value;
        }

        iterator &operator++() {
            current_node = current_node->next;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp{*this};
            current_node = current_node->next;
            return tmp;
        }

        iterator &operator--() {
            current_node = current_node->prev;
            return *this;
        }

        iterator operator--(int) {
            iterator tmp{*this};
            current_node = current_node->prev;
            return tmp;
        }

        iterator &operator +=(int offset) {
            while(offset--) ++(*this);
            return *this;
        }

        iterator &operator -=(int offset) {
            while(offset--) --(*this);
            return *this;
        }

    private:
        // some privates
        node_type *current_node;
    };

    using iterator = sorted_list_iterator;

    sorted_list()
    : list_size{0},
      head{nullptr},
      tail{nullptr}
    {}

    ~sorted_list() {
        clear();
    }

    bool find(const T & value) const {
        node_type *tmp = head;
        while(tmp && tmp->value != value) tmp = tmp->next;
        return tmp != nullptr;
    }

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

    void print_list() {
        std::cout << "===== list ======\n";
        node_type *tmp = head;
        while(tmp) {
            std::cout << "value: " << tmp->value << "\n";
            tmp = tmp->next;
        }
    }

    bool erase(const T & value) {
        node_type *tmp = head;
        while(tmp && tmp->value != value) tmp = tmp->next;
        if(!tmp) return false;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        delete tmp;
        return true;
    }

    size_t size() const {
        return list_size;
    }

    bool empty() const {
        return list_size == 0;
    }

    T &front() const {
        assert(head);
        return head->value;
    }

    T &back() const {
        assert(tail);
        return tail->value;
    }

    void pop_front() {
        if(empty()) return;
        if(size() == 1) clear();
        list_size--;
        node_type *tmp = head;
        head = head->next;
        head->prev = nullptr;
        tmp->next = nullptr;
        delete tmp;
    }

    void pop_back() {
       if(empty()) return;
       if(size() == 1) clear();
       list_size--;
       node_type *tmp = tail;
       tail = tail->prev;
       tail->next = nullptr;
       tmp->prev = nullptr;
       delete tmp;
    }

    void clear() {
        node_type *tmp;
        while(head) {
            tmp = head;
            head = head->next;
            delete tmp;
            list_size--;
        }
    }

    /* ================== */

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(tail);
    }

    //iterator rbegin();
    //iterator rend();

    //std::pair<iterator, bool> insert(const T &value);
    //iterator insert(iterator hint, const T &value);
    //void erase(iterator first, iterator last);



private:
    // some private members
    node_type *head;
    node_type *tail;

    size_t list_size;
};