#ifndef SET_HPP
# define SET_HPP

#include <memory>
#include "../utils/functional.hpp"
#include "../utils/pair.hpp"
#include "rb_tree_set.hpp"
#include "rbt_bidirectional_iterator.hpp"
#include "../utils/equal.hpp"
#include "../utils/lexicographical_compare.hpp"

namespace ft
{
	template<class Key, class Compare = ft::less<Key>,
			class Allocator = std::allocator<Key> >
	class set {
	public:
		typedef Key																		key_type;
		typedef Key																		value_type;
		typedef std::size_t																size_type;
		typedef std::ptrdiff_t															difference_type;
		typedef Compare																	key_compare;
		typedef Compare																	value_compare;
		typedef Allocator																allocator_type;
		typedef typename ft::red_black_tree<value_type, key_compare, allocator_type>	tree_type;
		typedef value_type&																reference;
		typedef const value_type&														const_reference;
		typedef value_type*																pointer;
		typedef const value_type*														const_pointer;
		typedef typename tree_type::iterator											iterator;
		typedef typename tree_type::const_iterator										const_iterator;
		typedef typename tree_type::reverse_iterator									reverse_iterator;
		typedef typename tree_type::const_reverse_iterator								const_reverse_iterator;

		private:
			tree_type _tree;

	public:
		explicit set(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _tree(comp, allocator_type(alloc)) {}

		template<class InputIt>
		set(InputIt first, InputIt last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _tree(comp, allocator_type(alloc)) {
			_tree.insert(first, last);
		}

		set(const set& other) : _tree(other._tree) {}

		~set() {
			clear();
		}

		set& operator=(const set& other) {
			_tree = other._tree;
			return *this;
		}

		allocator_type get_allocator(void) const {
			return allocator_type(_tree.get_allocator());
		}

		iterator begin(void) {
			return _tree.begin();
		}

		const_iterator begin(void) const {
			return _tree.begin();
		}

		iterator end(void) {
			return _tree.end();
		}

		const_iterator end(void) const {
			return _tree.end();
		}

		reverse_iterator rbegin(void) {
			return _tree.rbegin();
		}

		const_reverse_iterator rbegin(void) const {
			return _tree.rbegin();
		}

		reverse_iterator rend(void) {
			return _tree.rend();
		}

		const_reverse_iterator rend(void) const {
			return _tree.rend();
		}

		bool empty(void) const {
			return _tree.empty();
		}

		size_type size(void) const {
			return _tree.size();
		}

		size_type max_size(void) const {
			return _tree.max_size();
		}

		void clear(void) {
			_tree.clear();
		}

		ft::pair<iterator, bool> insert(const value_type& value) {
			return _tree.insert(value);
		}

		iterator insert(iterator hint, const value_type& value) {
			return _tree.insert(hint, value);
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last) {
			_tree.insert(first, last);
		}

		void erase(iterator pos) {
			_tree.erase(pos);
		}

		void erase(iterator first, iterator last) {
			_tree.erase(first, last);
		}

		size_type erase(const key_type& key) {
			return _tree.erase(key);
		}

		void swap(set& other) {
			set tmp = *this;
			*this = other;
			other = tmp;
		}

		size_type count(const key_type& key) {
			return _tree.count(key);
		}

		iterator find(const key_type& key) {
			return _tree.find(key);
		}

		const_iterator find(const key_type& key) const {
			return _tree.find(key);
		}

		ft::pair<iterator, iterator> equal_range(const key_type& key) {
			return _tree.equal_range(key);
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
			return _tree.equal_range(key);
		}

		iterator lower_bound(const key_type& key) {
			return _tree.lower_bound(key);
		}

		const_iterator lower_bound(const key_type& key) const {
			return _tree.lower_bound(key);
		}

		iterator upper_bound(const key_type& key) {
			return _tree.upper_bound(key);
		}

		const_iterator upper_bound(const key_type& key) const {
			return _tree.upper_bound(key);
		}

		key_compare key_comp(void) const {
			return _tree.key_comp();
		}

		value_compare value_comp(void) const {
			return value_compare(key_comp());
		}
	};

	template<class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && lhs.size() == rhs.size();
	}

	template<class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return lhs < rhs || lhs == rhs;
	}

	template<class Key, class Compare, class Alloc>
	bool operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return rhs < lhs;
	}

	template<class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return rhs <= lhs;
	}

	template<class Key, class Compare, class Alloc>
	void swap(set<Key, Compare, Alloc>& lhs, set<Key, Compare, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#endif