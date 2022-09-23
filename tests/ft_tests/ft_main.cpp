#include <iostream>
#include <fstream>
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

    B.insert(B.end() -1, B.end() - 2, B.end());
    cout << *B.erase(B.end(), B.end() + 1) << endl;

    ft::vector<int>::iterator it = B.begin();
    cout << endl << B.size() << endl;
    for (; it != B.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;

}
void inputf()
{
    ifstream   infile("input");

    ft::vector<char> words;  // vector initialized from input

    words.push_back('x');
    words.push_back('c');
    words.push_back('v');
    words.push_back('b');
    words.push_back('n');

    words.insert(words.begin() + 3, (istreambuf_iterator<char>(infile)), (istreambuf_iterator<char>()));
    
    ft::vector<char>::iterator it = words.begin();
    cout << endl << words.size() << endl;
    for (; it != words.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;
}

void ft_resize()
{
    ft::vector<int> myvector;

    // set some initial content:
    for (size_t i = 1; i < 9; i++) myvector.push_back(i);

    std::cout << myvector.capacity() << '\n';
    myvector.resize(5);
    myvector.resize(8,100);
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
    // ft_tests();
    // inputf();
    // ft_resize();
    ft_swap();
    // system("leaks ftcontainers");

    return(0);
}