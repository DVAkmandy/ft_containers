#ifndef RB_TREE_SET_HPP
# define RB_TREE_SET_HPP

# include <cstddef>
# include <iostream>
# include <stdexcept>
# include "set.hpp"
# include "../utils/pair.hpp"
# include "rbt_bidirectional_iterator.hpp"
# include "../utils/functional.hpp"
# include "../utils/type_traits.hpp"


namespace ft
{
	enum color {RED, BLACK};

	template<class T>
	struct rbt_node {
		typedef T							value_type;
		value_type							data;
		rbt_node*							parent;
		rbt_node*							left;
		rbt_node*							right;
		color								color;

		rbt_node(value_type data) : data(data), parent(0), left(0), right(0), color(BLACK) {}
	};

	template<class T, class Compare = less<T>,
			class Allocator = std::allocator<T> >
	class red_black_tree {
	public:
		typedef T																value_type;
		typedef Compare															key_compare;
		typedef	rbt_node<value_type>											node_type;
		typedef	node_type*														pointer;
		typedef	const node_type*												const_pointer;
		typedef	node_type&														reference;
		typedef	const node_type&												const_reference;
		typedef typename Allocator::template rebind<node_type>::other			allocator_type;
		typedef std::size_t														size_type;
		typedef std::ptrdiff_t													difference_type;
		typedef ft::rbt_bidirectional_iterator<node_type>						iterator;
		typedef ft::rbt_bidirectional_iterator<const node_type>					const_iterator;
		typedef ft::reverse_iterator<iterator>									reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

	private:
		pointer			_root;
		pointer			_nil;
		key_compare		_comp;
		size_type		_size;
		allocator_type	_alloc;

	public:
		explicit red_black_tree(const key_compare& comp = key_compare(),
								const allocator_type& alloc = allocator_type()) :	_root(0), _nil(0), _comp(comp),
																					_size(0), _alloc(alloc) {
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, node_type(value_type()));
			_nil->color = BLACK;
			_root = _nil;
		}

		template<class InputIt>
		red_black_tree(InputIt first, InputIt last, const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type()) :	_root(0), _nil(0), _comp(comp),
																			_size(0), _alloc(alloc) {
			_nil = _alloc.allocate(1);
			_alloc.consruct(_nil, node_type(value_type()));
			_nil->color = BLACK;
			_root = _nil;
			insert(first, last);
		}

		red_black_tree(const red_black_tree& other) :	_root(0), _nil(0), _comp(other._comp),
																					_size(0), _alloc(other._alloc) {
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, node_type(value_type()));
			_nil->color = BLACK;
			_root = _nil;
			insert(other.begin(), other.end());
		}

		virtual ~red_black_tree(void) {
			clear();
			_delete_node(_nil);
		}

		red_black_tree& operator=(const red_black_tree& other) {
			if (this == &other) {
				return *this;
			}
			clear();
			_alloc = other._alloc;
			_comp = other._comp;
			insert(other.begin(), other.end());
			return *this;
		}

		allocator_type get_allocator(void) const {
			return _alloc;
		}

		iterator begin(void) {
			pointer tmp = _root;
			while (tmp->left != _nil && tmp != _nil) {
				tmp = tmp->left;
			}
			return iterator(tmp, _root, _nil);
		}

		const_iterator begin(void) const {
			pointer tmp = _root;
			while (tmp->left != _nil && tmp != _nil) {
				tmp = tmp->left;
			}
			return const_iterator(tmp, _root, _nil);
		}

		iterator end(void) {
			return iterator(_nil, _root, _nil);
		}

		const_iterator end(void) const {
			return const_iterator(_nil, _root, _nil);
		}

		reverse_iterator rbegin(void) {
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin(void) const {
			return const_reverse_iterator(end());
		}

		reverse_iterator rend(void) {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend(void) const {
			return const_reverse_iterator(begin());
		}

		bool empty(void) const {
			return _size == 0;
		}

		size_type size(void) const {
			return _size;
		}

		size_type max_size(void) const {
			return _alloc.max_size();
		}

		void clear(void) {
			_clear_help(_root);
			_root = _nil;
		}

		ft::pair<iterator, bool> insert(const value_type& value) {
			iterator it = find(value);
			if (it != end()) {
				return ft::make_pair(it, false);
			}
			pointer new_node = _create_node(node_type(value));
			if (_root == _nil) {
				new_node->color = BLACK;
				_root = new_node;
			} else {
				_insert_helper(new_node, _root);
			}
			it = iterator(new_node, _root, _nil);
			++_size;
			return ft::make_pair(it, true);
		}

		iterator insert(iterator hint, const value_type& value) {
			(void)hint;
			return insert(value).first;
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0) {
			while (first != last) {
				insert(*first);
				++first;
			}
		}

		void erase(iterator pos) {
			if (pos != end()) {
				_erase_helper(pos._ptr);
				--_size;
			}
		}

		void erase(iterator first, iterator last) {
			while (first != last) {
				erase(*first++);
			}
		}

		size_type erase(const value_type& key) {
			iterator it = find(key);
			if (it == end()) {
				return 0;
			}
			erase(it);
			return 1;
		}

		size_type count(const value_type& key) {
			if (find(key) != end()) {
				return 1;
			}
			return 0;
		}

		iterator find(const value_type& key) {
			pointer node = _search_key(key, _root);
			if (!node) {
				return end();
			}
			return iterator(node, _root, _nil);
		}

		const_iterator find(const value_type& key) const {
			pointer node = _search_key(key, _root);
			if (!node) {
				return end();
			}
			return const_iterator(node, _root, _nil);
		}

		ft::pair<iterator, iterator> equal_range(const value_type& key) {
			return ft::make_pair<iterator, iterator> (lower_bound(key), upper_bound(key));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const value_type& key) const {
			return ft::make_pair<const_iterator, const_iterator> (lower_bound(key), upper_bound(key));
		}

		iterator lower_bound(const value_type& key) {
			for (iterator it = begin(); it != end(); ++it) {
				if (!_comp(it._ptr->data, key)) {
					return it;
				}
			}
			return end();
		}

		const_iterator lower_bound(const value_type& key) const {
			for (const_iterator it = begin(); it != end(); ++it) {
				if (!_comp(it._ptr->data, key)) {
					return it;
				}
			}
			return end();
		}

		iterator upper_bound(const value_type& key) {
			for (iterator it = begin(); it != end(); ++it) {
				if (_comp(key, it._ptr->data)) {
					return it;
				}
			}
			return end();
		}

		const_iterator upper_bound(const value_type& key) const {
			for (const_iterator it = begin(); it != end(); ++it) {
				if (_comp(key, it._ptr->data)) {
					return it;
				}
			}
			return end();
		}

		key_compare key_comp(void) const {
			return key_compare();
		}

	private:
		void _clear_help(pointer node) {
			if (node == _nil) {
				return ;
			}
			_clear_help(node->left);
			_clear_help(node->right);
			_delete_node(node);
			--_size;
		}

		pointer _search_key(const value_type& key, const pointer& node) const {
			if (node == _nil) {
				return 0;
			} else if (node->data == key) {
				return node;
			}
			if (_comp(key, node->data)) {
				return _search_key(key, node->left);
			} else {
				return _search_key(key, node->right);
			}
		}

		pointer _create_node(const_reference value) {
			pointer node = _alloc.allocate(1);
			_alloc.construct(node, value);
			node->color = RED;
			node->parent = _nil;
			node->left = _nil;
			node->right = _nil;
			return node;
		}

		void _delete_node(pointer node) {
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		}

		void _rotate_left(pointer x) {
			pointer y = x->right;
			x->right = y->left;
			if (y->left != _nil) {
				y->left->parent = x;
			}
			if (y != _nil) {
				y->parent = x->parent;
			}
			if (x->parent != _nil) {
				if (x == x->parent->left) {
					x->parent->left = y;
				} else {
					x->parent->right = y;
				}
			} else {
				_root = y;
			}
			y->left = x;
			if (x != _nil) {
				x->parent = y;
			}
		}

		void _rotate_right(pointer x) {
			pointer y = x->left;
			x->left = y->right;
			if (y->right != _nil) {
				y->right->parent = x;
			}
			if (y != _nil) {
				y->parent = x->parent;
			}
			if (x->parent != _nil) {
				if (x == x->parent->right) {
					x->parent->right = y;
				} else {
					x->parent->left = y;
				}
			} else {
				_root = y;
			}
			y->right = x;
			if (x != _nil) {
				x->parent = y;
			}
		}

		void _insert_helper(pointer new_node, pointer node) {
			pointer current = node;
			pointer parent = 0;
			while (current != _nil) {
				parent = current;
				if (_comp(new_node->data, current->data)) {
					current = current->left;
				} else {
					current = current->right;
				}
			}
			new_node->parent = parent;
			if (_comp(new_node->data, parent->data)) {
				parent->left = new_node;
			} else {
				parent->right = new_node;
			}
			if (new_node->parent != _root) {
				_insert_fix_up(new_node);
			}
		}

		void _insert_fix_up(pointer node) {
			pointer uncle = 0;
			pointer parent = node->parent;
			pointer grandparent = node->parent->parent;
			while (node != _root && parent->color == RED) {
				if (parent == grandparent->left) {
					uncle = grandparent->right;
					if (uncle->color == RED) {
						parent->color = BLACK;
						uncle->color = BLACK;
						grandparent->color = RED;
						node = grandparent;
					} else {
						if (node == parent->right) {
							node = parent;
							_rotate_left(node);
						}
						parent->color = BLACK;
						grandparent->color = RED;
						_rotate_right(grandparent);
					}
				} else {
					uncle = grandparent->left;
					if (uncle->color == RED) {
						parent->color = BLACK;
						uncle->color = BLACK;
						grandparent->color = RED;
						node = grandparent;
					} else {
						if (node == parent->left) {
							node = parent;
							_rotate_right(node);
						}
						parent->color = BLACK;
						grandparent->color = RED;
						_rotate_left(grandparent);
					}
				}
			}
			_root->color = BLACK;
		}

		void _delete_fix_up(pointer node) {
			pointer tmp;
			while (node != _root && node->color == BLACK) {
				if (node == node->parent->left) {
					tmp = node->parent->right;
					if (tmp->color == RED) {
						tmp->color = BLACK;
						node->parent->color = RED;
						_rotate_left(node->parent);
						tmp = node->parent->right;
					}
					if (tmp->left->color == BLACK && tmp->right->color == BLACK) {
						tmp->color = RED;
						node = node->parent;
					} else {
						if (tmp->right->color == BLACK) {
							tmp->left->color = BLACK;
							tmp->color = RED;
							_rotate_right(tmp);
							tmp = node->parent->right;
						}
						tmp->color = node->parent->color;
						node->parent->color = BLACK;
						tmp->right->color = BLACK;
						_rotate_left(node->parent);
						node = _root;
					}
				} else {
					tmp = node->parent->left;
					if (tmp->color == RED) {
						tmp->color = BLACK;
						node->parent->color = RED;
						_rotate_right(node->parent);
						tmp = node->parent->left;
					}
					if (tmp->right->color == BLACK && tmp->left->color == BLACK) {
						tmp->color = RED;
						node = node->parent;
					} else {
						if (tmp->left->color == BLACK) {
							tmp->right->color = BLACK;
							tmp->color = RED;
							_rotate_left(tmp);
							tmp = node->parent->left;
						}
						tmp->color = node->parent->color;
						node->parent->color = BLACK;
						tmp->left->color = BLACK;
						_rotate_right(node->parent);
						node = _root;
					}
				}
			}
			node->color = BLACK;
		}

		void _erase_helper(pointer node) {
			pointer x = 0;
			pointer y = 0;
			if (!node || node == _nil) {
				return;
			}
			if (node->left == _nil || node->right == _nil) {
				y = node;
			} else {
				y = node->right;
				while (y->left != _nil) {
					y = y->left;
				}
			}
			if (y->left != _nil) {
				x = y->left;
			} else {
				x = y->right;
			}
			x->parent = y->parent;
			if (y->parent) {
				if (y == y->parent->left) {
					y->parent->left = x;
				} else {
					y->parent->right = x;
				}
			} else {
				_root = x;
			}
			if (y != node) {
				_delete_node(node);
				pointer p = _create_node(node_type(y->data));
				node = p;
			}
			if (y->color == BLACK) {
				_delete_fix_up(x);
			}
			_delete_node(y);
		}
	};
}


#endif