#pragma once

template<typename T, typename C = std::less<T>>
class sorted_list {
public:
    sorted_list();
    ~sorted_list();

    bool find(const T & value) const;   // checks if value is in list
    void insert(const T & value);   // inserts element into list
    bool erase(const T & value);    // removes element and returns true
                                        // returns false if not found
    size_t size() const;    // returns number of elements
    bool empty() const;     // checks if there are any elements
    T &front() const;       // returns smallest element
    T &back() const;        // returns greatest element

    void pop_front();       // removes smallest element
    void pop_back();        // removes greatest element

    void clear();           // empties list

private:
    // some private members
};