#pragma once
#include "sorted_list_node.h"

template<typename T, typename C = std::less<T>>
class sorted_list {
public:

    using value_type = T;
    using node_type = sorted_list_node<T>;
    C compare;

    struct sorted_list_iterator {
        friend sorted_list_iterator sorted_list::insert(sorted_list_iterator hint, const T &value);

        using iterator = sorted_list_iterator;

        sorted_list_iterator();

        sorted_list_iterator(node_type *src, node_type* prev)
        : current_node{src},
          prev_node{prev}
        {}

        sorted_list_iterator(iterator &src)
        : current_node{src.current_node}
        {}

        ~sorted_list_iterator() {
        }

        // compare operator
        friend bool operator==(iterator const & lhs,iterator const & rhs) {
            return lhs.current_node == rhs.current_node;
        }

        friend bool operator!=(iterator const & lhs,iterator const & rhs) {
            return !(lhs==rhs);
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
            prev_node = current_node;
            current_node = current_node->next;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp{*this};
            prev_node = current_node;
            current_node = current_node->next;
            return tmp;
        }

        iterator &operator--() {
            if(current_node) {
                prev_node = current_node;
                current_node = current_node->prev;
            } else {
                current_node = prev_node;
                prev_node = nullptr;
            }

            return *this;
        }

        iterator operator--(int) {
            iterator tmp{*this};
            if(current_node) {
                prev_node = current_node;
                current_node = current_node->prev;
            } else {
                current_node = prev_node;
                prev_node = nullptr;
            }
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
        node_type *prev_node;
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

        // return if value already exists in list
        if(find(value)) return;
        node_type * node = new sorted_list_node(value);
        list_size++;

        // empty list
        if(!head) {
            head = node;
            tail = node;
            return;
        }

        // insert front
        if (compare(value,head->value)) {
            node->prev = nullptr;
            node->next = head;
            head->prev = node;
            head = node;
            return;
        }

        // insert back
        if(!(compare(value,tail->value))) {
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
        std::cout << "sorted_list: ";
        node_type *tmp = head;
        while(tmp) {
            std::cout << tmp->value << " ";
            tmp = tmp->next;
        }
        std::cout << "\n";
    }

    bool erase(const T & value) {
        node_type *tmp = head;
        while(tmp && tmp->value != value) tmp = tmp->next;
        if(!tmp) return false;
        if(size() == 1) clear();
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        list_size--;
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
        return iterator(head, nullptr);
    }

    iterator end() {
        return iterator(nullptr, tail);
    }

    std::reverse_iterator<iterator> rbegin() {
        return std::make_reverse_iterator(end());
    }

    std::reverse_iterator<iterator> rend() {
        return std::make_reverse_iterator(begin());
    }

    /*
    std::pair<iterator,bool> insert(const T &value) {
        iterator test{head, nullptr};
        return {test,true};
    }


    iterator insert(iterator hint, const T &value) { // TODO
        node_type * node = new sorted_list_node(value);

        if(!hint.current_node->prev && C(value,*hint)) {
            // push front
        }

        if(!hint.current_node->next && !C(value,*hint)) {
            // push back
        }

        node->prev = hint.current_node;
        node->next = hint.current_node->next;
        hint.current_node->next = node;
        return iterator(node);
    }
    */
    void erase(iterator first, iterator last) {
        // to do
    }

private:
    // some private members
    node_type *head;
    node_type *tail;

    size_t list_size;
};