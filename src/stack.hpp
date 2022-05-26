#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template<class T, class Container = ft::vector<T> >
	class stack {
	public:
		typedef Container																	container_type;
		typedef typename container_type::value_type											value_type;
		typedef typename container_type::size_type											size_type;
		typedef typename container_type::reference											reference;
		typedef typename container_type::const_reference 									const_reference;

	protected:
		container_type	_c;

	public:
		explicit stack(const container_type& cont = container_type()) : _c(cont) {}

		stack(const stack& other) : _c(other._c) {}

		~stack(void) {}

		stack& operator=(const stack& other) {
			if (this == &other) {
				return *this;
			}
			_c = other._c;
			return *this;
		}

		reference top(void) {
			return _c.back();
		}

		const_reference top(void) const {
			return _c.back();
		}

		bool empty(void) const {
			return _c.empty();
		}

		size_type size(void) const {
			return _c.size();
		}

		void push(const value_type& value) {
			return _c.push_back(value);
		}

		void pop(void) {
			return _c.pop_back();
		}

		template<class U, class Cont>
		friend bool operator==(const ft::stack<U, Cont>& lhs, const ft::stack<U, Cont>& rhs);

		template<class U, class Cont>
		friend bool operator!=(const ft::stack<U, Cont>& lhs, const ft::stack<U, Cont>& rhs);

		template<class U, class Cont>
		friend bool operator<(const ft::stack<U, Cont>& lhs, const ft::stack<U, Cont>& rhs);

		template<class U, class Cont>
		friend bool operator<=(const ft::stack<U, Cont>& lhs, const ft::stack<U, Cont>& rhs);

		template<class U, class Cont>
		friend bool operator>(const ft::stack<U, Cont>& lhs, const ft::stack<U, Cont>& rhs);

		template<class U, class Cont>
		friend bool operator>=(const ft::stack<U, Cont>& lhs, const ft::stack<U, Cont>& rhs);
	};

	template<class T, class Container>
	bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
		return lhs._c == rhs._c;
	}

	template<class T, class Container>
	bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
		return lhs._c != rhs._c;
	}

	template<class T, class Container>
	bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
		return lhs._c < rhs._c;
	}

	template<class T, class Container>
	bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
		return lhs._c <= rhs._c;
	}

	template<class T, class Container>
	bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
		return lhs._c > rhs._c;
	}

	template<class T, class Container>
	bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
		return lhs._c >= rhs._c;
	}
}

#endif