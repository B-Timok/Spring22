/// @file Container.hpp
/// @author Brandon Timok <8000477724@student.csn.edu>
/// @date 03/14/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief A Container stores a set of values The storage of the Container is
/// handled automatically, being expanded as needed.

#ifndef CONTAINER_HPP
#define CONTAINER_HPP
#include <initializer_list>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <stdexcept>
#include <algorithm>

/// A Container that stores a set of values. The storage of the Container is
/// handled automatically, being expanded as needed.

template <class T>
class Container {
public:
    /// Member types.
    using value_type    = T;
    using size_type     = std::size_t;
    using pointer       = value_type*;
    using const_pointer = const value_type*;
    
    /// Default ctor.
    Container(size_type count = 0);
    
    /// Copy ctor.
    Container(const Container& other);

    /// Move ctor.
    Container(Container&& other)
    : capacity(std::exchange(other.capacity, 0)),
      used(std::exchange(other.used, 0)),
      data(std::exchange(other.data, nullptr)) {}
    
    /// Initializer List ctor
    Container(const std::initializer_list<value_type>& init);

    /// Destructor.
    ~Container() { delete [] data; }
    
    /// Checks if the container has no elements, e.g begin() == end()
    /// @returns true if the container is empty, false otherwise.
    bool empty() const { return begin() == end(); }
    
    /// Returns the number of elements in the container.
    size_type size() const { return used; }
    
    /// Returns a pointer to the first element.
    pointer begin() { return data; }
    const_pointer begin() const { return data; }
    
    /// Returns a pointer to the end (the element following the last element).
    pointer end() { return begin() + size(); }
    const_pointer end() const { return begin() + size(); }
    
    /// Adds an element to the end.
    void push_back(const value_type& value);
    
    /// Removes a single item from the container.
    void erase(pointer pos);
    
    /// After this call, size() returns zero. The capacity remains unchanged.
    void clear() { used = 0; }

    /// Exchanges the contents of the container with those of other.
    void swap(Container& other);
    
    /// Finds the first element equal to the given target. Search begins at pos. 
    /// @returns pointer to the element if found, or end() if not found.
    pointer find(const value_type& target, pointer pos = nullptr);

    /// Replaces the contents of the container with a copy of the contents of rhs.
    Container& operator=(const Container& rhs);

    /// Moves the contents of the container instead of replacing.
    Container& operator=(Container&& rhs);

    /// Returns other appended to this.
    /// @returns this
    Container& operator+=(const Container& other);

    /// Returns the value at the index chosen.
    /// Checks for out of bounds.
    T& at(size_type pos);
    const T& at(size_type pos) const;
    
    /// Returns the value at the index chosen.
    /// Does not check for bounds.
    T& operator[](size_type pos) { return *(begin() + pos); }
    const T& operator[](size_type pos) const { return *(begin() + pos); }


private:
    size_type capacity;  ///< Physical capacity of container.
    size_type used;      ///< Number of items in container.
    pointer   data;      ///< Array of items.
};
    
// related non-member functions
    
/// Equality comparison operator.
/// @returns true if lhs compares equal to rhs, otherwise false
template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs);

/// Inequality comparison operator.
/// @returns true if lhs does not compare equal to rhs, otherwise false
template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs);

/// Returns the concatenation of lhs and rhs.
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs);

/// Writes a formatted representation of rhs to output.
/// @returns output
template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset);

// ============================================================================

template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs);

template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs);

template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs);

template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset);

/// Default ctor.
template <class T>
Container<T>::Container(size_type count) {
    data = new value_type[count];
    used = 0;
    capacity = count;
}

/// Copy ctor.
template <class T>
Container<T>::Container(const Container<T>& other) 
: Container<T>(other.size()) {
    std::copy(other.begin(), other.end(), begin());
    used = other.size();
}

/// Initializer List ctor
template <class T>
Container<T>::Container(const std::initializer_list<value_type>& init) 
: Container<T>(init.size()) {
    std::copy(init.begin(), init.end(), begin());
    used = init.size();
}

///
template <class T>
T& Container<T>::at(size_type pos) {
    if (pos > used) {
        throw std::out_of_range("Out of bounds");
    }
    return data[pos];
}

///
template <class T>
const T& Container<T>::at(size_type pos) const {
    if (pos > used) {
        throw std::out_of_range("Out of bounds");
    }

    return data[pos];
}

/// Adds an element to the end.
template <class T>
void Container<T>::push_back(const value_type& value) {
    if (size() == capacity) {
        // make a new dynamic array of sufficient size (capacity +8)
        pointer temp = new value_type[capacity += 8];

        // copy elements from data to new temp array
        std::copy(begin(), end(), temp);

        // delete the old data array
        delete [] data;

        // reassign data pointer to the temp array
        data = temp; 
    }

    *(data + used++) = value;
}

/// Removes a single item from the container.
template <class T>
void Container<T>::erase(pointer pos) {
    if (pos != nullptr) {
        if (pos < begin() || pos > end()) {
            throw std::out_of_range("Out of bounds");
        }
        // assert(pos >= begin());
        // assert(pos < end());
        std::copy(pos + 1, end(), pos);
        --used;
    }
}

/// Exchanges the contents of the container with those of other.
template <class T>
void Container<T>::swap(Container<T>& other) {
    std::swap(capacity, other.capacity);
    std::swap(used, other.used);
    std::swap(data, other.data);
}

/// Finds the first element equal to the given target. Search begins at pos. 
/// @returns pointer to the element if found, or end() if not found.
template <class T>
typename Container<T>::pointer 
Container<T>::find(const value_type& target, pointer pos) {
    auto first = pos == nullptr ? begin() : pos;
    return std::find(first, end(), target);
}

/// Replaces the contents of the container with a copy of the contents of rhs.
template <class T>
Container<T>& Container<T>::operator=(const Container<T>& rhs) {
    if (this != &rhs) {
        // deallocate any memory that Container is using internally
        delete [] data;
        data = nullptr;
        used = 0;
        // allocate memory to hold the contents of rhs
        data = new value_type[rhs.size()];
        used = rhs.size();
    }
    // copy the values from rhs into this instance
    std::copy(rhs.begin(), rhs.begin() + rhs.size(), begin());
    used = capacity = rhs.size();

    return *this;
}

// Move assignment operator
template <class T>
Container<T>& Container<T>::operator=(Container<T>&& rhs) {
    if (this != &rhs) {
        capacity = std::exchange(rhs.capacity, 0);
        used = std::exchange(rhs.used, 0);
        data = std::exchange(rhs.data, data);
    }
    return *this;
}

/// Returns other appended to this.
/// @returns this
template <class T>
Container<T>& Container<T>::operator+=(const Container<T>& other) {
    if (size() + other.size() > capacity) {
        capacity = size() + other.size();
        pointer temp = new value_type[capacity];
        
        std::copy(begin(), end(), temp);
        
        delete [] data;
        data = temp;
    }
    std::copy(other.begin(), other.end(), end());
    used = size() + other.size();

    return *this;
}

// related non-member functions
            
/// Equality comparison operator.
/// @returns true if lhs compares equal to rhs, otherwise false
template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/// Inequality comparison operator.
/// @returns true if lhs does not compare equal to rhs, otherwise false
template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs) {
    return !std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/// Returns the concatenation of lhs and rhs.
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs) {
    Container<T> box(lhs);
    
    box += rhs;
    return box;
}

/// Writes a formatted representation of rhs to output.
/// @returns output
template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset) {
    char separator[2] = "";

    output << '{';

    for (const typename Container<T>::value_type& item : oset) {
        output << separator << item;
        *separator = ',';
    }

    output << '}';

    return output;
}

#endif /* CONTAINER_HPP */

/* EOF */
