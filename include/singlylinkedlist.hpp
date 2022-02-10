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

namespace ds
{
    // TODO: Make some some methods inline for performance
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

        SinglyLinkedList<T> operator+(const SinglyLinkedList<T> &other) const; // Addition operator
        SinglyLinkedList<T> &operator+=(const SinglyLinkedList<T> &other);     // Addition assignment operator

        // Overload output operator
        template <typename U>
        friend ostream &operator<<(ostream &os, const SinglyLinkedList<U> &list);

        size_t size() const;                            // Get size of the list
        SlNode<T> *at(size_t index) const;              // Return pointer to the node at the index
        void push_front(const T data);                  // Insert at head
        void push_back(const T data);                   // Add a new node at the end of the list
        void push_at(size_t index, const T data);       // Insert at given index
        T pop_front();                                  // Remove the head node
        T pop_at(size_t index);                         // Remove the node at the given index
        T pop_back();                                   // Remove the last node
        void delete_at(size_t index);                   // Delete node at given index
        void erase(const T &data);                      // Delete node with given data
        void replace(const T &data, const T &new_data); // Replace node with given data with new data
        void clear();                                   // Clear the list
        bool empty() const;                             // Check if the list is empty
        size_t find(const T &data) const;               // Find the index of the data
        bool contains(const T &data) const;             // Check if the list contains the data
        void reverse();                                 // Reverse the list
        void sort();                                    // Sort the list
        
        // Function to call function on each node (with variable number of arguments)
        template <typename... Args>
        void for_each(void (*func)(SlNode<T> *, Args...), Args... args);
    };
}

#include "../src/singlylinkedlist.tpp"
#endif // __SINGLY_LINKED_LIST__
