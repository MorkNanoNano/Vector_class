/**
 * @file vector.h
 * @author Andrea Pizzi (https://github.com/MorkNanoNano/Vector_class)
 * @brief Implementation of some algorithm for vector and iterator class
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once 

#ifndef _ALGORITHM_HEADER_
#define _ALGORITHM_HEADER_

#include <fstream>
#include <iostream>
#include <sstream>

#ifndef _RANGE_HEADER_
#include "range.h"
#endif //_RANGE_HEADER_

namespace myobj{

#ifndef _VECTOR_HEADER_
template<typename T> class vector;
#endif //_VECTOR_HEADER_

#ifndef _VECTOR_ITERATOR_HEADER_
template<class vector>class random_access_iterator;
template<class vector>class const_random_iterator;
#endif //_VECTOR_ITERATOR_HEADER_


namespace algorithm{

template<typename T> 
void fload(const std::string&, vector<T>&);

// template<class Iter>
// static vector<typename Iter::value_type> inplace_merge(Iter, Iter, Iter);

// template<class Iter>
// void merge_sort(Iter, Iter);

template<class Iter>
void sort(Iter, Iter);

template<class vector>
void bubble_sort(vector&);

template<typename T>
double sum(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>);

template<typename T>
void sprint(vector<T>&, std::stringstream);

template<typename T>
void tprint(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>);

template<typename T>
void fprint(vector<T>&, const std::string&);

template<typename T>
T minval(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>);

template<typename T>
T maxval(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ALGORITHM FUNTION IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> 
void fload(const std::string& filename, myobj::vector<T>& vec){
    if(std::ifstream in{filename, std::ios::binary | std::ios::ate}){
        std::streampos size = in.tellg();
        in.seekg(0, std::ios::beg);
        vec.reserve(size); T val = 0; 
        while(in >> val) vec.emplace_back(val);
        in.close();
        vec.shrink_to_fit();
    }
}

// template<class Iter>
// static vector<typename Iter::value_type> inplace_merge(Iter begin, Iter mid, Iter end){
//     vector<typename Iter::value_type> buffer(ranges::distance(begin, end));
//     Iter left(begin); Iter right(mid);

//     while(left != mid && right != end)
//         buffer.push_back(std::move((*left > *right) ? *right++ : *left++));
    
//     if(left != mid)
//         buffer.insert(buffer.end(), left, mid);
//     else    
//         buffer.insert(buffer.end(), right, end);

//     return buffer;
// }

// template<class Iter>        
// void merge_sort(Iter begin, Iter end){
//        if(ranges::distance(begin, end)  > 1){
//         typename Iter::difference_type diff = ranges::distance(begin, end) / 2;
//         Iter mid = ranges::advance(begin, diff);
//         merge_sort(begin, mid);
//         merge_sort(mid+1, end);
//         vector<typename Iter::value_type> out(std::move(inplace_merge(begin, mid, end)));    
//         std::move(out.begin(), out.end(), begin);  
//     }
// }

template<typename Iter>
void sort(Iter begin, Iter end){
    vector<typename Iter::value_type> buffer(ranges::distance(begin, end));
    Iter left = begin; Iter right = end-1;

    while(left != right)
        buffer.emplace_back(std::move((*left < *right) ? *left++ : *right--));
    buffer.emplace_back(std::move(*right));

    std::move(buffer.begin(), buffer.end(), begin);  
}

template<class vector>
void buuble_sort(vector& vec){
    for(auto previous = vec.begin(); previous != vec.end()-1; ++previous){
        for(auto next = previous+1; next != vec.end(); ++next){
            if(*next < *previous){
                typename vector::value_type tmp = *previous;
                *previous = * next;
                *next = tmp;
            }
        }
    }
}

template<typename T >    
double sum(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last){
    double out = 0; 
    for(auto it = first; it != last; ++it)
        out += *it;
    return out;
}

template<typename T>
void sprint(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last, std::stringstream strm){
    for(; first != last; ++first)
        strm << *first << "\n";
    strm << std::endl;
}

template<typename T>
void tprint(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last){
    for(; first != last; ++first)
        std::cout << *first << "\n";
    std::cout << std::endl;
}

template<typename T>
void fprint(vector<T>& vec , const std::string& filename){
    std::ofstream out(filename, std::ios::binary);
    out.write(vec, vec.size());
    out.close();
}

template<typename T>
T minval(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last){
    T m_val = *first;
    for(first+1 ; first != last; ++first){
        if(*first < m_val)
            m_val = *first;
    }
    return m_val;
}

template<typename T>
T maxval(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last){
    T m_val = *first;
    for(first+1 ; first != last; ++first){
        if(*first > m_val)
            m_val = *first;
    }
    return m_val;
}

}  //ALGORITHM NAMESPACE END
}  //MYOBJ NAMESPACE END

#ifndef _STATISTICS_HEADER_
#include "statistics.h"
#endif //_STATISTICS_HEADER_

#endif //_ALGORITHM_HEADER_ 
