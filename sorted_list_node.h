#pragma once

template<typename T>
struct sorted_list_node {

    using value_type = T;

    sorted_list_node(T value)
    : value{value}
    {}

    value_type value;
    sorted_list_node *prev{nullptr};
    sorted_list_node *next{nullptr};
};