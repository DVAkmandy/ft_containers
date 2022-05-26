#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{
	template<class It1, class It2>
	bool lexicographical_compare(It1 first1, It1 last1, It2 first2, It2 last2) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				return true;
			} else if (*first2 < *first1) {
				return false;
			}
			++first1;
			++first2;
		}
		return first1 == last1 && first2 != last2;
	}

	template<class It1, class It2, class Compare>
	bool lexicographical_compare(It1 first1, It1 last1, It2 first2, It2 last2, Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2)) {
				return true;
			} else if (comp(*first2, *first1)) {
				return false;
			}
			++first1;
			++first2;
		}
		return first1 == last1 && first2 != last2;
	}
}

#endif