/**
 * @file    singlylinkedlist.h
 * @author  pushyanth kamatham
 * @brief   This file contains the definitions of singly linked list data structure
 */

#ifndef __SINGLY_LINKED_LIST__
#define __SINGLY_LINKED_LIST__

#include <ostream>
#include "slnode.hpp"

using std::initializer_list;
using std::ostream;
using std::size_t;

template <typename T>
class SinglyLinkedList
{
private:
    SlNode<T> *head; // Head of the singly linked list
    size_t _size;    // Current size
public:
    SinglyLinkedList();                                     // Default constructor
    SinglyLinkedList(const T &data);                        // Parameterized constructor
    SinglyLinkedList(const SinglyLinkedList<T> &other);     // Copy constructor
    SinglyLinkedList(SinglyLinkedList<T> &&other) noexcept; // Move constructor
    SinglyLinkedList(const initializer_list<T> &list);      // Initializer list constructor
    ~SinglyLinkedList();                                    // Destructor

    SinglyLinkedList<T> &operator=(const SinglyLinkedList<T> &other);     // copy assignment operator
    SinglyLinkedList<T> &operator=(SinglyLinkedList<T> &&other) noexcept; // move assignment operator

    T &operator[](size_t index);       // Return reference to the data at the index
    T &operator[](size_t index) const; // Return reference to the data at the index

    bool operator==(const SinglyLinkedList<T> &other) const; // Equality operator
    bool operator!=(const SinglyLinkedList<T> &other) const; // Inequality operator

    // "+" operator overload (concatenate two lists)
    SinglyLinkedList<T> operator+(const SinglyLinkedList<T> &other) const;

    // Overload output operator
    template <typename U>
    friend ostream &operator<<(ostream &os, const SinglyLinkedList<U> &list);

    size_t size() const;                   // Get size of the list
    void insert(const T &data);            // Insert at head
    void insert_end(const T &data);        // Add a new node at the end of the list
    void insert_at(size_t index, T &data); // Insert at given index
    T pop();                               // Remove head node
    T remove_at(size_t index);             // Delete node at given index
    T pop_back();                          // Remove last node
    void clear();                          // Clear the list
    bool is_empty() const;                 // Check if the list is empty
    size_t find(const T &data) const;      // Find the index of the data
    bool contains(const T &data) const;    // Check if the list contains the data
    void reverse();                        // Reverse the list
    void sort();                           // Sort the list

    // TODO: Implement iterators
};

#include "../src/singlylinkedlist.tpp"
#endif // __SINGLY_LINKED_LIST__
