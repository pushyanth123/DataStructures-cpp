/**
 * @file singlylinkedlist
 * @author pushyanth kamatham
 * @brief This file contains the definitions of SinglyLinkedList data structure
 */

#include "../include/singlylinkedlist.hpp"
#include <functional>

using ds::SinglyLinkedList;
using ds::SlNode;
using std::ostream;

namespace ds
{
    template <typename T>
    ostream &operator<<(ostream &os, const SinglyLinkedList<T> &list)
    {
        using std::ostream;
        if (list.head == nullptr)
            return os << "{}";

        os << "{ ";
        SlNode<T> *temp = list.head;
        while (temp->next != nullptr)
        {
            os << temp->data << ", ";
            temp = temp->next;
        }
        os << temp->data << " }";
        return os;
    }
}

inline void index_out_of_range_exception(int _actual_index, int _max_index)
{
    throw std::out_of_range("Index " + std::to_string(_actual_index) +
                            " is out of bounds, max index is " + std::to_string(_max_index));
}

// Default constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
{
    this->head = nullptr;
    this->_size = 0;
}

// Parameterized constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const T &data)
{
    head = new SlNode<T>;
    head->data = data;
    head->next = nullptr;
    _size = 1;
}

// Copy constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T> &other)
{
    this->head = nullptr;
    this->_size = 0;

    *this = other; // Call the copy assignment operator
}

// Move constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T> &&other) noexcept
    : head(other.head), _size(other._size)
{
    other.head = nullptr;
    other._size = 0;
}

// Initializer list constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const std::initializer_list<T> &list)
{
    if (list.size() == 0) // If list is empty, return
        return;

    this->head = new SlNode<T>;
    SlNode<T> *__this_ptr = this->head;

    // Copy all nodes into the list
    auto __itr = std::begin(list);
    for (;; ++__itr)
    {
        __this_ptr->data = *__itr;
        if (__itr + 1 == std::end(list))
            break;
        __this_ptr->next = new SlNode<T>;
        __this_ptr = __this_ptr->next;
    }

    this->_size = list.size();
}

// Destructor
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    if (this->head == nullptr) // Return if list is empty
        return;

    SlNode<T> *__temp = this->head;
    while (__temp != nullptr)
    {
        SlNode<T> *next = __temp->next;
        delete __temp;
        __temp = next;
    }

    this->head = nullptr;
    this->_size = 0;
}

// Copy assignment operator
template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(const SinglyLinkedList<T> &other)
{
    // If other list is empty or both operator lists are same, return
    if (other.head == nullptr || this == &other)
        return *this;

    // Delete existing data if the list is not empty
    if (this->head != nullptr)
        this->~SinglyLinkedList();

    this->head = other.head->copy();
    this->_size = other._size; // Copy the size
    return *this;
}

// Move assignment operator
template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(SinglyLinkedList<T> &&other) noexcept
{
    // Check if the list is not empty
    if (this->head != nullptr)
        this->~SinglyLinkedList(); // Call destructor

    // Call swap function
    std::swap(this->head, other.head);
    std::swap(this->_size, other._size);

    return *this;
}

// Overload [] operator (get and set)
template <typename T>
T &SinglyLinkedList<T>::operator[](size_t index)
{
    return this->at(index)->data;
}

// Overload [] operator (get only)
template <typename T>
T &SinglyLinkedList<T>::operator[](size_t index) const
{
    // Call non-const version and cast it to const version
    return const_cast<SinglyLinkedList<T> *>(this)->operator[](index);
}

// Overload "==" operator to check if two lists are equal
template <typename T>
bool SinglyLinkedList<T>::operator==(const SinglyLinkedList<T> &other) const
{
    // If both are different size, return false
    if (this->_size != other.size())
        return false;

    // If both are not empty, call SlNode's == operator
    return *this->head == *other.head;
}

// Overload "!=" operator to check if two lists are not equal
template <typename T>
bool SinglyLinkedList<T>::operator!=(const SinglyLinkedList<T> &other) const
{
    return !(*this == other);
}

// Overload "+" operator to concatenate two lists
template <typename T>
SinglyLinkedList<T> SinglyLinkedList<T>::operator+(const SinglyLinkedList<T> &other) const
{
    // If either list is empty, return the other list (it won't copy the data)
    if (this->head == nullptr)
        return other;
    if (other.head == nullptr)
        return *this;

    // Call copy constructor
    SinglyLinkedList<T> result(*this);

    return result.operator+=(other); // Call += operator
}

// Overload "+=" operator to concatenate two lists
template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator+=(const SinglyLinkedList<T> &other)
{
    SlNode<T> *__this_ptr = this->at(this->size() - 1);
    __this_ptr->next = other.head->copy(); // Copy the other list
    this->_size += other.size();           // Update size

    return *this;
}

// Function to get the size of the list
template <typename T>
size_t SinglyLinkedList<T>::size() const
{
    return _size;
}

// Return pointer to the node at the index
template <typename T>
inline SlNode<T> *SinglyLinkedList<T>::at(size_t _index) const
{
    SlNode<T> *_temp = this->head;
    while (_index--)
        _temp = _temp->next;

    return _temp;
}

// Function to insert data at front of the list
template <typename T>
void SinglyLinkedList<T>::push_front(const T data)
{
    // Create a new SlNode
    SlNode<T> *_temp = new SlNode<T>(data);
    _temp->next = this->head;

    this->head = _temp; // Update the head pointer
    _size += 1;         // Increment the size of list
}

// Function to insert data at the end of the list
template <typename T>
void SinglyLinkedList<T>::push_back(const T data)
{
    SlNode<T> *temp = (this->head == nullptr) ? (head = new SlNode<T>(data)) : this->at(this->_size - 1);
    temp->next = new SlNode<T>(data);
    this->_size += 1;
}

// Function to insert data at given index
template <typename T>
void SinglyLinkedList<T>::push_at(size_t index, T data)
{
    if (index == 0)
        this->push_front(data); // Insert at front if index is 0
    else if (index <= this->_size - 1)
    {
        SlNode<T> *temp = this->at(index - 1); // Get the node before the index
        SlNode<T> *__next = temp->next;        // Get the node after the index
        temp->next = new SlNode<T>(data);      // Create a new node
        temp->next->next = __next;             // Update the next pointer
        _size += 1;
    }
    else
        index_out_of_range_exception(index, (this->_size == 0) ? 0 : this->_size - 1);
}

// Function to remove data at head of the list
template <typename T>
T SinglyLinkedList<T>::pop_front()
{
    // Check if the list is empty
    if (head == nullptr)
        throw std::out_of_range("List is empty");

    T data = head->data;    // Store the data to be returned
    SlNode<T> *temp = head; // Store the head pointer
    head = head->next;      // Update the head pointer
    delete temp;            // Delete the old head pointer
    _size--;                // Decrement the size of the list

    return data;
}

// Function to remove data at the end of the list
template <typename T>
T SinglyLinkedList<T>::pop_back()
{
    // Check if the list is empty
    if (head == nullptr)
        throw std::out_of_range("List is empty");

    // If the list has only one node, call pop front
    if (head->next == nullptr)
        return this->pop_front();

    SlNode<T> *__itr = this->at(this->size() - 2), *temp = __itr->next;
    T data = __itr->next->data;
    __itr->next = nullptr, this->_size--;
    delete temp;

    return data;
}

// Function to remove data at given index
template <typename T>
T SinglyLinkedList<T>::pop_at(size_t index)
{
    if (index == 0)
        return this->pop_front(); // If index is 0, call pop_front function
    else if (index < this->_size)
    {
        SlNode<T> *__itr = this->at(index - 1), *_tmp = __itr->next->next;
        T data = _tmp->next->data;
        delete __itr->next;
        __itr->next = _tmp, this->_size--;
        return data;
    }
    else if (this->_size == 0)
        throw std::out_of_range("List is empty");
    else
        index_out_of_range_exception(index, (this->_size == 0) ? 0 : this->_size - 1);
}

// Function to delete data at given index (without returning it)
template <typename T>
void SinglyLinkedList<T>::delete_at(size_t index)
{
    if (index == 0)
        this->pop_front(); // If index is 0, call pop_front function
    else if (index < this->_size)
    {
        SlNode<T> *__itr = this->at(index - 1), *_tmp = __itr->next->next;
        delete __itr->next;
        __itr->next = _tmp;
        this->_size--;
    }
    else
        (this->_size == 0) ? throw std::out_of_range("List is empty") : index_out_of_range_exception(index, (this->_size == 0) ? 0 : this->_size - 1);
}

// Function to clear the list (set all data to nullptr)
template <typename T>
void SinglyLinkedList<T>::clear()
{
    // If the list is empty, return
    if (head == nullptr)
        return;

    // Iterate through the list and delete all nodes
    SlNode<T> *temp = head;
    while (temp != nullptr)
    {
        temp->data = (T)NULL;
        temp = temp->next;
    }
}

// Function to check if the list is empty
template <typename T>
bool SinglyLinkedList<T>::empty() const
{
    return head == nullptr;
}

// Function to find the first occurrence of data
template <typename T>
size_t SinglyLinkedList<T>::find(const T &data) const
{
    // Iterate through the list to find the data
    SlNode<T> *__itr = this->head;
    for (size_t i = 0; __itr != nullptr; i++)
    {
        if (__itr->data == data)
            return i;

        __itr = __itr->next;
    }
    return -1; // If the element is not found
}

// Function to check if the list contains given data
template <typename T>
bool SinglyLinkedList<T>::contains(const T &data) const
{
    return this->find(data) != -1;
}

// Function to reverse the list
template <typename T>
void SinglyLinkedList<T>::reverse()
{
    // If the list is empty, return
    if (head == nullptr)
        return;

    // Iterate through the list and reverse the pointers
    SlNode<T> *__itr = this->head;
    SlNode<T> *prev = nullptr;
    SlNode<T> *next;
    while (__itr != nullptr)
    {
        next = __itr->next; // Store the next pointer
        __itr->next = prev; // Update the next pointer to previous
        prev = __itr;       // Update the previous pointer
        __itr = next;       // Update the current pointer
    }

    // Update the head pointer
    head = prev;
}

// Method to sort the singly linked list Change pointers instead of data
template <typename T>
void SinglyLinkedList<T>::sort()
{
    // TODO: Implement the program to sort the singly linked list
}

// Method to erase the given data from the list
template <typename T>
void SinglyLinkedList<T>::erase(const T &data)
{
    if (head == nullptr)
        return;

    if (head->data == data)
        this->pop_front();

    for (SlNode<T> *__itr = this->head, *__temp; __itr->next != nullptr; __itr = __itr->next)
    {
        if (__itr->next->data == data)
        {
            __temp = __itr->next;
            __itr->next = __temp->next;
            delete __temp;
            this->_size--;
        }
    }
}

// Method replace the given data with the new data
template <typename T>
void SinglyLinkedList<T>::replace(const T &data, const T &new_data)
{
    for (SlNode<T> *__itr = this->head; __itr != nullptr; __itr = __itr->next)
    {
        if (__itr->data == data)
            __itr->data = new_data;
    }
}

// Implement function on each node in the list
template <typename T>
template <typename... Args>
void SinglyLinkedList<T>::for_each(void (*func)(SlNode<T> *, Args...), Args... args)
{
    for (SlNode<T> *__itr = this->head; __itr != nullptr; __itr = __itr->next)
        func(__itr, args...);
}