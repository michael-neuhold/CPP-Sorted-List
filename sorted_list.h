#pragma once
#include "sorted_list_node.h"


class UnaryPredicate {
public:
    bool operator()(int value) {
        return value & 1;   // return true if odd
    }
};

template<typename T>
class PairCompare {
public:
    bool operator()(std::pair<T,T> first,std::pair<T,T> second) {
        return first.first < second.first && first.second < second.second;
    }
};

namespace swe4 {

template<typename T, typename C = std::less<T>>
class sorted_list {
public:

    using value_type = T;
    using node_type = sorted_list_node<T>;
    C compare;

    struct sorted_list_iterator {
        friend sorted_list_iterator sorted_list::insert(sorted_list_iterator hint, const T &value);
        friend void sorted_list::erase(sorted_list_iterator first, sorted_list_iterator last);

        using iterator = sorted_list_iterator;

        // necessary for std::make_reverse_iterator
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using value_type = T;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        sorted_list_iterator();

        sorted_list_iterator(node_type *src, node_type* prev)
        : current_node{src},
          prev_node{prev}
        {}

        sorted_list_iterator(const iterator &src)
        : current_node{src.current_node},
          prev_node{src.prev_node}
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
            current_node = src.current_node;
            prev_node = src.prev_node;
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

        /* for testing */
        iterator &operator +=(int offset) {
            while(offset--) ++(*this);
            return *this;
        }
        /* for testing */
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
    : list_size{ 0 },
      head{ nullptr },
      tail{ nullptr }
    {}

    sorted_list(std::initializer_list<T> list)
    : list_size{ 0 },
      head{ nullptr},
      tail{ nullptr }
    {
        for(auto item : list) insert(item);
    }

    ~sorted_list() {
        clear();
    }

    bool find(const T & value) const {
        node_type *tmp{head};
        while(tmp && tmp->value != value) tmp = tmp->next;
        return tmp != nullptr;
    }
/*
    void insert(const T & value) {
      //  if(find(value)) return;
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

        // find position
        node_type *tmp = head;
        while (tmp->next != nullptr && compare(tmp->next->value,value)) tmp = tmp->next;
        node->next = tmp->next;
        if(tmp->next != nullptr)
            node->next->prev = node;
        else
            tail = node;
        tmp->next = node;
        node->prev = tmp;
    }
*/
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
        assert(!empty() && "&front from empty list");
        return head->value;
    }

    T &back() const {
        assert(!empty() && "&back from empty list");
        return tail->value;
    }

    void pop_front() {
        assert(!empty() && "pop_front from empty list");
        if(size() == 1) clear();
        list_size--;
        node_type *tmp = head;
        head = head->next;
        head->prev = nullptr;
        tmp->next = nullptr;
        delete tmp;
    }

    void pop_back() {
       assert(!empty() && "pop_back from empty list");
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


    std::pair<iterator,bool> insert(const T &value) {
        if(find(value)) return {sorted_list_iterator(head, nullptr),false};
        node_type * node = new sorted_list_node(value);
        list_size++;

        // empty list
        if(!head) {
            head = node;
            tail = node;
            return {sorted_list_iterator(head, nullptr),true};
        }

        // insert front
        if (compare(value,head->value)) {
            node->prev = nullptr;
            node->next = head;
            head->prev = node;
            head = node;
            return {sorted_list_iterator(head, nullptr),true};
        }

        // find position
        node_type *tmp = head;
        while (tmp->next != nullptr && compare(tmp->next->value,value)) tmp = tmp->next;
        node->next = tmp->next;
        if(tmp->next != nullptr)
            node->next->prev = node;
        else
            tail = node;
        tmp->next = node;
        node->prev = tmp;
        return {sorted_list_iterator(node, nullptr),true};
    }


    iterator insert(iterator hint, const T &value) {
        if(find(value)) return hint;
        node_type * node = new sorted_list_node(value);
        list_size++;
        if(empty()) {
            head = node;
            tail = node;
            return hint;
        } else {
            if(compare(*hint,value)) {
                while(hint.current_node && compare(*hint, value)) hint++;
                hint--;
            } else if (!compare(*hint,value)) {
                while(hint.current_node->prev && !compare(*hint, value)) hint--;
            }
            if(hint.current_node == head) {
                node->next = hint.current_node;
                hint.current_node->prev = node;
                head = node;
            } else {
                node->next = hint.current_node->next;
                if(hint.current_node->next != nullptr)
                    node->next->prev = node;
                else
                    tail = node;
                hint.current_node->next = node;
                node->prev = hint.current_node;
            }
        }
        return sorted_list_iterator{node, nullptr};
    }

    // interval: [first,last) includes first but not last
    void erase(iterator first, iterator last) {
        if(first == last) return;
        while(first != last) {
            iterator tmp{first};
            first++;
            if(tmp.current_node->prev)
                tmp.current_node->prev->next = tmp.current_node->next;
            else
                head = first.current_node;
            if(tmp.current_node->next)
                tmp.current_node->next->prev = tmp.current_node->prev;
            else
                tail = tmp.current_node->prev;
            delete tmp.current_node;
        }
    }

    template<class UnaryPredicate> void erase_if(UnaryPredicate p) {
        node_type *current{head};
        node_type *tmp{nullptr};
        if(empty()) return;

        while(current) {
            if(p(current->value)) {
                if (current == head) {
                    pop_front();
                    current = head;
                } else if (current == tail) {
                    pop_back();
                    current = tail;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    tmp = current;
                    current = current->next;
                    delete tmp;
                    list_size--;
                }
            } else {
                current = current->next;
            }
        }
    }

private:
    node_type *head;
    node_type *tail;
    size_t list_size;
};

}