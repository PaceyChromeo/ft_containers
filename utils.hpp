#pragma once 

#include <string>
#include <fstream>

namespace ft {

	template<class T1, class T2>
		struct pair{	
			typedef T1	first_type;
			typedef T2	second_type;

			T1		first;
			T2		second;
			
			pair() : first(), second() {}; // Default constructor
			pair(const T1 & a, const T2 & b) : first(a), second(b) {}; // Initialization constructor
			template<class U1, class U2>
				pair (const pair< U1, U2 >& pr) : first(pr.first), second(pr.second) {}; // Copy constructor
			~pair() {};
			
			pair& operator=(const pair<T1, T2>& rhs) {
				if (this != &rhs){
					first = rhs.first;
					second = rhs.second;
				}
				return (*this);
			};	
		};

		template <class T1, class T2>
			bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
				return lhs.first == rhs.first && lhs.second == rhs.second;
			};
		template <class T1, class T2>
			bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {return !(lhs == rhs);};
		template <class T1, class T2>
			bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
				return lhs.first < rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
			};
		template <class T1, class T2>
			bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {return !(rhs < lhs);};
		template <class T1, class T2>
			bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {return rhs > lhs;};
		template <class T1, class T2>
			bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {return !(lhs < rhs);};
		
		template <class T1, class T2>
			pair<T1, T2> make_pair (T1 x, T2 y) {return (pair<T1, T2>(x, y));};
			
	template<bool Cond, class T = void> 
		struct enable_if {};

	template<class T> 
		struct enable_if<true, T> { 
			typedef T type;
		};

	template <class T, T v>
		struct integral_constant {
			static const T					value = v;
			typedef T						value_type;
			typedef integral_constant<T,v> 	type;
			operator T() { return v; }
	};

	typedef integral_constant<bool, true>	true_type;   
	typedef integral_constant<bool, false>	false_type;

	template <class T>
		struct is_integral : false_type {};

	template <>
		struct is_integral<int> : true_type {};

	template <>
		struct is_integral<bool> : true_type {};

	template <>
		struct is_integral<char> : true_type {};

	template <>
		struct is_integral<char16_t> : true_type {};

	template <>
		struct is_integral<char32_t> : true_type {};

	template <>
		struct is_integral<wchar_t> : true_type {};

	template <>
		struct is_integral<short> : true_type {};

	template <>
		struct is_integral<long> : true_type {};

	template <>
		struct is_integral<long long> : true_type {};

	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2){
		    while (first1 != last1){
				if (first2 == last2 || *first2 < *first1) 
					return false;
				else if (*first1 < *first2)
					return true;
				++first1;
				++first2;
			}
			return (first2 != last2);
		}
	
	template <class InputIterator1, class InputIterator2>
		bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ){
			while (first1 != last1){
				if (!(*first1 == *first2))
					return false;
				++first1;
				++first2;
			}
			return true;
		}
}