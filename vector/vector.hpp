#pragma once

#include <iostream>
#include <memory>
#include <cstddef>
#include <cctype>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "../iterator/iterator.hpp"
#include "../utils.hpp"

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	
	class vector {

		
		public :
		
		typedef T                                           value_type;
		typedef Alloc                                       allocator_type;
		typedef typename allocator_type::reference          reference;
		typedef typename allocator_type::const_reference    const_reference;
		typedef typename allocator_type::pointer            pointer;
		typedef typename allocator_type::const_pointer      const_pointer;
		typedef	ft::iterator<T>								iterator; 
		typedef	ft::iterator<const T>						const_iterator; 
		typedef	ft::reverse_iterator<iterator>				reverse_iterator; 
		typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator; 
		typedef std::ptrdiff_t                              difference_type;
		typedef size_t                                      size_type;

		//--------------------[Constructor & Destructor]--------------------//

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr) {
			(void)enable;
            this->_alloc = alloc;
			size_type n = 0;
			InputIterator tmp = first;
			for (;first != last; first++){
				n++;
			}
			this->_tab = _alloc.allocate(n);
			first = tmp;
			n = 0;
			for (;first != last; first++){
				_alloc.construct(_tab + n, *first);
				n++;
			}
			this->_size = n;
			this->_capacity = n;
		}

		explicit vector(const allocator_type & alloc = allocator_type()) {

			this->_size = 0; 
			this->_alloc = alloc;
			this->_capacity = 0;
		}

		explicit vector (size_type n, const value_type & val = value_type(), 
			const allocator_type & alloc = allocator_type()) {
			this->_size = n;
			this->_capacity = n;
			this->_alloc = alloc;
			this->_tab = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(_tab + i, val);
			}
		}

		vector(vector const & x)  {
			_size = x._size;
			_capacity = x._capacity;
			_tab = _alloc.allocate(x._capacity);
			for (size_type i = 0; i < x.size(); i++)
				_tab[i] = x._tab[i];
		}

		~vector(void) {}
		
			//--------------------[Iterators]--------------------//
		iterator 				begin() { return iterator(_tab); }

		const_iterator			begin() const { return const_iterator(_tab); }

		iterator				end() { return iterator(_tab + _size); }

		const_iterator			end() const { return const_iterator(_tab + _size); }
		
		reverse_iterator		rbegin() { return reverse_iterator(_tab + (_size)); }

		const_reverse_iterator	rbegin() const { return const_reverse_iterator(_tab + (_size)); }
			
		reverse_iterator		rend() { return reverse_iterator(_tab); }

		const_reverse_iterator	rend() const { return const_reverse_iterator(_tab); }

			//--------------------[OVERLOAD OPERATOR =]--------------------//

		vector& operator=(const vector& x) {

			if (_size > 0) {
				for(size_type i = 0; i < _size; i++)
					_alloc.destroy(_tab + i);
				_alloc.deallocate(_tab, _capacity);
			}
			_tab = _alloc.allocate(x._capacity);
			_size = x._size;
			_capacity = x._capacity;
			for(size_t i = 0; i < _size; i++)
				_tab[i] = x._tab[i];
			return *this;
		}

			//--------------------[CAPACITY]--------------------//
		
		size_type	size() const { return this->_size; }

		size_type	max_size() const { return _alloc.max_size(); }

		void		resize(size_type n, value_type val = value_type()) {
			if (n < this->_size) {
				for (size_type i = n; i <= this->_size;i++) {
					_alloc.destroy(_tab + i);
				}
			}
			else if (n > this->_size) {
				pointer tmp = _alloc.allocate(n);
				for (size_type i = 0; i < this->_size; i++) {
					_alloc.construct(tmp + i, _tab[i]);
					_alloc.destroy(_tab + i);
				}
				_alloc.deallocate(_tab, this->_capacity);
				_tab = tmp;
				while (this->_size < n) {
					_tab[this->_size] = val;
					this->_size++;
				}
			}
			else
				return ;
			this->_size = n;
			this->_capacity = n;
		}

		size_type	capacity() const { return this->_capacity; } 

		bool		empty() const {
			if (this->_size == 0)
				return true;
			else
				return false;
		}

		void		reserve(size_type n) {
			if (n > max_size())
				throw std::length_error("vector");
			if (n > this->_capacity) {
			   pointer tmp = _alloc.allocate(n);
			   if (_size > 0){
				   for (size_type i = 0; i < _size; i++){
					   _alloc.construct(tmp + i, _tab[i]);
					   _alloc.destroy(_tab + i);
				   }
				}    
			   _alloc.deallocate(_tab, _capacity);
			   _tab = tmp;
			   _capacity = n;
		   }
		}
			//--------------------[ELEMENT ACCESS]--------------------//
		
		reference operator[] (size_type n) { return _tab[n]; }

		const_reference operator[] (size_type n) const { return _tab[n]; }

		reference			at (size_type n) {
			if (n < 0 || n >= _size)
				throw std::out_of_range("vector");
			return _tab[n];
		}

		const_reference		at (size_type n) const {
			if (n < 0 || n >= _size)
				throw std::out_of_range("vector");
			return _tab[n];   
		}

		reference			front() { return _tab[0]; }

		const_reference		front() const { return _tab[0]; }

		reference			back() { return _tab[_size - 1]; }
		
		const_reference		back() const { return _tab[_size - 1]; }

			//--------------------[MODIFIERS]--------------------//

		template<class InputIterator>
		void				assign (InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr ) {
                (void)enable;
		   if (!empty()) {
			   for (size_type  i = 0; i < this->_size; ++i){
				   _alloc.destroy(this->_tab + i);
			   }
			   _alloc.deallocate(_tab, _size);
		   } 
			InputIterator tmp = first;
			size_type n = 0;
		   for(; first != last; first++) {
			   n++;
		   }
		   	_tab = _alloc.allocate(n);
		  	first = tmp;
			n = 0;
		  	for(;first != last; first++) {
				_alloc.construct(_tab + n, *first);
				n++;
		   }
		   _size = n;
		   _capacity = n;
		}

        void				assign(size_type n, const value_type& val) {
		   if (!empty()) {
			   for (size_type  i = 0; i < this->_size; i++){
				   _alloc.destroy(this->_tab + i);
			   }
			   _alloc.deallocate(_tab, _size);
		   } 
		   this->_size = n;
		   this->_capacity = n;
		   this->_tab = _alloc.allocate(this->_size);
		   for(size_type i = 0; i < this->_size; i++) {
				_alloc.construct(_tab + i , val);
		   }
		}


		void				push_back (const value_type & val) {
			if (this->_size < this->_capacity)
			{
				_tab[_size] = val;
				this->_size++; 
			}
			else if (this->_size == 0) {
				this->_capacity++;
				_tab = _alloc.allocate(this->_capacity);
				this->_alloc.construct(this->_tab + this->_size, val);
				this->_size++;
			}
			else
			{
				this->_capacity *= 2;
				pointer tmp = _alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
				{
					_alloc.construct(tmp + i, _tab[i]);
					_alloc.destroy(_tab + i);
				}
				if (_capacity > 0)
				_alloc.deallocate(_tab, _capacity / 2);
				this->_tab = tmp;
				this->_tab[_size] = val;
				this->_size++;
			} 
		}

		void			pop_back(void){
			if (this->_size > 0) {
				this->_alloc.destroy(&this->_tab[--_size]);
			}
		}

		iterator		insert(iterator position, const value_type &val) {

			difference_type  i = position - _tab;

            if (_size == 0)
            {
                this->_tab = _alloc.allocate(_size + 1);
                 _alloc.construct(_tab + i, val);
                this->_capacity++;
            }
			else if ((_size + 1) > _capacity) {
				_capacity *= 2;
				pointer tmp;
				tmp = _alloc.allocate(_capacity);
				for (size_type j = 0; j < _size; j++) {
					_alloc.construct(tmp + j, _tab[j]);
					_alloc.destroy(_tab + j);
				}
				_alloc.deallocate(_tab, _capacity / 2);
				_tab = tmp;
				int j = _size - 1;
                while (j >= i)
                {
                    _tab[j + 1] = _tab[j];
                    j--;
                }
			}
			else {
                int j = _size - 1;
                while (j >= i)
                {
                    _tab[j + 1] = _tab[j];
                    j--;
                }
			}
            this->_size++;
			_tab[i] = val;
			return iterator(_tab + i);
		}

		void			insert (iterator position, size_type n, const value_type& val) {

			iterator it = position;
			for (size_type i = 0; i < n; i++)
				it = insert(it, val);
		}

		template <class InputIterator>
		void			insert(iterator position, InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr) {
            (void)enable;

			iterator it = position;
            for (;first != last; first++) {
				it = insert(it, *first);
				it++;
			}
		}

		iterator		erase (iterator position) {

			difference_type i = position - _tab;

			_alloc.destroy(_tab + i);
			while (i < static_cast<int>(_size))
			{
				_tab[i] = _tab[i + 1];
				i++;
			}
			this->_size--;
			return iterator(position);
		}

		iterator		erase(iterator first, iterator last) {

			iterator it = first;
			difference_type diff = last - first;

			for(; first != last; first++)
				erase(it);
			return first - diff;
		}

		void			swap(vector& x) {
		   std::swap(this->_tab,x._tab);
		   std::swap(this->_size,x._size);
		   std::swap(this->_capacity,x._capacity);
		}

		void			clear() {
			for (size_type i = 0; i < this->_size; ++i) {
				_alloc.destroy(_tab + i);
			}
			this->_size = 0;
		}

			//--------------------[ALLOCATOR]--------------------//

		allocator_type	get_allocator() const { return this->_alloc; }

			//--------------------[DEBUG]--------------------//
		protected :

		friend std::ostream & operator<<(std::ostream &o, vector const &rhs) 
		{
			o << "OUR VECTOR : \n";
			for(size_t i = 0;  i < rhs.size(); ++i)
				  o << rhs._tab[i] << " ";
			o << std::endl;
			o << "Size : " << rhs.size() << std::endl;
			o << "Capacity : " << rhs.capacity() << std::endl;
			return o;
		}


		pointer			_tab;
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;

	};

			//--------------------[NON-MEMBER FUNCTION OVERLOADS]--------------------//
			//----------[RELATIONAL OPERATOR]----------//

template<class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	ft::vector<int>::const_iterator it = lhs.begin();
	ft::vector<int>::const_iterator ite = lhs.end();
	ft::vector<int>::const_iterator it2 = rhs.begin();
	if (lhs.size() == rhs.size()) {
		while (it != ite){
			if(!(*it == *it2))
				return false;
			++it;
			++it2;
		}
		return true;
	}
	else
		return false;
}

template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	  return (!(lhs == rhs));
  }

template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	ft::vector<int>::const_iterator first1 = lhs.begin();
	ft::vector<int>::const_iterator first2 = rhs.begin();
	ft::vector<int>::const_iterator last1 = lhs.end();
	ft::vector<int>::const_iterator last2 = rhs.end();

	while (first1!=last1)
  	{
  		if (first2==last2 || *first2<*first1) {
			return false;
		}
  		else if (*first1<*first2) {
			return true;
		}
  		++first1; ++first2;
  	}
  	return (first2!=last2);  
}

template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	  return (!(lhs > rhs));
  	}

template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	  return (rhs < lhs);
  	}

template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	  return (!(lhs < rhs));
  	}

template< class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}