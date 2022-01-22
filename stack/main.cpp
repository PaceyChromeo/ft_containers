#include "stack.hpp"
#include <stack>
#include <vector>
#include <deque>
#include <list>
#include <iostream>
#include <string>

#ifndef NAMESPACE
# define NAMESPACE ft
#endif


int main(){
	{
		{
			std::cout << "           --- Constructors and size ---             \n";
			std::deque<int> mydeque (3,100);
			std::list<int> mylist (5,500);
			std::vector<int> myvector (2,200);

			NAMESPACE::stack<int> first;
			NAMESPACE::stack<int, std::vector<int> > second;
			NAMESPACE::stack<int, std::vector<int> > third (myvector);
			NAMESPACE::stack<int, std::list<int> > fourth(mylist);
			NAMESPACE::stack<int, std::deque<int> > fifth(mydeque);

			std::cout << "size of first: " << first.size() << '\n';
			std::cout << "size of second: " << second.size() << '\n';
			std::cout << "size of third: " << third.size() << '\n';
			std::cout << "size of third: " << fourth.size() << '\n';
			std::cout << "size of third: " << fifth.size() << '\n';
		}
		{
			std::cout << "          --- Push / Pop / Top / Empty ---         \n";
			NAMESPACE::stack<int> mystack;
			int sum (0);

			for (int i = 1; i <= 10; i++)
				mystack.push(i * 5);

			while (!mystack.empty())
			{
				sum += mystack.top();
				mystack.pop();
			}
			std::cout << "total: " << sum << '\n';
		}

	}
}