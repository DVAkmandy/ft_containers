#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
# include <memory>

namespace ft
{
	template<class Iter>
	class reverse_iterator {
	public:
		typedef Iter														iterator_type;
		typedef typename iterator_traits<Iter>::iterator_category			iterator_category;
		typedef typename iterator_traits<Iter>::value_type					value_type;
		typedef typename iterator_traits<Iter>::difference_type				difference_type;
		typedef typename iterator_traits<Iter>::pointer						pointer;
		typedef typename iterator_traits<Iter>::reference					reference;

	private:
		iterator_type _it;

	public:
		reverse_iterator() : _it(0) {}
		explicit reverse_iterator(iterator_type it) : _it(it) {}
		template<class U>
		reverse_iterator(const reverse_iterator<U>& other) : _it(other.base()) {}
		virtual ~reverse_iterator() {}

		reverse_iterator& operator=(const reverse_iterator& other) {
			if (this == &other) {
				return *this;
			}
			this->_it = other._it;
			return *this;
		}

		iterator_type base() const {
			return _it;
		}

		reference operator*() const {
			iterator_type tmp = _it;
			return *--tmp;
		}

		pointer operator->() const {
			return &operator*();
		}

		reference operator[](difference_type n) const {
			return base()[-n - 1];
		}

		reverse_iterator& operator++() {
			--_it;
			return *this;
		}

		reverse_iterator& operator--() {
			++_it;
			return *this;
		}

		reverse_iterator operator++(int) {
			reverse_iterator copy = *this;
			--_it;
			return copy;
		}

		reverse_iterator operator--(int) {
			reverse_iterator copy = *this;
			++_it;
			return copy;
		}

		reverse_iterator& operator+=(difference_type n) {
			_it -= n;
			return *this;
		}

		reverse_iterator& operator-=(difference_type n) {
			_it += n;
			return *this;
		}

		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator<Iter>(_it - n);
		}

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator<Iter>(_it + n);
		}

		bool operator==(const reverse_iterator& other) const {
			return this->base() == other.base();
		}

		bool operator!=(const reverse_iterator& other) const {
			return this->base() != other.base();
		}

		bool operator<(const reverse_iterator& other) const {
			return this->base() > other.base();
		}

		bool operator<=(const reverse_iterator& other) const {
			return this->base() >= other.base();
		}

		bool operator>(const reverse_iterator& other) const {
			return this->base() < other.base();
		}

		bool operator>=(const reverse_iterator& other) const {
			return this->base() <= other.base();
		}

	};

	template<class IteratorL, class IteratorR>
	bool operator==(reverse_iterator<IteratorL>& lhs, reverse_iterator<IteratorR>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class IteratorL, class IteratorR>
	bool operator!=(reverse_iterator<IteratorL>& lhs, reverse_iterator<IteratorR>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<class IteratorL, class IteratorR>
	bool operator<(reverse_iterator<IteratorL>& lhs, reverse_iterator<IteratorR>& rhs) {
		return lhs.base() > rhs.base();
	}

	template<class IteratorL, class IteratorR>
	bool operator<=(reverse_iterator<IteratorL>& lhs, reverse_iterator<IteratorR>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template<class IteratorL, class IteratorR>
	bool operator>(reverse_iterator<IteratorL>& lhs, reverse_iterator<IteratorR>& rhs) {
		return lhs.base() < rhs.base();
	}

	template<class IteratorL, class IteratorR>
	bool operator>=(reverse_iterator<IteratorL>& lhs, reverse_iterator<IteratorR>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template<class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
															const reverse_iterator<Iterator>& other) {
		return n + other;
	}

	template<class Iterator>
	reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n,
															const reverse_iterator<Iterator>& other) {
		return n - other;
	}

	template<class IteratorL, class IteratorR>
	typename reverse_iterator<IteratorL>::difference_type operator-(reverse_iterator<IteratorL>& lhs, reverse_iterator<IteratorR>& rhs) {
		return rhs.base() - lhs.base();
	}
}

#endif