#include <iostream>
#include "../../doc/__wrap_iter.hpp"
#include "../../doc/cluv.hpp"
#include "../../src/vector_iterator.hpp"
// #include <vector>
#include "../../src/vector.hpp"

using namespace std;

void ft_tests()
{
    ft::vector<int> B;
    
    B.push_back(1);
    cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    cout << B.capacity();
    B.push_back(*(B.end()-1) + B.size());
    cout << B.capacity();
    
    cout << endl << B.max_size() << endl;

   B.insert(B.end() -3 , 2, -2);

    ft::vector<int>::iterator it = B.begin();
    cout << endl << B.size() << endl;
    for (; it != B.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;
}


int main()
{
    ft_tests();
    // system("leaks ftcontainers");

    return(0);
}