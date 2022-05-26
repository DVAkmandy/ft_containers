#ifndef FUNCTIONAL_HPP
# define FUNCTIONAL_HPP

namespace ft
{
	template<class Argument1, class Argument2, class Result>
	struct binary_function {
		typedef Argument1 			first_argument_type;
		typedef Argument2 			second_argument_type;
		typedef Result 			    result_type;
	};

	template<class T>
	struct less : binary_function<T, T, bool> {
		bool operator()(const T& lhs, const T& rhs) const {
			return lhs < rhs;
		}
	};
}

#endif