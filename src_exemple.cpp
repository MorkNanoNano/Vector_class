#include "iterator.h"
#include "vector.h"
#include "algorithm.h"

void print(int* ptr){
    for(int i = 0; i < 1; i++)
        std::cout << ptr[i] << std::endl;
}

int main(){

    myobj::vector<int> vec;
    myobj::algorithm::fload("test.data", vec);  

    myobj::algorithm::sort(vec.begin(), vec.end());

    for(auto& val : vec)
        std::cout << val << std::endl;

    auto lambda = [](auto& val)->bool { if(val < 5 && val >3) return true; return false; };

    myobj::vector<int> out;
    myobj::ranges::for_each(vec.begin(), vec.end(), [&out, &lambda](auto& val)->void { if(lambda(val)) out.emplace_back(val); });

    print(out.data());

    std::cin.get();
}

