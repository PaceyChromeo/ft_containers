#include "map.hpp"
#include <iostream>
#ifndef NAMESPACE
# define NAMESPACE ft
#endif
int main(void) {
	
	std::cout << "           --- Constructors / iterators && [] ---             \n";
	std::cout << std::endl;
	{
		NAMESPACE::map<char, int> m1;
		m1['a'] = 10;
		m1['b'] = 30;
		m1['c'] = 50;
		m1['d'] = 70;
		NAMESPACE::map<char, int> m2(m1.begin(), m1.end());
		NAMESPACE::map<char, int>::iterator it;
		
		std::cout << "m1 -------------" << std::endl;
		for(it = m1.begin(); it != m1.end(); it++) {
			std::cout << " " << it->first << " = " << it->second;
		}
		m2['f'] = 90;
		std::cout << std::endl;
		std::cout << "m2 -------------" << std::endl;
		for(it = m2.begin(); it != m2.end(); it++) {
			std::cout << " " << it->first << " = " << it->second;
		}
	}
	std::cout << std::endl << std::endl;
	std::cout << "           --- Capacity ---             \n";
	std::cout << std::endl;
	{
		NAMESPACE::map<char, int> m1;
		NAMESPACE::map<char, int> m2;
		m2['a'] = 42;
		m2['b'] = 99;
		if (m1.empty())
			std::cout << "m1 is empty" << std::endl;
		if (!m2.empty())
			std::cout << "m2 is not empty" << std::endl;
		std::cout << "m1 size : " << m1.size() << std::endl;
		std::cout << "m2 size : " << m2.size() << std::endl;
	}
	std::cout << "           --- Modifiers ---             \n";
    {
        NAMESPACE::map<char, int> m1;
        NAMESPACE::pair<char,int> p1('x', 19);
        NAMESPACE::pair<char,int> p2('a', 42);
        NAMESPACE::pair<char,int> p3('k', 64);
        NAMESPACE::map<char,int>::iterator  it;

        if (m1.empty())
            std::cout << "--> m1 is empty" << std::endl;
        m1.insert(p1);
        std::cout << "--> m1 insert(p1)" << std::endl;
        std::cout << "m1 : ";
		for(it = m1.begin(); it != m1.end(); it++) {
			std::cout << " " << it->first << " = " << it->second;
		}
        std::cout << std::endl;
        m1.insert(p2);
        std::cout << "--> m1 insert(p2)" << std::endl;
        std::cout << "m1 : ";
		for(it = m1.begin(); it != m1.end(); it++) {
			std::cout << " " << it->first << " = " << it->second;
		}
        std::cout << std::endl;
        m1.insert(p3);
        std::cout << "--> m1 insert(p3)" << std::endl;
        std::cout << "m1 : ";
		for(it = m1.begin(); it != m1.end(); it++) {
			std::cout << " " << it->first << " = " << it->second;
		}
        std::cout << std::endl;
        m1.erase('k');
        std::cout << "--> m1 erase('k')" << std::endl;
        std::cout << "m1 : ";
		for(it = m1.begin(); it != m1.end(); it++) {
			std::cout << " " << it->first << " = " << it->second;
		}
        std::cout << std::endl;
        m1.clear();
        std::cout << "--> m1 clear()" << std::endl;
        std::cout << "m1 : ";
		for(it = m1.begin(); it != m1.end(); it++) {
			std::cout << " " << it->first << " = " << it->second;
		}
        std::cout << std::endl;
        if (m1.empty())
            std::cout << "--> m1 is empty" << std::endl;
    }
	std::cout << "           --- Observers ---             \n";
    {
        NAMESPACE::map<char, int> m1;
        NAMESPACE::pair<char,int> p1('x', 19);
        NAMESPACE::pair<char,int> p2('t', 54);
        NAMESPACE::pair<char,int> p3('l', 89);
        NAMESPACE::pair<char,int> p4('f', 6);
        NAMESPACE::map<char, int>::iterator it;

        m1.insert(p1);
        m1.insert(p2);
        m1.insert(p3);
        m1.insert(p4);
        std::cout << "m1 : ";
		for(it = m1.begin(); it != m1.end(); it++) {
			std::cout << "|" << it->first << " = " << it->second;
		}
        std::cout << std::endl;

        std::cout << "count('k') --> " << m1.count('k') << std::endl;
        std::cout << "count('l') --> " << m1.count('l') << std::endl;
    }
	return 0;
}