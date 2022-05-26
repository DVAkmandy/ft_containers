#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <cstddef>
# include <iterator>

namespace ft
{
	template<class T>
	class random_access_iterator {
	public:
		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef value_type*							pointer;
		typedef const value_type*					const_pointer;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef std::random_access_iterator_tag		iterator_category;

	private:
		pointer _ptr;

	public:
		random_access_iterator() : _ptr(0) {}
		explicit random_access_iterator(pointer ptr) : _ptr(ptr) {}
		random_access_iterator(const random_access_iterator& other) : _ptr(other._ptr) {}
		virtual ~random_access_iterator() {}

		random_access_iterator& operator=(const random_access_iterator& other) {
			if (this == &other) {
				return *this;
			}
			this->_ptr = other._ptr;
			return *this;
		}

		operator random_access_iterator<const value_type>() const {
			return random_access_iterator<const value_type>(_ptr);
		}

		reference operator*() {
			return *_ptr;
		}

		const_reference operator*() const {
			return *_ptr;
		}

		pointer operator->() {
			return _ptr;
		}

		const_pointer operator->() const {
			return _ptr;
		}

		reference operator[](difference_type n) {
			return *(_ptr + n);
		}

		const_reference operator[](difference_type n) const {
			return *(_ptr + n);
		}

		pointer base(void) const {
			return _ptr;
		}

		random_access_iterator& operator++() {
			++_ptr;
			return *this;
		}

		random_access_iterator& operator--() {
			--_ptr;
			return *this;
		}

		random_access_iterator operator++(int) {
			random_access_iterator copy = *this;
			++_ptr;
			return copy;
		}

		random_access_iterator operator--(int) {
			random_access_iterator copy = *this;
			--_ptr;
			return copy;
		}

		random_access_iterator& operator+=(difference_type n) {
			_ptr += n;
			return *this;
		}

		random_access_iterator& operator-=(difference_type n) {
			_ptr -= n;
			return *this;
		}

		random_access_iterator operator+(difference_type n) const {
			return random_access_iterator<T>(_ptr + n);
		}

		random_access_iterator operator-(difference_type n) const {
			return random_access_iterator<T>(_ptr - n);
		}

		difference_type operator+(const random_access_iterator& other) const {
			return base() + other.base();
		}

		difference_type operator-(const random_access_iterator& other) const {
			return base() - other.base();
		}

		bool operator==(const random_access_iterator& other) const {
			return base() == other.base();
		}

		bool operator!=(const random_access_iterator& other) const {
			return base() != other.base();
		}

		bool operator<(const random_access_iterator& other) const {
			return base() < other.base();
		}

		bool operator<=(const random_access_iterator& other) const {
			return base() <= other.base();
		}

		bool operator>(const random_access_iterator& other) const {
			return base() > other.base();
		}

		bool operator>=(const random_access_iterator& other) const {
			return base() >= other.base();
		}
	};

	template<class T, class U>
	bool operator==(random_access_iterator<T>& lhs, random_access_iterator<U>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class T, class U>
	bool operator!=(random_access_iterator<T>& lhs, random_access_iterator<U>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<class T, class U>
	bool operator<(random_access_iterator<T>& lhs, random_access_iterator<U>& rhs) {
		return lhs.base() < rhs.base();
	}

	template<class T, class U>
	bool operator<=(random_access_iterator<T>& lhs, random_access_iterator<U>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template<class T, class U>
	bool operator>(random_access_iterator<T>& lhs, random_access_iterator<U>& rhs) {
		return lhs.base() > rhs.base();
	}

	template<class T, class U>
	bool operator>=(random_access_iterator<T>& lhs, random_access_iterator<U>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template<class T>
	random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n,
															const random_access_iterator<T>& other) {
		return n + other;
	}
}

#endif