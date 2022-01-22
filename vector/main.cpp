#include "vector.hpp"
#include <stack>
#include <vector>
#include <deque>
#include <iostream>
#include <string>

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

int main(void) {
    std::cout << "           --- Constructors / Size ---             \n";
    {
        NAMESPACE::vector<int>  v1(3, 10); 
        NAMESPACE::vector<int>  v2(5); 
        NAMESPACE::vector<int>  v3; 

        std::cout << "v1 size : " << v1.size() << std::endl;
        std::cout << "v2 size : " << v2.size() << std::endl;
        std::cout << "v3 size : " << v3.size() << std::endl;
    }
	std::cout << "           --- Iterators ---             \n";
    {
        NAMESPACE::vector<int>  v1(10); 
        NAMESPACE::vector<int>::iterator it;
        NAMESPACE::vector<int>::iterator ite = v1.end();
        NAMESPACE::vector<int>::reverse_iterator rit;
        NAMESPACE::vector<int>::reverse_iterator rite = v1.rend();
        int i = 0;

        std::cout << "v1 with iterator : ";
        for(it = v1.begin();it != ite; it++) {
            *it += i;
            i++;
            std::cout << " " << *it; 
        }

        std::cout << std::endl;
        std::cout << "v1 with reverse iterator : ";
        for(rit = v1.rbegin();rit != rite; rit++) {
            std::cout << " " << *rit; 
        }
        std::cout << std::endl;
    }
	std::cout << "           --- Capacity ---             \n";
    {
        NAMESPACE::vector<int>  v1(10); 
        NAMESPACE::vector<int>  v2(4, 42); 
        NAMESPACE::vector<int>  v3; 

        std::cout << "Before resize function : " << std::endl << std::endl;
        std::cout << "v1 size : " << v1.size() << std::endl;
        std::cout << "v1 capacity : " << v1.capacity() << std::endl;
        std::cout << "v2 size : " << v2.size() << std::endl;
        std::cout << "v2 capacity : " << v2.capacity() << std::endl << std::endl;
        v1.resize(5);
        v2.resize(13);
        std::cout << "After resize function : " << std::endl << std::endl;
        std::cout << "v1 size : " << v1.size() << std::endl;
        std::cout << "v1 capacity : " << v1.capacity() << std::endl;
        std::cout << "v2 size : " << v2.size() << std::endl;
        std::cout << "v2 capacity : " << v2.capacity() << std::endl << std::endl;

        std::cout << "Who is empty : " << std::endl << std::endl;
        if (!v1.empty()) 
            std::cout << "v1 is not empty" << std::endl;
        if (!v2.empty()) 
            std::cout << "v2 is not empty" << std::endl;
        if (v3.empty()) 
            std::cout << "v3 is empty" << std::endl << std::endl;
        
        std::cout << "Before reserve function : " << std::endl << std::endl;
        std::cout << "v1 size : " << v1.size() << std::endl;
        std::cout << "v1 capacity : " << v1.capacity() << std::endl << std::endl;
        v1.reserve(8);
        std::cout << "After reserve function : " << std::endl << std::endl;
        std::cout << "v1 size : " << v1.size() << std::endl;
        std::cout << "v1 capacity : " << v1.capacity() << std::endl;
    }
	std::cout << "           --- Modifiers ---             \n";
    {
        NAMESPACE::vector<int>  v1(10, 8);
        NAMESPACE::vector<int>::iterator it; 
        NAMESPACE::vector<int>::iterator ite; 

        v1[2] = 42;
        v1.push_back(78);
        v1.push_back(96);
        std::cout << "--> v1[2] = 42" << std::endl;
        std::cout << "--> push_back(78)" << std::endl;
        std::cout << "--> push_back(96)" << std::endl << std::endl;
        for(it = v1.begin();it != v1.end(); it++) {
            std::cout << " " << *it; 
        }

        std::cout << std::endl << std::endl;

        v1.pop_back();
        v1.pop_back();
        std::cout << "--> pop_back()" << std::endl;
        std::cout << "--> pop_back()" << std::endl << std::endl;
        for(it = v1.begin();it != v1.end(); it++) {
            std::cout << " " << *it; 
        }
        std::cout << std::endl << std::endl;
        v1.insert(v1.begin(), 5);
        v1.insert(v1.end(), 19);
        std::cout << "--> v1.insert(v1.begin(), 5)" << std::endl;
        std::cout << "--> v1.insert(v1.end(), 19)" << std::endl << std::endl;
        for(it = v1.begin();it != v1.end(); it++) {
            std::cout << " " << *it; 
        }
        std::cout << std::endl << std::endl;
        std::cout << "--> v1.erase(v1.begin())" << std::endl;
        std::cout << "--> v1.erase(v1.begin())" << std::endl;
        std::cout << "--> v1.erase(v1.begin())" << std::endl << std::endl;
        v1.erase(v1.begin());
        v1.erase(v1.begin());
        v1.erase(v1.begin());
        for(it = v1.begin();it != v1.end(); it++) {
            std::cout << " " << *it; 
        }
    }
}