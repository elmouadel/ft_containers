#include <iostream>
#include <iterator>
#include "../../doc/cluv.hpp"
// #include <vector>
int main()
{
    std::vector<int, std::allocator<int> > A;
    std::vector<int, std::allocator<int> > a;

    A.push_back(1);
    A.push_back(2);
    A.push_back(3);
    a = A;
    std::vector<int>::iterator it = A.begin();
    std::vector<int>::iterator itt = a.begin();
    // itt = 1 + it;
    std::cout << *it;
    std::cout << *itt;
    return(0);
}