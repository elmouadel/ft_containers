#include <iostream>
#include "../../doc/__wrap_iter.hpp"
#include "../../doc/cluv.hpp"
#include "../../src/vector_iterator.hpp"
// #include <vector>
// #include "../../doc/vappc.hpp"
#include "../../src/vector.hpp"

    int main()
{
    std::vector<int> A;
    std::vector<char, std::allocator<char> > a;

    A.push_back(1);
    A.push_back(2);
    A.push_back(3);
    // int B[3] = {1 , 2, 3};
    // ft::v_iterator<int*> it(B);
    // ft::v_iterator<int*> itt;
    // itt = 1 + it;
    // std::cout << *it;
    // std::cout << *itt;
    // if (it != itt)
    //     std::cout << "ok\n";
    return(0);
}