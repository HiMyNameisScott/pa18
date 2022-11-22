 /// @file ForwardList.hpp
 /// @author Scott T. Koss
 /// @date 11/15/2022
 /// @note I pledge my word of honor that I have complied with the
 /// CSN Academic Integrity Policy while completing this assignment.
 /// @brief template class for ForwardList
 /// @note 6-8 hours

#ifndef HPP_FORWARDLIST
#define HPP_FORWARDLIST
#include <iterator>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <cassert>

/// ---------------------------------------------------------------------------
/// A ForwardList is a container that supports fast insertion and removal of
/// elements from anywhere in the container. Fast random access is not
/// supported. It is implemented as a singly-linked list.
///
/// Adding, removing, and moving the elements within the list, or across several
/// lists, does not invalidate the iterators currently referring to other
/// elements in the list. However, an iterator or reference referring to an
/// element is invalidated when the corresponding element is removed (via
/// erase()) from the list.
/// ---------------------------------------------------------------------------
template <class T>
class ForwardList
{
protected:
    /// A ForwardList node.
    struct Node
    {
        T info{};               // initial node
        Node *link{};           // initial node link
    };

public:
    /// An iterator for ForwardList containers.
    class Iterator
    {
    public:
        // member types (required to integrate with standard library)
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;                               //  data type
        using difference_type = std::ptrdiff_t;
        using pointer = Node *;                             //  node data type for pointer
        using reference = value_type &;                     //  derefence the data

        Iterator(pointer ptr = nullptr) : current(ptr) {}   
        reference operator*() const { return current->info; }
        pointer operator->() { return current; }
        Iterator &operator++()
        {
            current = current->link;
            return *this;
        }

        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs.current == rhs.current;
        }

        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs.current != rhs.current;
        }

    private:
        pointer current; ///< The current node.
    };

    // member types
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type &;
    using iterator = Iterator;

    // ctors
    ForwardList();
    ForwardList(const ForwardList &other);
    ForwardList(const std::initializer_list<value_type> &ilist);
    // dtor
    virtual ~ForwardList();
    // copy assignment
    ForwardList &operator=(const ForwardList &rhs);

    // iterators
    iterator begin() const { return iterator(first); }
    iterator end() const { return iterator(last); }

    // capacity
    bool empty() const { return begin() == end(); }
    size_type size() const { return count; }

    /// Clears the contents
    void clear();
    /// Inserts a value before pos
    iterator insert(iterator pos, const value_type &value);
    /// Erases an element at pos
    iterator erase(iterator pos);

protected:
    Node *first{};     ///< pointer to the head node
    Node *last{};      ///< pointer to the tail node
    size_type count{}; ///< number of nodes in list
};

/** NON-MEMBER FUNCTIONS **/

/// Equality comparison operator.
template <class T>
bool operator==(const ForwardList<T> &lhs, const ForwardList<T> &rhs);

/// Inequality comparison operator.
template <class T>
bool operator!=(const ForwardList<T> &lhs, const ForwardList<T> &rhs);

// ctors
template <class T>
ForwardList<T>::ForwardList()
{
    first = nullptr;        // default values for initial nodes
    count = 0;
};

template <class T>
ForwardList<T>::ForwardList(const ForwardList &other)
{
    *this = other;          // copies this to other list with copy assignment
};


template <class T>
ForwardList<T>::ForwardList(const std::initializer_list<T> &ilist){
    if (ilist.size() > 0) {
        Node* last{};
        typename std::initializer_list<T>::iterator it = ilist.begin();

        first = new Node{ *it, nullptr};
        last = first;

        for (++it; it != ilist.end(); ++it){
            last->link = new Node{ *it, nullptr };
            last = last->link;
        }

        count = ilist.size();
    }
};

// dtor
template <class T>
ForwardList<T>::~ForwardList(){ clear(); };

// copy assignment
template <class T>
ForwardList<T> &ForwardList<T>::operator=(const ForwardList<T>& rhs)
{
  if (this != &rhs ){
    while (size() <rhs.size()) {
        insert(begin(), 0);
    }

    while (size() > rhs.size()){
        erase(begin());
    }

    std::copy(rhs.begin(), rhs.end(), begin());
  }

  return *this;
};

/// Clears the contents
template <class T>
void ForwardList<T>::clear()
{
    while (!empty()) {
        erase(begin());
    }

    assert(first == nullptr);
    assert(count == 0);
};

/// Inserts a value before pos
template <class T>
typename ForwardList<T>::iterator ForwardList<T>::insert(ForwardList<T>::iterator pos, const ForwardList<T>::value_type &value)
{
   Node *node = new Node{value, nullptr};   // Node to become inserted

   if(empty() || pos == nullptr) {
    
        node->link = first;
        first = node;

   } else if (pos == end()){
        last->link = node;
        last = node;

   } else {
        // Will insert somewhere in the list
        Node* previous = first;         // trailer
        Node* current = first->link;    // traversal

        // traverse the list, looking for node before pos
        while (current != nullptr && current != pos.operator->()) {
            previous = current;
            current = current->link;
        }
        // insert new node before pos
        node->link = previous->link;
        previous->link = node;
   }

        count ++;
   
   return iterator{ node };
};

/// Erases an element at pos
template <class T>
typename ForwardList<T>::iterator ForwardList<T>::erase(ForwardList<T>::iterator pos){
    if (empty()) {
        pos = end();                    // no elements exist
    } else if (pos == begin()) {
        //case 1: item to be deleted is first node of the list
        const Node* tmp = first;        // temp pointer for removal
        pos = iterator(first->link);    // node follownig erased one
        first = first->link;            // update first pointer
        delete tmp;                     // reclaim memory
        --count;                        // lower count 
    } else {
        //case 2: item to be deleted is somewhere in the list
        Node* previous = first;             // trailing pointer
        Node* current = first->link;        // traversal pointer

        // this loop will trail the list looking for the node before pos
        while (current != nullptr && current != pos.operator->()) {
            previous = current;             
            current = current->link;
        }

        if (current != nullptr){
            pos = iterator(current->link);  // node following the erased node
            previous->link = current->link; // remove the node from the list
            delete current;                 // reclaim mem
            current = nullptr;              // no dangling pointers
            --count;

        }
        
    }

    return pos;
};

/** NON-MEMBER FUNCTIONS **/

/// Equality comparison operator.
template <class T>
bool operator==(const ForwardList<T> &lhs, const ForwardList<T> &rhs){
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};

/// Inequality comparison operator.
template <class T>
bool operator!=(const ForwardList<T> &lhs, const ForwardList<T> &rhs){
    return !(lhs == rhs);
};

#endif
