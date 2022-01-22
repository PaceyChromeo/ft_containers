#pragma once

#include "../utils.hpp"
#include "iterator_trait.hpp"
#include <unistd.h>

namespace ft{

	template<class Node, class V>
		class setIterator : public std::bidirectional_iterator_tag {

			public:

				typedef const V								value_type;
				typedef Node*								pointer;
				typedef Node&								reference;
				typedef std::bidirectional_iterator_tag		iterator_category;
				typedef ptrdiff_t							difference_type;

			// constructors :
			explicit setIterator( void ) : _rbt(nullptr) {}
			setIterator( const Node& k) : _rbt(&k) {}
			setIterator( const pointer ptr ) : _rbt(ptr) {}
			setIterator( const setIterator<const Node, const V> & other ) : _rbt(other.get_node()) {}
			~setIterator() {}
		
			// Operators
			setIterator&		operator=( const setIterator & other ) { _rbt = other._rbt; return *this; }
			setIterator			operator++( int ) {setIterator tmp = *this;++(*this);return tmp;}
			setIterator			operator--( int ) {setIterator tmp = *this;--(*this);return tmp;}
			setIterator&		operator++( void ) {this->_rbt = getNext(this->_rbt);return (*this);}
			setIterator&		operator--( void ) {this->_rbt = getPrevious(this->_rbt);return (*this);}
			bool				operator!=(const setIterator & other ) { return (this->_rbt != other._rbt); }
			bool				operator>(const setIterator & other ) { return (this->_rbt < other._rbt); }
			bool				operator<(const setIterator & other ) { return (this->_rbt > other._rbt); }
			bool				operator==(const setIterator & other ) { return (this->_rbt == other._rbt); }
			const value_type& 	operator*() const {return (*(this->operator->()));}
			const value_type*	operator->() const {return (value_type*)&(this->_rbt->value);}
			
			operator setIterator<const Node, const V>() const {
				setIterator<const Node, const V> temp(this->_rbt);
				return (temp);
			}

			pointer 	base() const { return this->_rbt; }


			setIterator operator- (difference_type n) const{
				static_cast<void>(n);
				setIterator temp(getPrevious(this->_rbt));
				return (temp);
			}
			
			Node*	get_node() const { return this->_rbt; }

			Node*	getNext(Node *target) const {

				if (target->is_Nil == true) {
					return target;
				}
				if (target->right->is_Nil == true) {
					while (target->parent && target == target->parent->right && target->parent->is_end == false) {
						target = target->parent;
					}
					if (target->parent) {
						return target->parent;
					}
					else {
						return target;
					}
				}
				Node *min = minNode(target->right);
				if (min->is_Nil == true) {
					pointer tmp = target; 
					while (tmp->parent->value.first > target->value.first){
						tmp = tmp->parent;
					}
					return tmp;
				}
				return min;
			}


			Node*	getPrevious(Node *target) const {
				if (target->is_Nil == true) {
					return target;
				}
				if (target->left->is_Nil == true) {
					while (target->parent && target == target->parent->left && target->parent->is_end == false) {
						target = target->parent;
					}
					if (target->parent) {
						return target->parent;
					}
					else {
						return target;
					}
				}
				Node*	max = maxNode(target->left);
				if (max->is_Nil == true) {
					pointer tmp = target; 
					while (tmp->parent->value.first > target->value.first){
						tmp = tmp->parent;
					}
					return tmp;
				}
				return max;
			}

			Node*	maxNode(Node* node) const {
				while(node->right->is_Nil != true)
					node = node->right;
				return (node);
			}

			Node*	minNode(Node* node) const {
				while (node->left->is_Nil != true)
					node = node->left;
				return (node);
			}
			
			void	debug() {
				std::cout << "DEBUG : " << this->_rbt->value.first << " | " << this->_rbt->value.second << std::endl;
			}

			protected :
				pointer _rbt;
	};

	template <class Iterator>
    	class reverse_setIterator {

        public:
        
            typedef Iterator                                                             iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category            iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type                   value_type;
            typedef typename ft::iterator_traits<Iterator>::pointer                      pointer;
            typedef typename ft::iterator_traits<Iterator>::reference                    reference;

            
            reverse_setIterator() : _rbt(0){}
            explicit reverse_setIterator (const iterator_type it) {_rbt = it;}
            
			template <class Iter>
            reverse_setIterator(const reverse_setIterator<Iter>& rev_it) {_rbt = rev_it.base();}
            reverse_setIterator(const reverse_setIterator &copy){*this = copy;}
            ~reverse_setIterator() {}

			reverse_setIterator&	operator=(const reverse_setIterator &rhs){this->_rbt = rhs._rbt;return (*this);}

            operator reverse_setIterator<const Iterator>() const {
                reverse_setIterator<const Iterator> temp(this->_rbt);
                return (temp);
			}

			reverse_setIterator&	operator++() {this->_rbt--;return (*this);}
            reverse_setIterator 	operator++(int) {reverse_setIterator temp = *this;++(*this);return (temp);}
            reverse_setIterator&	operator++() const {(*this)++;return (*this);}
            reverse_setIterator&	operator--() {this->_rbt++;return (*this);}
            reverse_setIterator 	operator--(int) {reverse_setIterator temp = *this;--(*this);return temp;}

            typename Iterator::value_type*	operator->() const {return ((_rbt - 1).operator->());}
            typename Iterator::value_type&	operator*() const {return (*(this->operator->()));}

			Iterator base() const{return (_rbt);}
		
		private:
			iterator_type	_rbt;
	};

	template <class Iterator, class T>
	bool operator== (const reverse_setIterator<Iterator>& lhs, const reverse_setIterator<T>& rhs){
		return (lhs.base() == rhs.base());
	}

	template <class Iterator, class T>
	bool operator!= (const reverse_setIterator<Iterator>& lhs, const reverse_setIterator<T>& rhs){
		return (lhs.base() != rhs.base());
	}
}