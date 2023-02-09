/**
 * @file statistic.h
 * @author Andrea Pizzi (https://github.com/MorkNanoNano/Vector_class)
 * @brief Implementation of statisics function
 * @version 0.1
 * @date 2023-02-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once 

#ifndef _STATISTICS_HEADER_
#define _STATISTICS_HEADER_

#include <cmath>

namespace myobj{    

#ifndef _VECTOR_HEADER_
template<typename T> class vector;
#endif //_VECTOR_HEADER_

#ifndef _VECTOR_ITERATOR_HEADER_
template<class vector>class random_access_iterator;
template<class vector>class const_random_iterator;
#endif //_VECTOR_ITERATOR_HEADER_

namespace statistics{

template<class Iter>
double euclid_dist(Iter, Iter);

template<class Iter>
double euclid_dist(Iter, Iter, Iter, Iter);

template<class Iter>
double std_dev(Iter, Iter);

template<class Iter>
double std_dev(Iter, Iter, double);

/////////////////////////////////////////////////////////////////////////////////////////////////
// STATISTICS FUNCTION IMPLEMENTATION
/////////////////////////////////////////////////////////////////////////////////////////////////

template<class Iter>
double euclid_dist(Iter first, Iter second){
    return(sqrt(pow(*second.x - *first.x), 2) + pow((*second.y - *first.y), 2));
}

template<class Iter>
double euclid_dist(Iter x_first, Iter x_second, Iter y_first, Iter y_second){
    return(sqrt(pow((*x_second - *x_first), 2) + pow((*y_second - *y_first), 2)));
}

template<class Iter>
double std_dev(Iter begin, Iter end){
    typename Iter::difference_type n_elem = ranges::distance(begin, end);
    double mean = algorithm::sum(begin, end) / n_elem;
    double diff_sum = 0; 

    for( ; begin != end; ++begin)
        diff_sum += pow((*begin - mean), 2);
        
    return sqrt(diff_sum / n_elem-1);
}

template<class Iter>
double std_dev(Iter begin, Iter end, double mean){
    typename Iter::difference_type n_elem = ranges::distance(begin, end);
    double diff_sum = 0; 
    
    for( ; begin != end; ++begin)
        diff_sum += pow((*begin - mean), 2);
    
    return sqrt(diff_sum / n_elem-1);
}


}   //NAMESPACE STATISTICS END
}   //NAMESPACE MYOBJ END

#endif //_STATISTICS_HEADER_
