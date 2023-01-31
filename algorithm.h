#pragma once 

#ifndef _ALGORITHM_HEADER_
#define _ALGORITHM_HEADER_

#include <fstream>
#include <sstream>
#include "range.h"

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

// template<typename Iter>
// static void merge(Iter, Iter, Iter);

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
    }
}

template<typename T> 
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

#endif //_ALGORITHM_HEADER_
