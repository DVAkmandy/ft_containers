#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "../utils/type_traits.hpp"
# include "../utils/random_access_iterator.hpp"
# include "../utils/reverse_iterator.hpp"
# include "../utils/equal.hpp"
# include "../utils/lexicographical_compare.hpp"
# include <memory>
# include <stdexcept>
# include <algorithm>

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T																		value_type;
		typedef Allocator																allocator_type;

		typedef typename allocator_type::reference										reference;
		typedef typename allocator_type::const_reference								const_reference;
		typedef typename allocator_type::size_type										size_type;
		typedef typename allocator_type::difference_type								difference_type;
		typedef typename allocator_type::pointer										pointer;
		typedef typename allocator_type::const_pointer									const_pointer;

		typedef ft::random_access_iterator<value_type>									iterator;
		typedef ft::random_access_iterator<const value_type>							const_iterator;
		typedef ft::reverse_iterator<iterator>											reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;

	private:
		pointer			_arr;
		size_type 		_size;
		size_type 		_capacity;
		allocator_type	_alloc;

	public:
		vector() : _arr(0), _size(0), _capacity(0), _alloc(allocator_type()) {}
		explicit vector(const allocator_type& alloc) : _arr(0), _size(0), _capacity(0), _alloc(alloc) {}

		explicit vector(size_type n, const value_type& value = value_type(),
						const allocator_type& alloc = allocator_type()) : _arr(0), _size(0), _capacity(0), _alloc(alloc) {
			if (n >= 0) {
				reserve(n);
				for (size_t i = 0; i < n; ++i) {
					_alloc.construct(_arr + i, value);
				}
				this->_size = n;
			}
		}

		template<class InputIt>
		vector(InputIt first, InputIt last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0) :	_arr(0),
																								_size(0),
																								_capacity(0),
																								_alloc(alloc) {
			clear();
			reserve(std::distance(first, last));
			for (InputIt it = first; it != last; ++it) {
				_alloc.construct(_arr + _size, *it);
				++_size;
			}
		}

		vector(const vector& other) : _arr(0), _size(0), _capacity(0), _alloc(other._alloc) {
			clear();
			reserve(other._capacity);
			for (size_t i = 0; i < other._size; ++i) {
				this->_alloc.construct(this->_arr + i, other._arr[i]);
			}
			this->_size = other._size;
		}

		virtual ~vector(void) {
			clear();
			if (_capacity) {
				_alloc.deallocate(_arr, _capacity);
			}
		}

		vector& operator=(const vector& other) {
			if (this != &other) {
				clear();
				this->_alloc.deallocate(_arr, _capacity);
				this->_size = other.size();
				this->_capacity = other.capacity();
				this->_arr = _alloc.allocate(_capacity);
				for (size_t i = 0; i < other._size; ++i) {
					this->_alloc.construct(this->_arr + i, other._arr[i]);
				}
			}
			return *this;
		}

		void assign(size_type count, const value_type& value) {
			if (count > 0) {
				clear();
				reserve(count);
				for (size_t i = 0; i < count; ++i) {
					push_back(value);
				}
			}
		}

		template<class inputIt>
		void assign(inputIt first, inputIt last,
					typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type* = 0) {
			clear();
			reserve(std::distance(first, last));
			for (; first != last; ++first) {
				push_back(*first);
			}
		}

		allocator_type get_allocator(void) const {
			return this->_alloc;
		}

		reference at(size_type pos) {
			if (pos >= _size) {
				throw std::out_of_range("Out of range");
			}
			return *(_arr + pos);
		}

		const_reference at(size_type pos) const {
			if (pos >= _size) {
				throw std::out_of_range("Out of range");
			}
			return *(_arr + pos);
		}

		reference operator[](size_type pos) {
			return *(_arr + pos);
		}

		const_reference operator[](size_type pos) const {
			return *(_arr + pos);
		}

		reference front(void) {
			return *_arr;
		}

		const_reference front(void) const {
			return *_arr;
		}

		reference back(void) {
			return *(_arr + (_size - 1));
		}

		const_reference back(void) const {
			return *(_arr + (_size - 1));
		}

		pointer data(void) {
			return _arr;
		}

		const pointer data(void) const {
			return _arr;
		}

		iterator begin(void) {
			return iterator(_arr);
		}

		const_iterator begin(void) const {
			return const_iterator(_arr);
		}

		iterator end(void) {
			return iterator(_arr + _size);
		}

		const_iterator end(void) const {
			return const_iterator(_arr + _size);
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

		bool empty() const {
			return size() == 0;
		}

		size_type size(void) const {
			return _size;
		}

		size_type max_size() const {
			return _alloc.max_size();
		}

		void reserve(size_type n) {
			if (n > _capacity) {
				pointer newArr = _alloc.allocate(n);
				for (size_t i = 0; i < _size; ++i) {
					_alloc.construct(newArr + i, _arr[i]);
					_alloc.destroy(_arr + i);
				}
				_alloc.deallocate(_arr, _capacity);
				this->_arr = newArr;
				this->_capacity = n;
			}
		}

		size_type capacity(void) const {
			return _capacity;
		}

		void clear(void) {
			if (_arr) {
				for (size_t i = 0; i < _size; ++i) {
					_alloc.destroy(_arr + i);
				}
			}
			_size = 0;
		}

		iterator insert(iterator pos, const value_type& value) {
			difference_type start = std::distance(this->begin(), pos);
			size_type i = 0;
			if (_capacity == _size && _capacity) {
				reserve(2 * _capacity);
			} else {
				reserve(1);
			}
			for (i = _size; i > static_cast<size_type>(start); --i) {
				_arr[i] = _arr[i - 1];
			}
			_alloc.construct(_arr + i, value);
			++_size;
			return iterator(_arr + start);
		}

		void insert(iterator pos, size_type count, const value_type& value) {
			difference_type start = std::distance(this->begin(), pos);
			if (count == 0) {
				return;
			}
			size_type i = 0;
			if (_size + count > _capacity) {
				if (count > _size) {
					reserve(_size + count);
				} else {
					reserve(2 * _capacity);
				}
			}
			for (i = _size; i > static_cast<size_type>(start); --i) {
				_arr[i + count - 1] = _arr[i - 1];
			}
			for (i = 0; i < count; ++i) {
				_alloc.construct(_arr + start + i, value);
			}
			_size += count;
		}

		template<class InputIt>
		void insert(iterator pos, InputIt first, InputIt last,
					typename ft::enable_if< !ft::is_integral< InputIt >::value, InputIt >::type* = 0) {
			if (first == last) {
				return;
			}
			difference_type start = std::distance(this->begin(), pos);
			difference_type count = std::distance(first, last);
			if (_size + static_cast<size_type>(count) > _capacity) {
				if (static_cast<size_type>(count) > _size) {
					reserve(_size + static_cast<size_type>(count));
				} else {
					reserve(2 * _capacity);
				}
			}
			size_type i = 0;
			for (i = _size; i > static_cast<size_type>(start); --i) {
				_arr[i + static_cast<size_type>(count) - 1] = _arr[i - 1];
			}
			for (i = 0; i < static_cast<size_type>(count); ++i, ++first) {
				_alloc.construct(_arr + start + i, *first);
			}
			_size += count;
		}

		iterator erase(iterator pos) {
			difference_type start = std::distance(this->begin(), pos);
			_alloc.destroy(_arr + start);
			for (size_type i = static_cast<size_type>(start); i < _size - 1; ++i) {
				_arr[i] = _arr[i + 1];
			}
			--_size;
			return pos;
		}

		iterator erase(iterator first, iterator last) {
			difference_type start = std::distance(this->begin(), first);
			if (first == last) {
				return iterator(_arr + start);
			}
			difference_type count = std::distance(first, last);
			for (iterator it = first; it != last; ++it) {
				_alloc.destroy(&(*it));
			}
			for (size_type i = static_cast<size_type>(start); i < _size - count; ++i) {
				_arr[i] = _arr[i + count];
			}
			_size -= count;
			return first;
		}

		void push_back(const T& value) {
			if (_capacity == _size && _capacity) {
				reserve(2 * _size);
			} else {
				reserve(1);
			}
			_alloc.construct(_arr + _size, value);
			++_size;
		}

		void pop_back() {
			if (!_size) {
				return;
			}
			_alloc.destroy(_arr + (_size - 1));
			--_size;
		}

		void resize(size_type count, value_type value = value_type()) {
			if (count < _size) {
				while (_size > count) {
					pop_back();
				}
			} else if (count > _size) {
				while (_size < count) {
					push_back(value);
				}
			}
		}

		void swap(vector& other) {
			std::swap(_arr, other._arr);
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
			std::swap(_alloc, other._alloc);
		}
	};

	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template<class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template<class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return rhs < lhs;
	}

	template<class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template<class T, class Alloc>
	void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#endif