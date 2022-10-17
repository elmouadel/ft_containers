
#include <iostream>
#include <string>
#include <deque>
#include "../../src/vector.hpp"
#include "../../src/stack.hpp"
#include "../../src/map.hpp"
#include "../../src/set.hpp"


#include <stdlib.h>

#define COUNT 1000000


struct Buffer
{
	long	id;
	int     ibuff[42];
	char    cbuff[1337];
	Buffer(int id) : id(id) {}
	bool operator!=(Buffer rhs)
	{
		return (id != rhs.id);
	}
};

template<typename T>
class MutantStack : public ft::stack<T>
{
    public:
    	MutantStack() {}
    	MutantStack(const MutantStack<T>& src) { *this = src; }
    	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
    	{
    		this->c = rhs.c;
    		return *this;
    	}
    	~MutantStack() {}

    	typedef typename ft::stack<T>::container_type::iterator iterator;

    	iterator begin() { return this->c.begin(); }
    	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) 
{
    if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

    ft::vector<int>::iterator   it_vi;

    ft::map<int, int>::iterator             it_mi;
    ft::map<std::string, char>::iterator    it_ms;

    ft::set<int>::iterator          it_si;
    ft::set<std::string>::iterator  it_ss;

	ft::vector<int>             vector_int;
	ft::vector<Buffer>          vector_buffer;

	ft::map<int, int>           map_int;
	ft::map<std::string, char>  map_str;

    MutantStack<int>                  it_stack_int;
    ft::stack<int, std::deque<int> >  stack_deq_int;

    ft::set<int>          set_int;
	ft::set<std::string>  set_str;

/******************************* vectors tests ********************************/
    for (int i = 0; i < COUNT; i++)
        vector_int.push_back(rand() % COUNT);
    {
        ft::vector<int> vector_tmp_int(vector_int.begin(), vector_int.end());
        
        if (vector_int.size() != vector_tmp_int.size())
            std::cerr << "error: vector construction with ranges failed!!\n";
        for (int i = 0; i < COUNT; i++)
        {
            if (vector_int[i] != vector_tmp_int[i])
                std::cerr << "error: vector construction with ranges failed!!\n";
            vector_tmp_int.pop_back();
        }
        if (!vector_tmp_int.empty())
            std::cerr << "error: this vector should be empty!!\n";
    }
    {
        ft::vector<int> vector_tmp_int;
        
        vector_tmp_int = vector_int;
        if (vector_int.size() != vector_tmp_int.size())
            std::cerr << "error: vector assign failed!!\n";
        for (int i = 0; i < COUNT; i++)
        {
            if (vector_int[i] != vector_tmp_int[i])
                std::cerr << "error: vector assign failed!!\n";

        }
        vector_tmp_int.resize(0, 0);
        if (!vector_tmp_int.empty())
            std::cerr << "error: this vector should be empty!!\n";
    }
    {
        ft::vector<int> vector_tmp_int;
        int*            arr;

        arr = vector_int.data();
        vector_tmp_int.resize(vector_int.size());

        for (it_vi = vector_tmp_int.begin(); it_vi != vector_tmp_int.end(); ++it_vi, ++arr)
            *it_vi = *arr;
        
        vector_tmp_int.erase(vector_tmp_int.begin() + (COUNT / 2), vector_tmp_int.end());
        vector_tmp_int.insert(vector_tmp_int.end(), vector_int.begin() + (COUNT / 2), vector_int.end());
        for (int i = 0; i < COUNT; i++)
        {
            if (vector_int[i] != vector_tmp_int[i])
                std::cerr << "error: vector erase/insert failed!!\n";
        }
    }
    {
        ft::vector<int> vector_tmp_int(vector_int.begin(), vector_int.end());
        
        int var_count = COUNT;

        for (int i = 0; i < var_count; i++)
        {
            if (vector_tmp_int.at(i) > COUNT - 100)
            {
                vector_tmp_int.erase(vector_tmp_int.begin() + i);
                --var_count;
            }
        }
        std::cout << "VECTOR CONTENT : " << std::endl;
        std::cout << "*****************" << std::endl;
        for (it_vi = vector_tmp_int.begin(); it_vi != vector_tmp_int.end(); ++it_vi)
            std::cout << *it_vi << ' ';
        
        std::cout << std::endl;
        std::cout << "VECTOR SIZE : " <<  std::endl;
        std::cout << "*****************" << std::endl;
        std::cout << vector_tmp_int.size() << std::endl;
    }
	for (int i = 0; i < COUNT; i++)
        vector_buffer.push_back(Buffer(rand() % COUNT));
    {
        ft::vector<Buffer> vectro_tmp_buf(vector_buffer.begin(), vector_buffer.end());
        
        if (vector_buffer.size() != vectro_tmp_buf.size())
            std::cerr << "error: vector construction with ranges failed!!\n";
        for (int i = 0; i < COUNT; i++)
        {
            if (vector_buffer[i] != vectro_tmp_buf[i])
                std::cerr << "error: vector construction with ranges failed!!\n";
        }
        vectro_tmp_buf.clear();
        if (!vectro_tmp_buf.empty())
            std::cerr << "error: this vector should be empty!!\n";
    }
    {
        ft::vector<int> vector_tmp_int;
        
        vector_tmp_int = vector_int;
        
        ft::swap(vector_int, vector_tmp_int);
        if (vector_tmp_int == vector_int)
            std::cout << "comp eq\n";
        vector_tmp_int.pop_back();
        if (vector_tmp_int < vector_int)
            std::cout << "comp smaller\n";
        vector_int.pop_back();
        vector_int.pop_back();
        if (vector_tmp_int > vector_int)
            std::cout << "comp greater\n";
    }
    std:: cout << "abc struct max size:" <<  ft::vector<Buffer>().max_size() << std::endl;
    std:: cout << "Float max size:" <<  ft::vector<float>().max_size() << std::endl;
    std:: cout << "Long max size:" <<  ft::vector<long>().max_size() << std::endl;
    std:: cout << "Int max size:" <<  ft::vector<int>().max_size() << std::endl;
    std:: cout << "Short max size:" <<  ft::vector<short>().max_size() << std::endl;
    std:: cout << "Char max size:" <<  ft::vector<char>().max_size() << std::endl;
/********************************** map tests *********************************/
    for (int i = 0; i < COUNT; i++)
        map_int.insert(ft::make_pair(rand() % COUNT, rand() % COUNT));
    {
        ft::map<int, int> map_tmp_int(map_int.begin(), map_int.end());
        
        if (map_int.size() != map_tmp_int.size())
            std::cerr << "error: map construction with ranges failed!!\n";

        ft::map<int, int>::iterator it_tmp = map_tmp_int.begin();
        for (it_mi = map_int.begin(); it_mi != map_int.end(); ++it_mi, ++it_tmp)
        {
            if (it_mi->first != it_tmp->first)
                std::cerr << "error: map construction with ranges failed!!\n";
        }

        map_tmp_int.erase(map_tmp_int.begin(), map_tmp_int.end());
        if (!map_tmp_int.empty())
            std::cerr << "error: this map should be empty!!\n";
    }
    {
        ft::map<int, int> map_tmp_int;
        
        map_tmp_int = map_int;
        if (map_int.size() != map_tmp_int.size())
            std::cerr << "error: map construction with ranges failed!!\n";
        ft::map<int, int>::iterator it_tmp = map_tmp_int.begin();
        for (it_mi = map_int.begin(); it_mi != map_int.end(); ++it_mi, ++it_tmp)
        {
            if (it_mi->first != it_tmp->first)
                std::cerr << "error: map construction with ranges failed!!\n";
        }
        map_tmp_int.erase(map_tmp_int.begin(), map_tmp_int.end());
        if (!map_tmp_int.empty())
            std::cerr << "error: this map should be empty!!\n";
    }
    {
        ft::map<int, int> map_tmp_int;

        map_tmp_int.insert(map_int.begin(), map_int.end());
        for (size_t i = 0; i < map_int.size(); i++)
        {
            if (map_int[i] != map_tmp_int[i])
                std::cerr << "error: map insert failed!!\n";
        }
		for (size_t i = 0; i < COUNT; i++)
			map_tmp_int.erase(i);

		if (!map_tmp_int.empty())
            std::cerr << "error: this map should be empty!!\n";
    }
	{
        ft::map<int, int> map_tmp_int(map_int.begin(), map_int.end());

        ft::swap(map_int, map_tmp_int);
        
        ft::map<int, int>::iterator it_tmp = map_int.begin();
        for (; it_tmp != map_int.end(); ++it_tmp)
        {
            if (map_tmp_int.at(it_tmp->first) > COUNT - 100000)
                map_tmp_int.erase(it_tmp->first);
            else if (map_tmp_int.at(it_tmp->first) > COUNT - 200000)
			{
				ft::map<int, int>::iterator _it = map_tmp_int.find(it_tmp->first);
				if (_it != map_tmp_int.end())
					map_tmp_int.erase(_it);
			}
            else if (map_tmp_int.at(it_tmp->first) > COUNT - 300000)
            {
                ft::map<int, int>::iterator _it = map_tmp_int.lower_bound(it_tmp->first);
				if (_it != map_tmp_int.end())
					map_tmp_int.erase(_it);
            }
            else if (map_tmp_int.at(it_tmp->first) > COUNT - 400000)
            {
                ft::map<int, int>::iterator _it = map_tmp_int.upper_bound(it_tmp->first);
				_it->second++;
            }
        }
        std::cout << "MAP CONTENT : " << std::endl;
        std::cout << "*****************" << std::endl;
        for (it_mi = map_tmp_int.begin(); it_mi != map_tmp_int.end(); ++it_mi)
            std::cout << it_mi->first << " : " << it_mi->second << '\n';
        
        std::cout << std::endl;
        std::cout << "MAP SIZE : " <<  std::endl;
        std::cout << "*****************" << std::endl;
        std::cout << map_tmp_int.size() << std::endl;
    }
    for (int i = 0; i < COUNT; i++)
    {
        std::string tmp;
        for (int j = 0; j < 26; j++)
            tmp.push_back((rand() % 26) + 97);
        map_str.insert(ft::make_pair(tmp, (rand() % 26) + 97));
    }
    {
        ft::map<std::string, char> map_tmp_str(map_str.begin(), map_str.end());

        ft::map<std::string, char>::iterator it_tmp = map_str.begin();
        
        for (; it_tmp != map_str.end(); ++it_tmp)
        {
            if (it_tmp->first > "t")
                map_tmp_str.erase(it_tmp->first);
            else if (it_tmp->first > "r")
			{
				ft::map<std::string, char>::iterator _it = map_tmp_str.find(it_tmp->first);
				if (_it != map_tmp_str.end())
					map_tmp_str.erase(_it);
			}
            else if (it_tmp->first > "p")
            {
                ft::map<std::string, char>::iterator _it = map_tmp_str.lower_bound(it_tmp->first);
				if (_it != map_tmp_str.end())
					map_tmp_str.erase(_it);
            }
            else if (it_tmp->first > "n")
            {
                ft::map<std::string, char>::iterator _it = map_tmp_str.upper_bound(it_tmp->first);
				_it->second++;
            }
        }
        std::cout << "MAP CONTENT : " << std::endl;
        std::cout << "*****************" << std::endl;
        for (it_ms = map_tmp_str.begin(); it_ms != map_tmp_str.end(); ++it_ms)
            std::cout << it_ms->first << " : " << it_ms->second << '\n';
        
        std::cout << std::endl;
        std::cout << "MAP SIZE : " <<  std::endl;
        std::cout << "*****************" << std::endl;
        std::cout << map_tmp_str.size() << std::endl;
    }
/********************************* stack tests ********************************/
    for (int i = 0; i < 100; ++i)
		it_stack_int.push(i);
	for (MutantStack<int>::iterator it = it_stack_int.begin(); it != it_stack_int.end(); it++)
		std::cout << *it << ' ';
    for (int i = 0; i < 100; i++)
        it_stack_int.pop();
    if (!it_stack_int.empty())
        std::cerr << "error: this map should be empty!!\n";
    
    for (int i = 0; i < 100; ++i)
		stack_deq_int.push(i);
    for (int i = 0; i < 100; i++)
        stack_deq_int.pop();
    if (!stack_deq_int.empty())
        std::cerr << "error: this map should be empty!!\n";

/********************************** set tests *********************************/
    for (int i = 0; i < COUNT; i++)
        set_int.insert(rand() % COUNT);
    {
        ft::set<int> set_tmp_int(set_int.begin(), set_int.end());
        
        if (set_int.size() != set_tmp_int.size())
            std::cerr << "error: set construction with ranges failed!!\n";

        ft::set<int>::iterator it_tmp = set_tmp_int.begin();
        for (it_si = set_int.begin(); it_si != set_int.end(); ++it_si, ++it_tmp)
        {
            if (*it_si != *it_tmp)
                std::cerr << "error: set construction with ranges failed!!\n";
        }

        set_tmp_int.erase(set_tmp_int.begin(), set_tmp_int.end());
        if (!set_tmp_int.empty())
            std::cerr << "error: this set should be empty!!\n";
    }
    {
        ft::set<int> set_tmp_int;
        
        set_tmp_int = set_int;
        if (set_int.size() != set_tmp_int.size())
            std::cerr << "error: set construction with ranges failed!!\n";
        ft::set<int>::iterator it_tmp = set_tmp_int.begin();
        for (it_si = set_int.begin(); it_si != set_int.end(); ++it_si, ++it_tmp)
        {
            if (*it_si != *it_tmp)
                std::cerr << "error: set construction with ranges failed!!\n";
        }
        set_tmp_int.erase(set_tmp_int.begin(), set_tmp_int.end());
        if (!set_tmp_int.empty())
            std::cerr << "error: this set should be empty!!\n";
    }
    {
        ft::set<int> set_tmp_int(set_int.begin(), set_int.end());

        ft::set<int>::iterator it_tmp = set_int.begin();
        
        for (; it_tmp != set_int.end(); ++it_tmp)
        {
            if (*it_tmp > COUNT - 100000)
                set_tmp_int.erase(*it_tmp);
            else if (*it_tmp > COUNT - 200000)
			{
				ft::set<int>::iterator _it = set_tmp_int.find(*it_tmp);
				if (_it != set_tmp_int.end())
					set_tmp_int.erase(_it);
			}
            else if (*it_tmp > COUNT - 300000)
            {
                ft::set<int>::iterator _it = set_tmp_int.lower_bound(*it_tmp);
				if (_it != set_tmp_int.end())
					set_tmp_int.erase(_it);
            }
            else if (*it_tmp > COUNT - 400000)
            {
                ft::set<int>::iterator _it = set_tmp_int.upper_bound(*it_tmp);
                set_tmp_int.erase(_it);
            }
        }
        std::cout << "SET CONTENT : " << std::endl;
        std::cout << "*****************" << std::endl;
        for (it_si = set_tmp_int.begin(); it_si != set_tmp_int.end(); ++it_si)
            std::cout << *it_si << ' ';
        
        std::cout << std::endl;
        std::cout << "SET SIZE : " <<  std::endl;
        std::cout << "*****************" << std::endl;
        std::cout << set_tmp_int.size() << std::endl;
    }
    

	
	return (0);
}