#pragma once

#include "../utils.hpp"
#include "iterator_trait.hpp"
#include <unistd.h>

namespace ft{

	template<class Node, class key, class mapped_type>
		class mapIterator : public std::bidirectional_iterator_tag {

			public:

				typedef key											key_type;
				typedef Node*										pointer;
				typedef Node&										reference;
				typedef std::bidirectional_iterator_tag				iterator_category;
				typedef ptrdiff_t									difference_type;
				typedef ft::pair<key, mapped_type>					value_type;

			// constructors :
			explicit mapIterator( void ) : _rbt(nullptr){}
			mapIterator( Node k) : _rbt(&k){}
			mapIterator( pointer ptr ) : _rbt(ptr){}
			mapIterator( const mapIterator & other ) : _rbt(other._rbt){}
		
			// Operators
			mapIterator		operator=( const mapIterator & other ) { _rbt = other._rbt; return *this; }
			mapIterator		operator++( int ) {mapIterator tmp = *this;++(*this);return tmp;}
			mapIterator		operator--( int ) {mapIterator tmp = *this;--(*this);return tmp;}
			mapIterator&	operator++( void ) {this->_rbt = getNext(this->_rbt);return (*this);}
			mapIterator&	operator--( void ) {this->_rbt = getPrevious(this->_rbt);return (*this);}
			bool			operator!=(const mapIterator & other ) { return (this->_rbt != other._rbt); }
			bool			operator>(const mapIterator & other ) { return (this->_rbt < other._rbt); }
			bool			operator<(const mapIterator & other ) { return (this->_rbt > other._rbt); }
			bool			operator==(const mapIterator & other ) { return (this->_rbt == other._rbt); }
			value_type& 	operator*() {return (*(this->operator->()));}
			value_type& 	operator*() const {return (*(this->operator->()));}
			value_type*		operator->() {return (value_type*)&(this->_rbt->value);}
			value_type*		operator->() const {return (value_type*)&(this->_rbt->value);}
			
			operator mapIterator<const Node, const key, const mapped_type>() const {
				mapIterator<const Node, const key, const mapped_type> temp(this->_rbt);
				return (temp);
			}

			pointer 	base() const { return this->_rbt; }


			mapIterator operator- (difference_type n) const{
				static_cast<void>(n);
				mapIterator temp(getPrevious(this->_rbt));
				return (temp);
			}
			
			Node*	get_node() { return this->_rbt; }

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
    	class reverse_mapIterator {

        public:
        
            typedef Iterator                                                             iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category            iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type                   value_type;
            typedef typename ft::iterator_traits<Iterator>::pointer                      pointer;
            typedef typename ft::iterator_traits<Iterator>::reference                    reference;

            
            reverse_mapIterator() : _rbt(0){}
            explicit reverse_mapIterator (const iterator_type it) {_rbt = it;}
            
			template <class Iter>
            reverse_mapIterator(const reverse_mapIterator<Iter>& rev_it) {_rbt = rev_it.base();}
            reverse_mapIterator(const reverse_mapIterator &copy){*this = copy;}
            ~reverse_mapIterator() {}

			reverse_mapIterator&	operator=(const reverse_mapIterator &rhs){this->_rbt = rhs._rbt;return (*this);}

            operator reverse_mapIterator<const Iterator>() const {
                reverse_mapIterator<const Iterator> temp(this->_rbt);
                return (temp);
			}

			reverse_mapIterator&	operator++() {this->_rbt--;return (*this);}
            reverse_mapIterator 	operator++(int) {reverse_mapIterator temp = *this;++(*this);return (temp);}
            reverse_mapIterator&	operator++() const {(*this)++;return (*this);}
            reverse_mapIterator&	operator--() {this->_rbt++;return (*this);}
            reverse_mapIterator 	operator--(int) {reverse_mapIterator temp = *this;--(*this);return temp;}

            typename Iterator::value_type*	operator->() const{return ((_rbt - 1).operator->());}
            typename Iterator::value_type&	operator*() const{return (*(this->operator->()));}

			Iterator base() const{return (_rbt);}
		
		private:
			iterator_type	_rbt;
	};

	template <class Iterator, class T>
	bool operator== (const reverse_mapIterator<Iterator>& lhs, const reverse_mapIterator<T>& rhs){
		return (lhs.base() == rhs.base());
	}

	template <class Iterator, class T>
	bool operator!= (const reverse_mapIterator<Iterator>& lhs, const reverse_mapIterator<T>& rhs){
		return (lhs.base() != rhs.base());
	}
}