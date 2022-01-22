#pragma once

#include <iostream>
#include <limits>
#include "../iterator/mapIterator.hpp"

enum	e_color {BLACK, RED};

template < class key, class mapped_type >
			struct Node {
				typedef ft::pair<key, mapped_type>								value_type;

				struct Node*	left;
				struct Node*	right;
				struct Node*	parent;
				value_type		value;
				enum e_color	color;
				bool			is_end;
				bool			is_Nil;
			};

template < class key, class mapped_type, class Compare = std::less<key>, class Alloc = std::allocator<Node< key, mapped_type> > >
	class	RBtree {

		public :
			typedef Alloc														allocator_type;
			typedef Node< key,mapped_type>										Node;
			typedef ft::pair< key, mapped_type>									value_type;
			typedef Compare														key_compare;
			typedef	ft::mapIterator<Node, key, mapped_type>						iterator;
			typedef	ft::mapIterator<const Node, const key, const mapped_type>	const_iterator;
			typedef	ft::reverse_mapIterator<iterator>							reverse_iterator;
			typedef	ft::reverse_mapIterator<const_iterator>						const_reverse_iterator;
			typedef size_t														size_type;
			typedef ptrdiff_t													difference_type;
			typedef key															key_type;

			class value_compare : public std::binary_function<value_type,value_type,bool>{
				protected:
					key_compare	_comp;
				
				public:
					value_compare (key_compare c) : _comp(c) {}
					bool operator() (const value_type& x, const value_type& y) const{
						return comp(x.first, y.first);
					}
		};

			typedef struct RBtree_s{
				Node* root;
				Node* NIL;
			}				RBT;


		private:

			RBT				_rbt;
			Node			*_end;
			allocator_type	_alloc;
			size_type		_size;
			key_compare		_comp;

			void	printTreeHelper(Node* node, std::string indent, bool last) {
				if (node != this->_rbt.NIL && node != _end) {
					if (node != this->_rbt.NIL && node != _end) {
						std::cout << indent;
						if (last) {
							std::cout << "R----";
							indent += "   ";
						}
						else {
							std::cout << "L----";
							indent += "|  ";
						}
					std::string sColor = node->color ? "RED" : "BLACK";
					std::cout << node->value.first << "(" << sColor << ")" << std::endl;
					printTreeHelper(node->left, indent, false);
					if (node->right != this->_rbt.NIL)
						printTreeHelper(node->right, indent, true);
					}
				}
			};

		public:

			explicit RBtree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp){
				this->_rbt.NIL = createNILNode();
				this->_rbt.root = this->_rbt.NIL;
				this->_end = _alloc.allocate(1);
				this->_end->is_end = true;
				this->_end->is_Nil = false;
				this->_end->right = nullptr;
				this->_end->value = ft::make_pair(key_type(), mapped_type());
				this->_end->color = BLACK;
				this->_size = 0;
			};

			RBtree(const RBtree& cp) {
				_rbt.root = cp.getRbtRoot();
				_rbt.NIL = createNILNode();
				this->_end = _alloc.allocate(1);
				this->_rbt.root->parent = this->_end;
				this->_end->color = BLACK;
			};

			~RBtree() { };

			//----------[Operator]----------//
			RBtree& operator=(const RBtree & rhs) {
				if (this != &rhs){
					this->clear();
					this->_alloc = rhs._alloc;
					this->_comp = rhs._comp;
					this->_size = rhs.size;
					this->insert(rhs.begin(), rhs.end());
				}
				return *this;
			};

			//----------[Iterator]-----------//
			iterator	begin() {
				return iterator(min_Node(_rbt.root)); 
			}

			const_iterator	begin() const {
				return const_iterator(min_Node(_rbt.root)); 
			}

			iterator	end() {
				if (this->_size){
					this->_end->parent = nullptr;
					this->_rbt.root->parent = this->_end;
					this->_end->left = this->_rbt.root;
				}
				return (iterator(this->_end));
			}

			const_iterator	end() const {
				if (this->_size){
					this->_end->parent = nullptr;
					this->_rbt.root->parent = this->_end;
					this->_end->left = this->_rbt.root;
				}
				return (const_iterator(this->_end));
			}

			reverse_iterator	rbegin() {
				return reverse_iterator(this->end());
			}

			const_reverse_iterator	rbegin(void) const {
				return const_reverse_iterator(this->end());
			}

			reverse_iterator	rend(void) {
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator	rend(void) const {
				return const_reverse_iterator(this->begin());
			}
			//----------[Capacity]-----------//
			bool empty(void) const{
				if (this->_rbt.root == this->_rbt.NIL)
					return true;
				return false;
			}

			size_type	size(void) const {
				return this->_size;
			}

			size_type	max_size(void) const { return  (this->_alloc.max_size()); }

			//----------[Element Access]-----------//
			mapped_type& operator[] (const key_type& k){

				Node* tmp = this->_rbt.root;

				while (tmp != this->_rbt.NIL){
					if (tmp->value.first == k)
						return (tmp->value.second);
					if (tmp->value.first < k)
						tmp = tmp->right;
					else
						tmp = tmp->left;
				}
				value_type pair = ft::make_pair(k, mapped_type());
				return this->insert(pair).first->second;
			}

			Node*	getRbtRoot() const {return (this->_rbt.root);};

			Node*	createNILNode() {
				Node* newNIL = _alloc.allocate(1);
				newNIL->left = nullptr;
				newNIL->right = nullptr;
				newNIL->parent = nullptr;
				newNIL->color = BLACK;
				newNIL->is_end = false;
				newNIL->is_Nil = true;
				return (newNIL);	
			};

			Node*	createNode(const value_type& value) {
				Node* newNode = _alloc.allocate(1);
				newNode->is_end = false;
				newNode->left = this->_rbt.NIL;
				newNode->right = this->_rbt.NIL;
				newNode->parent = this->_rbt.NIL;
				newNode->value = value;
				newNode->color = RED;
				newNode->is_Nil = false;
				return (newNode);
			};
	
			ft::pair<iterator, bool>	insert(const value_type &value) {
				Node*	y = nullptr;
				Node*	x = this->_rbt.root;
				iterator it = find(value.first);

				if (it != this->end()){
					return ft::make_pair(it, false);
				}
				Node*	newNode = createNode(value);
				while (x != this->_rbt.NIL){
					y = x;
					if (_comp(x->value.first, newNode->value.first)) {
						x = x->right;
					}
					else {
						x = x->left;
					}
				}
				newNode->parent = y;
				if (y == nullptr) {
					this->_rbt.root = newNode;
					this->_rbt.root->parent = this->_end;
					this->_end->left = this->_rbt.root;
				}
				else if (_comp(newNode->value.first, y->value.first))
					y->left = newNode;
				else
					y->right = newNode;
				balance_after_insert(newNode);
				this->_rbt.root->parent = _end;
				this->_end->left = this->_rbt.root;
				this->_size++;
				return ft::make_pair(iterator(newNode), true);
			};

			iterator insert(iterator position, const value_type& val) {
				(void)position;
				this->insert(val);
				iterator it = find(val.first);
				return it;
			}

			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last) {
				while (first != last){
					insert(*first);
					first++;
				}
			}

			void erase(iterator position) {
				if (this->_size > 0)
					this->delete_Node(*position);
			}

			size_type erase (const key_type& k) {
				iterator find = this->find(k);
				if (find != this->end()) {
					this->erase(find);
					return 1;
				}
				return 0;
			}

			void erase (iterator first, iterator last) {		
				iterator tmp = first;
				while (first != last) {
					first++;
					this->erase(tmp);
					tmp = first;
				}
			}

			void	swap(RBtree &x) {
				RBT tmp_rbt = x._rbt; 
				Node* tmp_end = x._end;
				size_type tmp_size = x._size;
			
				x._rbt = this->_rbt;
				x._end = this->_end;
				x._size = this->_size;

				this->_rbt = tmp_rbt;
				this->_end = tmp_end;
				this->_size = tmp_size;			
			}

			void		clear() {
				this->erase(this->begin(), this->end());
			};

			key_compare key_comp() const { return this->_comp; }
			
			value_compare value_comp() const { return this->_comp; }

			iterator find(const key_type &k) {
				iterator it = this->begin();

				while (it != this->end()) {
					if (it->first == k)
						return it;
					it++;
				}
				return this->end();
			}

			const_iterator find(const key_type& k) const {
				const_iterator it = this->begin();
				const_iterator ite = this->end();

				while (it != ite) {
					if (it->first == k)
						return it;
					it++;
				}
				return this->end();
			}

			size_type count (const key_type& k) const {
				if (find(k) != this->end())
					return 1;
				return 0;
			}

			iterator lower_bound (const key_type& k) {
				iterator it = this->begin();
				iterator ite = this->end();

				while (it != ite) {
					if (_comp(it->first, k) == false)
						return it;
					it++;
				}
				return this->end();
			}

			const_iterator lower_bound (const key_type& k) const {
				const_iterator it = this->begin();
				const_iterator ite = this->end();

				while (it != ite) {
					if (_comp(it->first, k) == false)
						return it;
					it++;
				}
				return this->end();
			}

			iterator upper_bound (const key_type& k) {
				iterator it = this->begin();
				iterator ite = this->end();

				while (it != ite) {
					if (_comp(k, it->first) == true)
						return it;
					it++;
				}
				return this->end();

			}

			const_iterator upper_bound (const key_type& k) const {
				const_iterator it = this->begin();
				const_iterator ite = this->end();

				while (it != ite) {
					if (_comp(k, it->first) == true)
						return it;
					it++;
				}
				return this->end();
			}

			ft::pair<iterator,iterator>             equal_range (const key_type& k){
  				return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}
			
			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
  				return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			};

			allocator_type	get_allocator() const {return (this->_alloc);};
			
			//------------------ HELPER FUNC ------------------------------//

			bool search_val(const value_type & value) {
				Node* tmp = this->_rbt.root;

				while (tmp != this->_rbt.NIL){
					if (tmp->value.first == value.first)
						return (true);
					if (_comp(tmp->value.first, value.first))
						tmp = tmp->right;
					else
						tmp = tmp->left;
				}
				return false;
			}

			void	balance_after_insert(Node* k){
				Node* u;

				while (k->parent && k->parent->color == RED){
					if (k->parent == k->parent->parent->right){
						u = k->parent->parent->left;
						if (u->color == RED){
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else{
							if (k == k->parent->left){
								k = k->parent;
								right_rotation(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							left_rotation(k->parent->parent);
						}
					}
					else {
						u = k->parent->parent->right;
						if (u->color == RED){
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else{
							if (k == k->parent->right){
								k = k->parent;
								left_rotation(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							right_rotation(k->parent->parent);
						}
					}
					if (k == this->_rbt.root)
						break ;
				}
				this->_rbt.root->color = BLACK;
			};

			void	delete_Node(value_type value) {
				Node*	z = search_Node(value);
				Node*	y = nullptr;
				Node*	x = nullptr;

				if (z == this->_end)
					return ;
				enum e_color color = z->color;
				if (z->left == this->_rbt.NIL && z->right == this->_rbt.NIL){
					x = z->right;
					transplant_Node(z, z->right);
					if (z == this->_rbt.root)
						this->_rbt.root = this->_rbt.NIL;
				}
				else if (z->right != this->_rbt.NIL && z->left != this->_rbt.NIL){
					y = min_Node(z->right);
					color = y->color;
					x = y->right;
					if (y->parent == z) {
						x->parent = y;
					}
					else {
						transplant_Node(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					transplant_Node(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				else {
					if (z->left == this->_rbt.NIL) {
						x = z->right;
						transplant_Node(z, z->right);
					}
					else {
						x = z->left;
						transplant_Node(z, z->left);
					}
				}
				_alloc.deallocate(z, 1);
				if (color == BLACK && this->_size > 1)
					balance_after_delete(x);
				this->_rbt.NIL->parent = nullptr;
				this->_size--;
			};

			void	balance_after_delete(Node* x) {
				Node* s = nullptr;
				
				while (x != this->_rbt.root && x->color == BLACK) {
					s = nullptr;
					if (x == x->parent->left) {
						s = x->parent->right;
						if (s->color == RED) {
							s->color = BLACK;
							x->parent->color = RED;
							left_rotation(x->parent);
							s = x->parent->right;
						}
						if (s->left->color == BLACK && s->right->color == BLACK) {
							s->color = RED;
							x = x->parent;
						}
						else {
							if(s->right->color == BLACK) {
								s->left->color = BLACK;
								s->color = RED;
								right_rotation(s);
								s = x->parent->right;
							}
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->right->color = BLACK;
							left_rotation(x->parent);
							x = this->_rbt.root;
						}
					}
					else {
						s = x->parent->left;
						if (s->color == RED) {
							s->color = BLACK;
							x->parent->color = RED;
							right_rotation(x->parent);
							s = x->parent->left;
						}
						if (s->right->color == BLACK && s->left->color == BLACK) {
							s->color = RED;
							x = x->parent;
						}
						else {
							if (s->left->color == BLACK) {
								s->left->color = BLACK;
								s->color = RED;
								left_rotation(s);
								s = x->parent->left;
							}
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->left->color = BLACK;
							right_rotation(s);
							x = this->_rbt.root;
						}
					}
				}
				x->color = BLACK;
				this->_rbt.root->color = BLACK;
			}

			void	transplant_Node(Node* n1, Node* n2){
				if (n1->parent == nullptr || n1->parent == this->_end) {
					n2->parent = this->_rbt.root->parent;
					this->_rbt.root = n2;
				}
				else if (n1 == n1->parent->left){
					n2->parent = n1->parent;
					n1->parent->left = n2;
				}
				else {
					n2->parent = n1->parent;
					n1->parent->right = n2;
				}
			};

			Node*	max_Node(Node* node) {
				if (this->_rbt.root == this->_rbt.NIL)
					return this->_end;
				while(node->right != this->_rbt.NIL)
					node = node->right;
				return (node);
			}
			Node*	min_Node(Node* node){
				if (this->_rbt.root == this->_rbt.NIL)
					return this->_end;
				while (node->left != this->_rbt.NIL)
					node = node->left;
				return (node);
			};

			Node*	max_Node(Node* node) const {
				if (this->_rbt.root == this->_rbt.NIL)
					return this->_end;
				while(node->right != this->_rbt.NIL)
					node = node->right;
				return (node);
			}
			Node*	min_Node(Node* node) const {
				if (this->_rbt.root == this->_rbt.NIL)
					return this->_end;
				while (node->left != this->_rbt.NIL)
					node = node->left;
				return (node);
			};

			Node*	search_Node(value_type value){
				Node* tmp = this->_rbt.root;

				while (tmp != this->_rbt.NIL){
					if (tmp->value.first == value.first)
						return (tmp);
					if (_comp(tmp->value.first, value.first))
						tmp = tmp->right;
					else
						tmp = tmp->left;
				}
				return (this->_end);
			}

			void	left_rotation(Node* node) {
				Node* y = node->right;
				node->right = y->left;

				if (y->left != this->_rbt.NIL) {
					y->left->parent = node;
				}
				y->parent = node->parent;
				if (node->parent == nullptr || node->parent == this->_end) {
					this->_rbt.root = y;
				}
				else if (node == node->parent->left) {
					node->parent->left = y;
				}
				else {
					node->parent->right = y;
				}
				y->left = node;
				node->parent = y;
			};

			void	right_rotation(Node* node) {
				Node* y = node->left;
				node->left = y->right;

				if (y->right != this->_rbt.NIL) {
					y->right->parent = node;
				}
				y->parent = node->parent;
				if (node->parent == nullptr || node->parent == this->_end) {
					this->_rbt.root = y;
				}
				else if (node == node->parent->right) {
					node->parent->right = y;
				}
				else {
					node->parent->left = y;
				}
				y->right = node;
				node->parent = y;
			};

			/* *********** DEBUG ***************** */
			void	printRoot(Node* node){
				std::cout << "root : " << node->value.first << " | " << node->value.second << std::endl;
			};

			void	printTree() {
				printRoot(this->_rbt.root);
				if (this->_rbt.root)
					printTreeHelper(this->_rbt.root, "", true);
			};
	};