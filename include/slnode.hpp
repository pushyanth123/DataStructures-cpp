/**
 * @file slnode.h
 * @author pushyanth kamatham
 * @brief  This file contains the declarations of singly linked Node data structure
 */

#ifndef __SL_NODE_H__
#define __SL_NODE_H__

#include <ostream>

using std::ostream;

template <typename T>
class SlNode
{
public:
    T data;
    SlNode *next;

    SlNode();                           // Default constructor
    SlNode(T data);                     // Parameterized constructor
    SlNode(const SlNode<T> &other);     // Copy constructor
    SlNode(SlNode<T> &&other) noexcept; // Move constructor

    // Operator overloads
    SlNode<T> &operator=(const SlNode<T> &other);     // Copy assignment operator
    SlNode<T> &operator=(SlNode<T> &&other) noexcept; // Move assignment operator
    bool operator==(const SlNode<T> &other) const;    // Equality operator
    bool operator!=(const SlNode<T> &other) const;    // Inequality operator

    SlNode<T> operator+(const SlNode<T> &other) const; // Addition operator
    SlNode<T> operator-(const SlNode<T> &other) const; // Subtraction operator

    // Output stream operator
    template <typename U>
    friend ostream &operator<<(ostream &os, const SlNode<U> &node);

    // TODO: Implement increment (prefix and postfix) operators, (1 increment changes current node to next node)
};

#include "../src/slnode.tpp"
#endif // __SL_NODE_H__
