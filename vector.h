/**
 * @file vector.h
 * @author Andrea Pizzi (https://github.com/MorkNanoNano/Vector_class)
 * @brief Implementation of STL like vector class
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#ifndef _VECTOR_HEADER_
#define _VECTOR_HEADER_ 

#include <iostream>


namespace myobj{

#ifndef _VECTOR_ITERATOR_HEADER_ 
template<class vector>class random_access_iterator;
template<class vector>class const_random_iterator;
#endif //_VECTOR_ITERATOR_HEADER_


template<typename T>
class vector {   
public:
    typedef T                                               value_type;
    typedef random_access_iterator<vector<T>>               iterator; 
    typedef const T                                         c_value_type;
    typedef const_random_iterator<vector<T>>                const_iterator;
  
public:
	constexpr vector() noexcept;
    constexpr vector(size_t f_size) noexcept;
    constexpr vector(const vector& other) noexcept;
    constexpr vector(std::streampos& strps);
    ~vector();
    void push_back(T&& data) noexcept;
    void push_back(const T& data) noexcept;
    template<typename... Args> 
    T& emplace_back(Args&&... args) noexcept;
    constexpr void reserve(size_t f_size) noexcept;
    void insert(iterator pos, T&);
    void insert(iterator pos, T&&);
    inline void pop_back();
    inline void clear();
    constexpr inline size_t size() const noexcept;
    T& operator[](size_t idx);
    constexpr const T& operator[](size_t idx) const;
    vector<T>& operator=(const vector& other) noexcept;

public: 
    iterator begin() { return iterator(m_data); }
    iterator end() {return iterator(m_data + m_size); }
    const_iterator cbegin() { return const_iterator(m_data); }
    const_iterator cend() { return const_iterator(m_data + m_size); }

private:
 	constexpr void realloc(size_t new_capacity) noexcept;
    void rshift(iterator pos) noexcept;

private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CONSTRUCTOR AND DESTRUCTUR IMPLEMENTATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
constexpr vector<T>::vector() noexcept
    : m_data(nullptr), m_size(0), m_capacity(0) {}

template<typename T>
constexpr vector<T>::vector(size_t f_size) noexcept
    : m_data(static_cast<T*>(::operator new(f_size * sizeof(T)))), m_size(0), m_capacity(f_size) {}

template<typename T>
constexpr vector<T>::vector(std::streampos& strps)
    : m_data(static_cast<T*>(::operator new(strps * sizeof(T)))), m_size(0), 
      m_capacity(reinterpret_cast<int>(strps)) {}
    
template<typename T>
constexpr vector<T>::vector(const vector& other) noexcept
    : m_data(static_cast<T*>(::operator new(other.size() * sizeof(T)))), m_size(other.size()), m_capacity(other.size()){
    for(int i = 0; i < other.size(); i++)
        m_data[i] = std::move(other[i]);
}

template<typename T>
vector<T>::~vector() {
    clear();
    ::operator delete(m_data, m_capacity * sizeof(T));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	PRIVATE REALLOC FUNCTION IMPLEMENTATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
constexpr void vector<T>::realloc(size_t new_capacity) noexcept {
    T* l_ptr = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

    for (size_t i = 0; i < m_size; ++i)
        new (&l_ptr[i]) T(std::move(m_data[i]));

    for (size_t i = 0; i < m_size; ++i)
        m_data[i].~T();

    ::operator delete(m_data, m_capacity * sizeof(T));
    m_data = std::move(l_ptr);
    m_capacity = new_capacity;
}

template<typename T>
void vector<T>::rshift(iterator pos) noexcept {
    if(m_size >= m_capacity)
        this->realloc(m_capacity + 1 + m_capacity/2);

    __int32_t idx = m_size;

    for(auto it = this-> end()-1; it!= pos-1; --it)
        m_data[idx--] = std::move(*it);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  CLASS MEMBER FUNCTION IMPLEMENTATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
void vector<T>::push_back(T&& data) noexcept {
    if (m_size >= m_capacity)
        this->realloc(m_capacity + 1 + m_capacity / 2);

    m_data[m_size] = std::move(data);
    m_size++;
}

template <typename T>
void vector<T>::push_back(const T& data) noexcept {
    if (m_size >= m_capacity)
        this->realloc(m_capacity + 1 + m_capacity / 2);

    m_data[m_size] = data;
    m_size++;
}

template<typename T>
template<typename... Args>
T& vector<T>::emplace_back(Args&&... args) noexcept {
    if (m_size >= m_capacity)
        this->realloc(m_capacity + 1 + m_capacity / 2);

    new(&m_data[m_size]) T(std::forward<Args>(args)...);
    return m_data[m_size++];
}

template<typename T>
constexpr void vector<T>::reserve(size_t f_size) noexcept {
    if(f_size > m_capacity)
        this->realloc(f_size);
}

template<typename T>
void vector<T>::insert(iterator pos, T& val){
    this->rshift(pos);
    *pos = val;
    m_size++;
}

template<typename T>
void vector<T>::insert(iterator pos, T&& val){
    this->rshift(pos);
    *pos = val;
    m_size++;
}

template <typename T>
void vector<T>::pop_back() {
    if (m_size > 0) {
        m_size--;
        m_data[m_size].~T();
    }
}

template<typename T>
void vector<T>::clear() {
    for (size_t i = 0; i < m_size; ++i)
        m_data[i].~T();

    m_size = 0;
}

template<typename T>
constexpr size_t vector<T>::size() const noexcept { return m_size;  }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  CLASS OPERATOR IMPLEMENTATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
T& vector<T>::operator[](size_t idx) { return m_data[idx]; }

template<typename T>
constexpr const T& vector<T>::operator[](size_t idx) const { return m_data[idx]; }

template<typename T>
vector<T>& vector<T>::operator=(const vector& other) noexcept {
    if(this != &other){
        this-> clear(); this-> reserve(other.size());
        for(int i = 0; i < other.size(); i++)
            m_data[i] = std::move(other.m_data[i]);
        this-> m_size = other.size();
    }
    return *this;
}

}  // MYOBJ NAMESPACE END

#endif //_VECTOR_HEADER_
