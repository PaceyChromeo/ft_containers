#pragma once
#include "../vector/vector.hpp"
#include "iterator_trait.hpp"

namespace ft {

		//--------------------[Iterators]--------------------//
template <class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator {

		public :

        typedef T         						value_type;
        typedef Distance  						difference_type;
        typedef Pointer   						pointer;
        typedef Reference 						reference;
        typedef std::random_access_iterator_tag iterator_category;

		//----------[Constructor]----------//
		iterator (void) { return ; }
		iterator (pointer p) { current = p; }
		iterator (const iterator & copy ) { this->current = copy.current; }
		~iterator(void) { };
		//----------[                        ]----------//
		value_type & operator[](int n) { return this->current[n]; }
		bool operator==(const iterator &rhs) const { return this->current == rhs.current; }
		//----------[Arithmetic Operator]----------//
		iterator &operator=(iterator const & src) { current = src.current; return *this; }
		iterator & operator++() { current++; return *this; } //prefix ++
		iterator operator++( int ) { iterator tmp = *this; ++(*this) ; return tmp; } //postfix ++
		iterator & operator--() { current--; return *this; } //prefix ++
		iterator operator--( int ) { iterator tmp = *this; --(*this) ; return tmp; } //postfix ++
		iterator operator+(difference_type n) const { return iterator(this->current + n); }
		iterator operator-(difference_type n) const { return iterator(this->current - n); }
		iterator operator+=(difference_type n) { return this->current += n; }
		iterator operator-=(difference_type n) { return this->current -= n; }
		difference_type operator+(const iterator & rhs) const { return this->current - rhs.current; }
		difference_type operator-(const iterator & rhs) const { return this->current - rhs.current; }
		//----------[Special Operator]----------//
		reference operator*() { return *current; }
		pointer operator->(){ return current; }
		pointer operator->() const { return current; } 

		operator iterator<const T>() const {
                    iterator<const T> temp(this->current);
                return (temp);
   		}
		pointer base() const {return this->current; }

		private :
			pointer current;
	};

	template <typename T>
	iterator<T> operator+(typename iterator<T>::difference_type n, const iterator<T> lhs){
	    return (n + lhs.base());
	}

	template <typename T>
	iterator<T> operator-(typename iterator<T>::difference_type n, const iterator<T> lhs){
	    return (n - lhs.base());
	}

	template <class Iterator1, class Iterator2>
	  typename iterator<Iterator1>::difference_type operator-(
	    const iterator<Iterator1>& lhs,
	    const iterator<Iterator2>& rhs)
	 	{ return lhs.base() - rhs.base(); }

	template <class Iterator1, class Iterator2>
	  typename iterator<Iterator1>::difference_type operator+(
	    const iterator<Iterator1>& lhs,
	    const iterator<Iterator2>& rhs)
	 	{ return lhs.base() + rhs.base(); }

	template< class T, class T2 >
	bool operator==( const iterator<T>& lhs, const iterator<T2>& rhs ) { return lhs.base() == rhs.base(); }

	template< class T, class T2 >
	bool operator!=( const iterator<T>& lhs, const iterator<T2>& rhs ) { return lhs.base() != rhs.base(); }

	template< class T, class T2 >
	bool operator<( const iterator<T>& lhs, const iterator<T2>& rhs ) { return lhs.base() < rhs.base(); }

	template< class T, class T2 >
	bool operator<=( const iterator<T>& lhs, const iterator<T2>& rhs ) { return lhs.base() <= rhs.base(); }

	template< class T, class T2 >
	bool operator>( const iterator<T>& lhs, const iterator<T2>& rhs ) { return lhs.base() > rhs.base(); }

	template< class T, class T2 >
	bool operator>=( const iterator<T>& lhs, const iterator<T2>& rhs ) { return lhs.base() >= rhs.base(); }

		//--------------------[Reverse Iterators]--------------------//
template <class T>
	class reverse_iterator{

		public :

        typedef T													iterator_type;
        typedef typename ft::iterator_traits<T>::value_type			value_type;
        typedef typename ft::iterator_traits<T>::difference_type	difference_type;
        typedef typename ft::iterator_traits<T>::pointer			pointer;
        typedef typename ft::iterator_traits<T>::reference			reference;
        typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;

		//----------[Constructor]----------//
		template<class G>
		reverse_iterator (const reverse_iterator<G> &r) : current(r.base() - 1) {} 
		reverse_iterator (void) : current(0){}
		reverse_iterator (const iterator_type &it) : current(it - 1) {}
		~reverse_iterator(void) { }
		//----------[Special]----------//
		reverse_iterator &operator=(reverse_iterator const & src) { current = src.current; return *this; }
		iterator_type base() const {return this->current + 1; }
		reference operator*() {return *(current);}
		//----------[Arithmetic Operator]----------//
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(this->base() - n); }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(this->base() + n); }
		reverse_iterator operator++() { current--; return *this; } //prefix ++
		reverse_iterator operator++( int ) { 
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
			} //postfix ++
		reverse_iterator operator--() { current++; return *this; } //prefix ++
		reverse_iterator operator--( int ) { 
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
			} //postfix ++
		reverse_iterator operator+=(difference_type n) { this->current -= n;return *this;}
		reverse_iterator operator-=(difference_type n) { this->current += n;return *this;}
		//----------[Special Operator]----------//
		pointer operator->(){ return current.operator->(); }
		pointer operator->() const { return current.operator->(); }
		reference operator[](int n) { return *(this->current - n); }

		private :
			iterator_type current;
	};

	template <typename T>
	reverse_iterator<T> operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> lhs){
	    return reverse_iterator<T>(lhs.base() - n);
	}

	template <typename T>
	reverse_iterator<T> operator-(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> lhs){
	    return reverse_iterator<T>(lhs.base() + n);
	}

	template <class Iterator1, class Iterator2>
	  typename reverse_iterator<Iterator1>::difference_type operator-(
	    const reverse_iterator<Iterator1>& lhs,
	    const reverse_iterator<Iterator2>& rhs)
	 	{ return rhs.base() - lhs.base(); }

	template <class Iterator1, class Iterator2>
	  typename reverse_iterator<Iterator1>::difference_type operator+(
	    const reverse_iterator<Iterator1>& lhs,
	    const reverse_iterator<Iterator2>& rhs)
	 	{ return rhs.base() + lhs.base(); }

	template< class T, class T2 >
	bool operator==( const reverse_iterator<T>& lhs, const reverse_iterator<T2>& rhs ) { return lhs.base() == rhs.base(); }

	template< class T, class T2 >
	bool operator!=( const reverse_iterator<T>& lhs, const reverse_iterator<T2>& rhs ) { return lhs.base() != rhs.base(); }

	template< class T, class T2 >
	bool operator<( const reverse_iterator<T>& lhs, const reverse_iterator<T2>& rhs ) { return lhs.base() > rhs.base(); }

	template< class T, class T2 >
	bool operator<=( const reverse_iterator<T>& lhs, const reverse_iterator<T2>& rhs ) { return lhs.base() >= rhs.base(); }

	template< class T, class T2 >
	bool operator>( const reverse_iterator<T>& lhs, const reverse_iterator<T2>& rhs ) { return lhs.base() < rhs.base(); }

	template< class T, class T2 >
	bool operator>=( const reverse_iterator<T>& lhs, const reverse_iterator<T2>& rhs ) { return lhs.base() <= rhs.base(); }
}