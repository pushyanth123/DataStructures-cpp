/**
 * @file singlylinkedlist
 * @author pushyanth kamatham
 * @brief This file contains the definitions of SinglyLinkedList data structure
 */


#include "../include/singlylinkedlist.hpp"

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
    // If other list is empty, return
    if (other.head == nullptr)
        return;

    this->head = new SlNode<T>;
    SlNode<T> *__other_ptr = other.head;
    SlNode<T> *__this_ptr = this->head;

    // Copy all nodes into the list
    while (__other_ptr->next != nullptr)
    {
        __this_ptr->data = __other_ptr->data;
        __this_ptr->next = new SlNode<T>;
        __this_ptr = __this_ptr->next;
        __other_ptr = __other_ptr->next;
    }

    __this_ptr->data = __other_ptr->data;

    // Set the size
    this->_size = other._size;
}

// Move constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T> &&other) noexcept
    : head(other.head)
{
    other.head = nullptr;
}

// Initializer list constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const std::initializer_list<T> &list)
{
    // If list is empty, return
    if (list.size() == 0)
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

    _size = list.size();
}

// Destructor
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    if (this->head == nullptr)
        return;

    if (this->head->next == nullptr)
    {
        delete this->head;
        return;
    }

    // Delete all nodes
    SlNode<T> *__next_ptr;
    while (head != nullptr)
    {
        __next_ptr = head->next;
        delete head;
        head = __next_ptr;
    }
}

// Copy assignment operator
template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(const SinglyLinkedList<T> &other)
{
    // First delete all existing data in the singly linked list
    delete this->head;

    // If other list is empty, return
    if (other.head == nullptr)
        return *this;

    // TODO: Complete rest. (Call copy constructor)

    return *this;
}

// Move assignment operator
template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(SinglyLinkedList<T> &&other) noexcept
{
    // First delete all existing data in the singly linked list
    delete this->head;

    // Call move constructor
    this->head = other.head;
    other.head = nullptr;

    return *this;
}

// Overload [] operator to get and set data
template <typename T>
T &SinglyLinkedList<T>::operator[](size_t index)
{
    // Check if index is out of bounds
    if (index < 0 or index >= _size)
        index_out_of_range_exception(index, _size - 1);

    SlNode<T> *temp = this->head;
    while (index--)
        temp = temp->next;

    return temp->data;
}

// Overload [] operator get only
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
    return this->head->operator==(other.head);
}

// Overload "!=" operator to check if two lists are not equal
template <typename T>
bool SinglyLinkedList<T>::operator!=(const SinglyLinkedList<T> &other) const
{
    return !(*this == other);
}

// Overload "+" operator to concatenate two lists
// TODO: Not working properly
template <typename T>
SinglyLinkedList<T> SinglyLinkedList<T>::operator+(const SinglyLinkedList<T> &other) const
{
    // If either list is empty, return the other list
    if (this->head == nullptr)
        return other;
    if (other.head == nullptr)
        return *this;

    // Call copy constructor
    SinglyLinkedList<T> result(*this);
    SinglyLinkedList<T> __temp(other);

    // Append all nodes from the second list
    SlNode<T> *__this_ptr = result.head;

    // Go to last node
    while (__this_ptr->next != nullptr)
        __this_ptr = __this_ptr->next;

    __this_ptr->next = __temp.head;
    result._size += other.size();

    return result;
}

// Overload "<<" operator to print the list
template <typename T>
ostream &operator<<(ostream &os, const SinglyLinkedList<T> &list)
{
    if (list.head == nullptr)
        return os << "List is empty";

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

// Function to get the size of the list
template <typename T>
size_t SinglyLinkedList<T>::size() const
{
    return _size;
}

// Function to insert data at front of the list
template <typename T>
void SinglyLinkedList<T>::insert(const T &data)
{
    // Create a new SlNode
    SlNode<T> *temp = new SlNode<T>(data);
    temp->next = head;

    head = temp; // Update the head pointer
    _size += 1;  // Increment the size of list
}

// Function to insert data at the end of the list
template <typename T>
void SinglyLinkedList<T>::insert_end(const T &data)
{
    // If the list is empty insert at head
    if (head == nullptr)
    {
        head = new SlNode<T>(data);
        _size += 1;
        return;
    }

    // Iterate to the end of the list
    SlNode<T> *temp = head;
    while (temp->next != nullptr)
        temp = temp->next;

    // Add the new node at the end
    temp->next = new SlNode<T>(data);
    _size += 1;
}

// Function to insert data at given index
template <typename T>
void SinglyLinkedList<T>::insert_at(size_t index, T &data)
{
    // Check if the index is valid
    if (index < 0 or index >= this->_size)
        index_out_of_range_exception(index, _size - 1);

    // If the index is 0, call insert function
    if (index == 0)
    {
        this->insert(data);
        return;
    }
    else if (index == _size - 1)
    {
        this->push_back(data);
        return;
    }

    // Create a new SlNode
    SlNode<T> *temp = new SlNode<T>(data);

    // Iterate through the list to reach the index
    SlNode<T> *__itr = this->head;
    while (index--)
        __itr = __itr->next;

    // Update the pointers
    temp->next = __itr->next;
    __itr->next = temp;

    _size++; // Increment the size of the list
}

// Function to remove data head of the list
template <typename T>
T SinglyLinkedList<T>::pop()
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

    // If the list has only one node, call pop function
    if (head->next == nullptr)
        return this->pop();

    // Iterate through the list to reach the end
    SlNode<T> *__itr = this->head;
    while (__itr->next->next != nullptr)
        __itr = __itr->next;

    T data = __itr->next->data; // Store the data to be returned
    delete __itr->next;         // Delete the last node
    __itr->next = nullptr;      // Update the last node pointer
    _size--;                    // Decrement the size of the list

    return data;
}

// Function to remove data at given index
template <typename T>
T SinglyLinkedList<T>::remove_at(size_t index)
{
    // Check if the index is valid
    if (index < 0 or index >= _size)
        index_out_of_range_exception(index, _size - 1);

    // If index == 0, call pop
    if (index == 0)
        return this->pop();
    else if (index == _size)
        return this->pop_back();

    // Iterate through the list to reach the index
    SlNode<T> *__itr = this->head;
    while (--index)
        __itr = __itr->next;

    T data = __itr->next->data;      // Store the data to be returned
    SlNode<T> *temp = __itr->next;   // Store the node to be deleted
    __itr->next = __itr->next->next; // Update the node pointer
    delete temp;                     // Delete the old node
    _size--;                         // Decrement the size of the list

    return data;
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
bool SinglyLinkedList<T>::is_empty() const
{
    return head == nullptr;
}

// Function to find the first occurrence of data
template <typename T>
size_t SinglyLinkedList<T>::find(const T &data) const
{
    // Iterate through the list to find the data
    SlNode<T> *__itr = this->head;
    size_t index = 0;
    while (__itr->next != nullptr)
    {
        if (__itr->data == data)
            return index;
        __itr = __itr->next;
        index++;
    }

    return -1; // If the element is not found
}

// Function to check if the list contains data
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
    // TODO: Need better understanding of this
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
void SinglyLinkedList<T>::sort() {
    // TODO: Implement the program to sort the singly linked list

}
