#include "iterator.h"
#include "vector.h"
#include "algorithm.h"

int main(){

    myobj::vector<double> vec;

    myobj::algorithm::fload("data.dat", vec);
    vec.insert(vec.begin()+3, 10);


    myobj::ranges::for_each(vec.begin(), vec.end(), [](auto&& x)-> void { std::cout << x*x << std::endl;});
    std::cout << myobj::ranges::count_if(vec.begin(), vec.end(), [](auto&& x)-> bool { if(x = 33.1164){return true;} return false;}) << std::endl;
   
    myobj::random_access_iterator<myobj::vector<double>> idx = myobj::ranges::find(vec.begin(), vec.end(), 33.1164);

    std::cout << *idx << std::endl;

    std::cin.get();
}
