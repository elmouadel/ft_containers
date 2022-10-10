#include <iostream>
// #include <fstream>
// #include "../../doc/__wrap_iter.hpp"
// #include "../../doc/cluv.hpp"
#include <vector>
#include "../../src/vector.hpp"
#include "../../src/map.hpp"

using namespace std;

// void ft_tests()
// {
//     ft::vector<int> B(1, 2);
    
//     B.push_back(1);
//     cout << B.capacity();
//     B.push_back(*(B.end()-1) + B.size());
//     cout << B.capacity();
//     B.push_back(*(B.end()-1) + B.size());
//     cout << B.capacity();
//     B.push_back(*(B.end()-1) + B.size());
//     cout << B.capacity();
//     B.push_back(*(B.end()-1) + B.size());
//     cout << B.capacity();
//     B.push_back(*(B.end()-1) + B.size());
//     cout << B.capacity();
//     B.push_back(*(B.end()-1) + B.size());
//     cout << B.capacity();
//     B.push_back(*(B.end()-1) + B.size());
//     cout << B.capacity();
//     B.push_back(*(B.end()-1) + B.size());
//     cout << B.capacity();
    
//     cout << endl << B.max_size() << endl;

//     ft::vector<int> A;
//     A.assign(B.begin(), B.end());

//     ft::vector<int>::iterator it = A.begin();
//     if (B.rbegin() != A.rbegin())
//         cout << endl << A.size() << *A.rbegin() << endl;
//     for (; it != A.end(); ++it)
//     {
//         cout << *it << " ";
//     }

//     cout << endl;

// }
// void inputf()
// {
//     ifstream   infile("input");

//     ft::vector<char> words;  // vector initialized from input

//     words.push_back('x');
//     words.push_back('c');
//     words.push_back('v');
//     words.push_back('b');
//     words.push_back('n');

//     words.insert(words.begin() + 3, (istreambuf_iterator<char>(infile)), (istreambuf_iterator<char>()));
    
//     ft::vector<char>::iterator it = words.begin();
//     cout << endl << words.size() << endl;
//     for (; it != words.end(); ++it)
//     {
//         cout << *it << " ";
//     }

//     cout << endl;
// }

// void ft_resize()
// {
//     ft::vector<int> myvector;

//     // set some initial content:
//     for (size_t i = 1; i < 9; i++) myvector.push_back(i);

//     std::cout << myvector.capacity() << '\n';
//     myvector.resize(5);
//     myvector.resize(8,100);
//     myvector.resize(12);
//     myvector.resize(37);
//     std::cout << myvector.capacity() << '\n';

//     std::cout << "myvector contains:";
//     for (size_t i=0;i<myvector.size();i++)
//       std::cout << ' ' << myvector[i];
//     std::cout << '\n';

// }

// void ft_swap()
// {
//     std::vector<int> foo (3,100);   // three ints with a value of 100
//     std::vector<int> bar (5,200);   // five ints with a value of 200

//     foo.swap(bar);

//     std::cout << "foo contains:";
//     for (size_t i=0; i<foo.size(); i++)
//         std::cout << ' ' << foo[i];
//     std::cout << '\n';

//     std::cout << "bar contains:";
//     for (size_t i=0; i<bar.size(); i++)
//         std::cout << ' ' << bar[i];
//     std::cout << '\n';

// }

// void ft_assign()
// {
//     {
//     ft::vector<char> v;
    
//     v.assign(0, 'c');
//     for (size_t i = 0; i < v.size(); i++)
//         std::cout << v[i];
//     v.assign(64, 'A');
//     for (size_t i = 0; i < v.size(); i++)
//         std::cout << v[i];
//     v.assign(32, '5');
//     for (size_t i = 0; i < v.size(); i++)
//         std::cout << v[i];
//     v.assign(49, '8');
//     for (size_t i = 0; i < v.size(); i++)
//         std::cout << v[i];
//     v.assign(77, '2');
//     for (size_t i = 0; i < v.size(); i++)
//         std::cout << v[i];
//     std::cout << v.capacity() << '\n';
//     }
//     {
//         ft::vector<std::string> v;
//         v.assign(0, "");
//          v.assign(64, "vector-string");
//     }
// }

// void ft_pair()
// {

//     ft::vector<ft::pair<int, int> > D;
//     D.push_back(ft::pair<int, int>(-1, -2));
//     D.push_back(ft::pair<int, int>(-3, -4));
//     D.push_back(ft::pair<int, int>(-6, -7));
//     D.push_back(ft::pair<int, int>(-8, -9));

//     ft::vector<ft::pair<int, int> >::iterator it = D.begin();
//     for (; it != D.end(); ++it)
//     {
//         cout << it->second << " ";
//     }
//     std::cout << '\n';
// }

void test_map()
{
    ft::map<int, int> a;
    a.insert(ft::pair<int, int>(6, 37));
    a.insert(ft::pair<int, int>(4, 47));
    a.insert(ft::pair<int, int>(9, 67));
    a.insert(ft::pair<int, int>(5, 87));
    a.insert(ft::pair<int, int>(7, 97));
    a.insert(ft::pair<int, int>(0, 97));
    a.insert(ft::pair<int, int>(10, 77));

    (void)a.value_comp();
 
    std::cout << a.equal_range(0).first->first << ' ' << a.equal_range(0).second->first << '\n';


    // std::map<int, int> b;
    // b.insert(std::pair<int, int>(6, 37));
    // b.insert(std::pair<int, int>(4, 47));
    // b.insert(std::pair<int, int>(9, 67));
    // b.insert(std::pair<int, int>(5, 87));
    // b.insert(std::pair<int, int>(7, 97));
    // b.insert(std::pair<int, int>(0, 97));
    // b.insert(std::pair<int, int>(10, 77));
 
    // std::cout << a.equal_range(0).first->first << ' ' << a.equal_range(0).second->first << '\n';
}

int main()
{
    // ft_tests();
    // inputf();
    // ft_resize();
    // ft_swap();
    // ft_assign();
    // ft_pair();
    
    // std::vector<int> a;
    // a.push_back(13);
    // std::vector<int>::iterator itt = a.begin();
    // std::vector<int>::const_iterator it = itt;
    // std::cout << it - itt << '\n';
    // *itt = 0;
    // (void)it;
    // return 0;
    // ft::map<int, int> a;
    // a.insert(ft::pair<int, int>(6, 37));
    // a.insert(ft::pair<int, int>(4, 47));
    // a.insert(ft::pair<int, int>(9, 67));
    // a.insert(ft::pair<int, int>(5, 87));
    // a.insert(ft::pair<int, int>(7, 97));
    // a.insert(ft::pair<int, int>(0, 97));
    // a.insert(ft::pair<int, int>(10, 77));


    // a.insert(ft::pair<int, int>(61, 37));
    // a.insert(ft::pair<int, int>(41, 47));
    // a.insert(ft::pair<int, int>(53, 57));
    // a.insert(ft::pair<int, int>(11, 67));
    // a.insert(ft::pair<int, int>(15, 87));
    // a.insert(ft::pair<int, int>(31, 97));
    // a.insert(ft::pair<int, int>(20, 77));
    // a.insert(ft::pair<int, int>(13, 77));
    // a.insert(ft::pair<int, int>(33, 77));
    // a.insert(ft::pair<int, int>(14, 77));

    // a.insert(ft::pair<int, int>(5, 87));
    // a.insert(ft::pair<int, int>(12, 97));
    // a.insert(ft::pair<int, int>(23, 77));
    // a.insert(ft::pair<int, int>(3, 77));
    // a.insert(ft::pair<int, int>(30, 77));
    // a.insert(ft::pair<int, int>(1, 77));

    // a.insert(ft::pair<int, int>(-5, 87));
    // a.insert(ft::pair<int, int>(-12, 97));
    // a.insert(ft::pair<int, int>(-23, 77));
    // a.insert(ft::pair<int, int>(-3, 77));
    // a.insert(ft::pair<int, int>(-30, 77));
    // a.insert(ft::pair<int, int>(-1, 77));

    
    // b.clear();
    // ft::map<int, int>::iterator it = b.begin();
    // (void)it;

    // for (; it != b.end(); it++)
    //     std::cout << it->first << ' ' << it->second << '\n';

    // a.print();
  
    // test_map();

    // system("leaks ftcontainers");

    return(0);
}