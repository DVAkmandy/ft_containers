#ifndef EQUAL_HPP
# define EQUAL_HPP

namespace ft
{
	template<class It1, class It2>
	bool equal(It1 first1, It1 last1, It2 first2) {
		while (first1 != last1) {
			if (*first1 != *first2) {
				return false;
			}
			++first1;
			++first2;
		}
		return true;
	}

	template<class It1, class It2, class BinaryPredicate>
	bool equal(It1 first1, It1 last1, It2 first2, BinaryPredicate p) {
		while (first1 != last1) {
			if (!p(*first1, *first2)) {
				return false;
			}
			++first1;
			++first2;
		}
		return true;
	}
}

#endif