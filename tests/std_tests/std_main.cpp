#include <iostream>
// #include <iterator>
#include "../../doc/__wrap_iter.hpp"
#include "../../doc/cluv.hpp"
// #include <vector>

void std_tests()
{
    std::vector<int> B;

    B.push_back(1);
    std::cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    std::cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    std::cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    std::cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    std::cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    std::cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    std::cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    std::cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    std::cout << B.capacity();
    
    std::cout << std::endl << B.max_size() << std::endl;

    B.insert(B.end() -3, 2, -2);
    std::vector<int>::iterator it = B.begin();
    std::cout << std::endl << B.size() << std::endl;
    for (; it != B.end(); it++)
    {
        std::cout << *it << " ";
    }

    std::cout << std::endl;
}


int main()
{
    std_tests();
    // system("leaks stdcontainers");

    return(0);
}