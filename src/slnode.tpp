/**
 * @file slnode
 * @author pushyanth kamatham
 * @brief  This file contains the definitions of singly linked Node data structure
 */

#include "../include/slnode.hpp"

// Default constructor
template <typename T>
SlNode<T>::SlNode() : next(nullptr) {}

// Parameterized constructor
template <typename T>
SlNode<T>::SlNode(T data) : data(data), next(nullptr) {}

// Copy constructor
template <typename T>
SlNode<T>::SlNode(const SlNode<T> &other)
{
    data = other.data;
    next = other.next;
}

// Move constructor
template <typename T>
SlNode<T>::SlNode(SlNode<T> &&other) noexcept
    : data(other.data), next(other.next)
{
    other.next = nullptr;
}

// Overload addition operator
template <typename T>
SlNode<T> SlNode<T>::operator+(const SlNode<T> &other) const
{
    SlNode<T> result;
    result.data = data + other.data;
    return result;
}

// Overload subtraction operator
template <typename T>
SlNode<T> SlNode<T>::operator-(const SlNode<T> &other) const
{
    SlNode<T> result;
    result.data = data - other.data;
    return result;
}

// Overload output stream operator
template <typename U>
ostream &operator<<(ostream &os, const SlNode<U> &node)
{
    os << node.data;
    return os;
}

template <typename T>
bool SlNode<T>::operator==(const SlNode<T> &other) const
{
    // Check if both nodes are nullptr
    if (next == nullptr && other.next == nullptr)
    {
        return true;
    }

    // Check if both are pointing to the same node
    if (&this == &other)
    {
        return true;
    }

    //  Iterate through the list and check if the data is equal
    SlNode<T> *__this_ptr = this;
    SlNode<T> *__other_ptr = &other;
    while (__this_ptr != nullptr && __other_ptr != nullptr)
    {
        if (__this_ptr->data != __other_ptr->data)
        {
            return false;
        }

        __this_ptr = __this_ptr->next;
        __other_ptr = __other_ptr->next;
    }

    return true;
}

// TODO: Implement increment (prefix and postfix) operators