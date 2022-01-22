#pragma once

#include <iostream>
#include <memory>
#include <cstddef>
#include <cctype>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "RBTset.hpp"

namespace ft {

template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set{

		public:

			typedef Node<T, T>										Node;
			typedef typename Alloc::template rebind<Node>::other 	rebind;
			typedef T												value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef	ft::setIterator<const Node, const T>			iterator;
			typedef	ft::setIterator< const Node, const T>			const_iterator;
			typedef	ft::reverse_setIterator<iterator>				reverse_iterator;
			typedef	ft::reverse_setIterator<const_iterator>			const_reverse_iterator;
			typedef std::ptrdiff_t									difference_type;
			typedef size_t											size_type;

		private:
			
			allocator_type				_alloc;
			key_compare					_comp;
			RBtree <T, T, key_compare>	_rbt;

		public:
		
		//--------------------[Nested Class]--------------------//

			class value_compare : public std::binary_function<value_type,value_type,bool>{
				friend class set;
				
				protected:
					key_compare	_comp;
					value_compare (key_compare c) : _comp(c) {}
				
				public:
					typedef bool			result_type;
					typedef value_type		first_argument_type;
					typedef value_type		second_argument_type;
					
					bool operator() (const value_type& x, const value_type& y) const{
						return _comp(x, y);
					}
		};

		//--------------------[Constructor & Destructor]--------------------//

		explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
			this->_alloc = alloc;
			this->_comp = comp;
		}

		template <class InputIterator>
		set (InputIterator first, InputIterator last, const Compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
			this->_comp = comp;
			this->_alloc = alloc;
			this->_rbt.insert(first, last);
		}

		set (const set& x) : _alloc(x._alloc) {
				if (!(x._rbt.empty())){
					this->_rbt.insert(x.begin(), x.end());
			}
		} 

		~set() {} 

		set& operator=(const set & rhs) {
			if (this != &rhs){
				this->_alloc = rhs._alloc;
				this->clear();
				this->_rbt.insert(rhs.begin(), rhs.end());
			}
			return (*this);
		}		

		//--------------------[Iterators]--------------------//

		iterator				begin() { return iterator(this->_rbt.begin()); };
		const_iterator			begin() const { return const_iterator(this->_rbt.begin());};

		iterator				end() {return this->_rbt.end();};
		const_iterator			end() const {return const_iterator(this->_rbt.end());};

		reverse_iterator		rbegin() {return this->_rbt.rbegin();};
		const_reverse_iterator	rbegin() const {return this->_rbt.rbegin();};

		reverse_iterator		rend() { return this->_rbt.rend(); };
		const_reverse_iterator	rend() const { return this->_rbt.rend(); };

		//--------------------[Capacity]--------------------//

		bool		empty() const { return this->_rbt.size() == 0; };
		size_type	size() const { return this->_rbt.size(); };
		size_type	max_size() const { return this->_alloc.max_size(); };

		//--------------------[Modifiers]--------------------//

		pair<iterator,bool>		insert (const value_type& val) { return this->_rbt.insert(ft::make_pair(val, val));};

		iterator				insert (iterator position, const value_type& val) { return this->_rbt.insert(position, ft::make_pair(val, val)); };

		template <class InputIterator>
		void					insert (InputIterator first, InputIterator last) { this->_rbt.insert(first, last); };
		
		void					erase (iterator position) { this->_rbt.erase(position); };
		size_type				erase (const value_type& k) { return this->_rbt.erase(k); };
     	void					erase (iterator first, iterator last) { this->_rbt.erase(first, last); };
		
		void					swap(set& x) { this->_rbt.swap(x._rbt); };

		void					clear() { this->_rbt.clear(); };

		//--------------------[Observers]--------------------//

		key_compare		key_comp() const { return this->_rbt.key_comp(); };

		value_compare	value_comp() const {return value_compare(this->key_comp());};

		//--------------------[Operations]--------------------//

		iterator		find (const value_type& k) {return this->_rbt.find(k);};

		const_iterator	find (const value_type& k) const {return this->_rbt.find(k);};
		
		size_type		count (const value_type & k) const {return this->_rbt.count(k);};
		
		iterator		lower_bound (const value_type& k) {return this->_rbt.lower_bound(k);};
		
		const_iterator	lower_bound (const value_type& k) const {return this->_rbt.lower_bound(k);};

		iterator		upper_bound (const value_type& k) {return this->_rbt.upper_bound(k);};
		
		const_iterator	upper_bound (const value_type& k) const {return this->_rbt.upper_bound(k);};

		pair<iterator, iterator>	equal_range (const value_type& k) {return this->_rbt.equal_range(k);};
		
		pair<const_iterator, const_iterator>	equal_range (const value_type& k) const {return this->_rbt.equal_range(k);};

		//--------------------[Allocator]--------------------//
		allocator_type get_allocator() const { return (this->rbt.get_allocator());};

	};

		//--------------------[Non-members Overloads]--------------------//

	template <class T, class key_compare, class Alloc>
	void swap (set<T, key_compare, Alloc>& x, set<T, key_compare, Alloc>& y) {
		x.swap(y);
	};

	template <class T, class key_compare, class Alloc>
	bool operator==( const set<T, key_compare, Alloc>& lhs, const set<T, key_compare, Alloc>& rhs ){
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	};

	template <class T, class key_compare, class Alloc>
	bool operator!=( const set<T, key_compare, Alloc>& lhs, const set<T, key_compare, Alloc>& rhs ){
		return !(lhs == rhs);
	};

	template <class T, class key_compare, class Alloc>
	bool operator<( const set<T, key_compare, Alloc>& lhs, const set<T, key_compare, Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template <class T, class key_compare, class Alloc>
	bool operator<=( const set<T, key_compare, Alloc>& lhs, const set<T, key_compare, Alloc>& rhs ) {
		return !(rhs < lhs);
	};

	template <class T, class key_compare, class Alloc>
	bool operator>( const set<T, key_compare, Alloc>& lhs, const set<T, key_compare, Alloc>& rhs ) {
		return rhs < lhs;
	};

	template <class T, class key_compare, class Alloc>
	bool operator>=( const set<T, key_compare, Alloc>& lhs, const set<T, key_compare, Alloc>& rhs ) {
		return !(lhs < rhs);
	};
}
