/**
 * @file iterator.h
 * @author Andrea Pizzi (https://github.com/MorkNanoNano/Vector_class)
 * @brief Implementation of an iterator
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#ifndef _VECTOR_ITERATOR_HEADER_
#define _VECTOR_ITERATOR_HEADER_

#include <iostream>

namespace myobj{

#ifndef _VECTOR_HEADER_
template<typename T> class vector;
#endif //_VECTOR_HEADER_


template<class vector>
class random_access_iterator{
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = typename vector::value_type;
    using pointer = value_type*;
    using reference = value_type&;

public:
    random_access_iterator() noexcept : m_ptr(nullptr) {}
    random_access_iterator(pointer ptr) noexcept : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }
    reference operator[](int indx) { return *(m_ptr + indx); }
    random_access_iterator& operator++()noexcept { m_ptr++; return *this; }
    random_access_iterator operator++(int) noexcept { random_access_iterator tmp = *this; ++(*this); return tmp; }
    random_access_iterator& operator--() noexcept { m_ptr--; return *this; }
    random_access_iterator operator--(int) noexcept { random_access_iterator tmp = *this; --(*this); return tmp; }
    difference_type operator-(const random_access_iterator& other) { return m_ptr - other.m_ptr; }
    random_access_iterator operator+(const difference_type& offset) { 
        auto old = m_ptr; m_ptr += offset; auto tmp(*this); m_ptr = old; return tmp; }
    random_access_iterator operator-(const difference_type& offset) { 
        auto old = m_ptr; m_ptr -= offset; auto tmp(*this); m_ptr = old; return tmp; }

    bool operator==(const random_access_iterator& other) { return m_ptr == other.m_ptr; }
    bool operator!=(const random_access_iterator& other) { return !(*this == other); }

private:
    pointer m_ptr;
};

template<class vector>
class const_random_iterator{
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = typename vector::c_value_type;
    using pointer = value_type*;
    using reference = value_type&;

public:
    const_random_iterator() noexcept : c_ptr(nullptr) {}
    const_random_iterator(pointer ptr) noexcept : c_ptr(ptr) {}

    reference operator*() const { return *c_ptr; }
    pointer operator->() { return c_ptr; }    
    const_random_iterator& operator++() noexcept { c_ptr++; return *this; }
    const_random_iterator operator++(int) noexcept { const_random_iterator tmp = *this; ++(*this); return tmp; }
    const_random_iterator& operator--() noexcept { c_ptr--; return *this; }
    const_random_iterator operator--(int) noexcept { const_random_iterator tmp = *this; --(*this); return tmp; }

    bool operator==(const const_random_iterator& other) { return c_ptr == other.c_ptr; }
    bool operator!=(const const_random_iterator& other) { return !(*this == other); }

private:
    pointer c_ptr;
};

}  //MYOBJ NAMESPACE END

#endif //_VECTOR_ITERATOR_HEADER_
