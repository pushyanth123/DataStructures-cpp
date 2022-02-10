/**
 * @file slnode
 * @author pushyanth kamatham
 * @brief  This file contains the definitions of singly linked Node data structure
 */

#include "../include/slnode.hpp"
using ds::SlNode;
using std::ostream;

namespace ds
{
    // Overload output stream operator
    template <typename U>
    ostream &operator<<(ostream &os, const SlNode<U> &node)
    {
        os << node.data;
        return os;
    }
}

// Default constructor
template <typename T>
SlNode<T>::SlNode() : next(nullptr), data(0) {}

// Parameterized constructor
template <typename T>
SlNode<T>::SlNode(T data) : data(data), next(nullptr) {}

// Copy constructor
template <typename T>
SlNode<T>::SlNode(const SlNode<T> &other)
    : data(other.data), next(other.next) {}

// Move constructor
template <typename T>
SlNode<T>::SlNode(SlNode<T> &&other) noexcept
    : data(other.data), next(other.next)
{
    other.data = (T)NULL;
    other.next = nullptr;
}

// Copy assignment operator
template <typename T>
SlNode<T> &SlNode<T>::operator=(const SlNode<T> &other)
{
    SlNode<T> temp(other);
    std::swap(data, temp.data);
    std::swap(next, temp.next);
    return *this;
}

// Move assignment operator
template <typename T>
SlNode<T> &SlNode<T>::operator=(SlNode<T> &&other) noexcept
{
    this->data = other.data, this->next = other.next;
    other.data = (T)NULL;
    other.next = nullptr;
    return *this;
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

template <typename T>
bool SlNode<T>::operator==(const SlNode<T> &other) const
{
    if (this == &other)
        return true;

    // Check if both first data is equal and pointers are equal
    if (next == other.next && data == other.data)
        return true;

    //  Iterate through the list and check if the data is equal
    SlNode<T> *__this_ptr = (SlNode<T> *)this;
    SlNode<T> *__other_ptr = (SlNode<T> *)&other;
    while (__this_ptr != nullptr && __other_ptr != nullptr)
    {
        if (__this_ptr->data != __other_ptr->data)
            return false;

        __this_ptr = __this_ptr->next, __other_ptr = __other_ptr->next;
    }

    return true;
}

// Overload inequality operator
template <typename T>
bool SlNode<T>::operator!=(const SlNode<T> &other) const
{
    return !(*this == other);
}

// Method to copy all the nodes in the list into a new list
template <typename T>
SlNode<T> *SlNode<T>::copy()
{
    SlNode<T> *_head = new SlNode<T>(this->data);
    SlNode<T> *__source_ptr = this, *__dest_ptr = _head;

    while (__source_ptr->next != nullptr)
    {
        __source_ptr = __source_ptr->next;
        __dest_ptr->next = new SlNode<T>(__source_ptr->data);
         __dest_ptr = __dest_ptr->next;
    }

    return _head;
}
