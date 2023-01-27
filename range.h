#pragma once 

#ifndef _RANGE_HEADER_
#define _RANGE_HEADER_

namespace myobj{

#ifndef _VECTOR_HEADER_
template<typename T> class vector;
#endif //_VECTOR_HEADER_

#ifndef _VECTOR_ITERATOR_HEADER_
template<class vector>class random_access_iterator;
template<class vector>class const_random_iterator;
#endif //_VECTOR_ITERATOR_HEADER_


namespace ranges{

template<typename T, class Pred>
bool all_of(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>, Pred&&);

template<typename T, class Pred>
bool any_of(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>, Pred&&);

template<typename T, class Pred>
bool none_of(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>, Pred&&);

template<typename T, class Action>
void for_each(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>, Action&&);

template<typename T>
__int32_t count_if(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>, T);

template<typename T, class Pred>
__int32_t count_if(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>, Pred&&);

template<typename T>
random_access_iterator<vector<T>> find(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>, T);

template<typename T, class Pred>
random_access_iterator<vector<T>> find_if(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>, Pred&&);

template<typename T, class Pred>
random_access_iterator<vector<T>> find_if_not(random_access_iterator<vector<T>>, random_access_iterator<vector<T>>, Pred&&);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RANGES FUNCTION IMPLEMENTATION
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, class Pred>
bool all_of(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last, Pred&& pred){
    if(first == last) return true;
    for( ; first != last; ++first)
        if(!pred(*first))
            return false;
    return true;
}

template<typename T, class Pred>
bool any_of(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last, Pred&& pred){
    if(first == last) return false;
    for( ; first != last; ++first)
        if(pred(*first))
            return true;
    return false;
}

template<typename T, class Pred>
bool none_of(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last, Pred&& pred){
    if(first == last) return true;
    for( ; first != last; ++first)
        if(pred(*first))
            return false;
    return true;
}

template<typename T, class Action>
void for_each(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last, Action&& action){
    for( ; first != last; ++first)
        action(*first);
}

template<typename T>
__int32_t count_if(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last, T element){
    __int32_t count = 0; 
    for( ; first != last; ++first)
        if(*first == element)
            count++;
    return count;
}

template<typename T, class Pred>
__int32_t count_if(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last, Pred&& pred){
    __int32_t count = 0; 
    for( ; first != last; ++first)
        if(pred(*first))
            count++;
    return count;
}

template<typename T>
random_access_iterator<vector<T>> find(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last, T element){
    for( ; first != last; ++first)
        if(*first == element)
            return first;
    return last;
}

template<typename T, class Pred>
random_access_iterator<vector<T>> find_if(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last, Pred&& pred){
    for( ; first != last; ++first)
        if(pred(*first))
            return first; 
    return last;
}

template<typename T, class Pred>
random_access_iterator<vector<T>> find_if_not(random_access_iterator<vector<T>> first, random_access_iterator<vector<T>> last, Pred&& pred){
    for( ; first != last; ++first)
        if(!pred(*first))
            return first;
    return last;   
}

} // RANGES NAMESPACE END
} // MYOBJ NAMESPACE END

#endif //_RANGE_HEADER_
