#include <iostream>
#include <fstream>
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

    B.insert(B.end() -1, B.end() - 2, B.end());
    std::cout << *B.erase(B.end(), B.end() + 1) << std::endl;

    std::vector<int>::iterator it = B.begin();
    std::cout << std::endl << B.size() << std::endl;
    for (; it != B.end(); it++)
    {
        std::cout << *it << " ";
    }

    std::cout << std::endl;
}


void inputf()
{
    using namespace std;
    ifstream   infile("input");

    vector<char> words;  // vector initialized from input

    words.push_back('x');
    words.push_back('c');
    words.push_back('v');
    words.push_back('b');
    words.push_back('n');

    words.insert(words.begin() + 3, (istreambuf_iterator<char>(infile)), (istreambuf_iterator<char>()));
    
    vector<char>::iterator it = words.begin();
    cout << endl << words.size() << endl;
    for (; it != words.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;
}


void ft_resize()
{
    std::vector<int> myvector;

    // set some initial content:
    for (size_t i = 1; i < 9; i++) myvector.push_back(i);

    myvector.resize(5);
    myvector.resize(8,100);
    std::cout << myvector.capacity() << '\n';
    myvector.resize(12);
    myvector.resize(37);
    std::cout << myvector.capacity() << '\n';

    std::cout << "myvector contains:";
    for (size_t i=0;i<myvector.size();i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';

}

void ft_swap()
{
    std::vector<int> foo (3,100);   // three ints with a value of 100
    std::vector<int> bar (5,200);   // five ints with a value of 200

    foo.swap(bar);

    std::cout << "foo contains:";
    for (size_t i=0; i<foo.size(); i++)
        std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (size_t i=0; i<bar.size(); i++)
        std::cout << ' ' << bar[i];
    std::cout << '\n';

}


int main()
{
    // std_tests();
    // inputf();
    // ft_resize();
    ft_swap();
    // system("leaks stdcontainers");

    return(0);
}