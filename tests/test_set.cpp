#include "../src/set.hpp"
#include <set>
#include <iostream>
#include <iomanip>

#define GREEN "\33[1;32m"
#define RED "\33[1;31m"
#define REST "\33[1;0m"


template<class T>
std::string
is_equal(const T &t1, const T &t2) { return t1 == t2 ? "ok" : "not ok"; }

template<class T>
std::string
is_equal_content(
        std::set<T> &stl_set,
        ft::set<T> &ft_set
) {
    typename ft::set<T>::iterator ft_it;
    typename std::set<T>::iterator stl_it;

    if (ft_set.size() != stl_set.size())
        return ("NOT EQUAL");
    stl_it = stl_set.begin();
    ft_it = ft_set.begin();
    while (ft_it != ft_set.end()) {
        if (*ft_it != *stl_it)
            return ("NOT EQUAL");
        stl_it++;
        ft_it++;
    }
    return ("EQUAL");
}

template<class T>
void
printValues(
        std::set<T> &stl_set,
        ft::set<T> &ft_set, std::string testName
) {
    //real set
    std::string stl_empty = ((stl_set.empty() == 1) ? "true" : "false");
    size_t stl_size = stl_set.size();

    //ft_set
    std::string ft_empty = ((ft_set.empty() == 1) ? "true" : "false");
    size_t ft_size = ft_set.size();

    //сравнение
    std::string empty = is_equal(ft_empty, stl_empty);
    std::string size = is_equal(ft_size, stl_size);

    std::string content = is_equal_content(stl_set, ft_set);

    std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
    std::cout << std::setfill(' ') << std::setw(20) << std::left << "Attribute";
    std::cout << std::setfill(' ') << std::setw(20) << std::left << "STL Set";
    std::cout << std::setfill(' ') << std::setw(20) << std::left << "FT Set";
    std::cout << std::setfill(' ') << std::setw(20) << std::left << "Result" << std::endl;

    std::cout << std::setfill(' ') << std::setw(20) << std::left << "Empty";
    std::cout << std::setfill(' ') << std::setw(20) << std::left << stl_empty;
    std::cout << std::setfill(' ') << std::setw(20) << std::left << ft_empty;
    std::cout << std::setfill(' ') << std::setw(20) << std::left << empty << std::endl;

    std::cout << std::setfill(' ') << std::setw(20) << std::left << "Size";
    std::cout << std::setfill(' ') << std::setw(20) << std::left << stl_size;
    std::cout << std::setfill(' ') << std::setw(20) << std::left << ft_size;
    std::cout << std::setfill(' ') << std::setw(20) << std::left << size << std::endl;

    std::cout << "\n";

    std::cout << std::left << "Result of content comparison: " << content << std::endl;
    if (empty == "not ok" || size == "not ok" /*|| max_size == "not ok" */|| content == "NOT EQUAL" /*|| capacity == "not ok"*/)
        std::cout << RED << "TOTAL: NOT OK" << REST << std::endl;
    else
        std::cout << GREEN << "TOTAL: OK" << REST << std::endl;
    std::cout << "**********************************************************************" << std::endl;
}

template<class T>
void
printSets(
        std::set<T> &stl_set,
        ft::set<T> &ft_set
) {
    typename std::set<T>::iterator stl_it;
    typename ft::set<T>::iterator ft_it;
    stl_it = stl_set.begin();
    ft_it = ft_set.begin();

    //печать STL
    std::cout << "STL Set content: ";
    while (stl_it != stl_set.end()) {
        std::cout << *stl_it;
        stl_it++;
        if (stl_it != stl_set.end())
            std::cout << ", ";
    }
    std::cout << "\n";

    //печать FT
    std::cout << "FT Set content: ";
    while (ft_it != ft_set.end()) {
        std::cout << *ft_it;
        ft_it++;
        if (ft_it != ft_set.end())
            std::cout << ", ";
    }
    std::cout << "\n";
    std::cout << "**********************************************************************" << std::endl;
    std::cout << "\n\n";
}

template<class T>
void
printSets2(
        std::set<T> &stl_set,
ft::set<T> &ft_set
) {
typename std::set<T>::iterator stl_it;
typename ft::set<T>::iterator ft_it;
stl_it = stl_set.begin();
ft_it = ft_set.begin();

//печать STL
std::cout << "STL Set content for swap: ";
while (stl_it != stl_set.end()) {
std::cout << *stl_it;
stl_it++;
if (stl_it != stl_set.end())
std::cout << ", ";
}
std::cout << "\n";

//печать FT
std::cout << "FT Set content for swap: ";
while (ft_it != ft_set.end()) {
std::cout << *ft_it;
ft_it++;
if (ft_it != ft_set.end())
std::cout << ", ";
}
std::cout << "\n";
std::cout << "**********************************************************************" << std::endl;
std::cout << "\n\n";
}

void
test_set() {
    std::string testName;
    std::set<int> myset;
    for (int i = 1; i <= 5; i++)
        myset.insert(i);
    std::cout << "**********SET TEST**********\n";

    {
        testName = "DEFAULT INT SET";

        std::set<int> stl_set_default_int;
        ft::set<int> ft_set_default_int;

        printValues(stl_set_default_int, ft_set_default_int, testName);
        printSets(stl_set_default_int, ft_set_default_int);
    }

    {
        testName = "DEFAULT STRING SET";

        std::set<std::string> stl_set_default_string;
        ft::set<std::string> ft_set_default_string;

        printValues(stl_set_default_string, ft_set_default_string, testName);
        printSets(stl_set_default_string, ft_set_default_string);

    }

    {
        testName = "RANGE CONSTRUCTOR";

        std::set<int> stl_range_set(myset.begin(), myset.end());
        ft::set<int> ft_range_set(myset.begin(), myset.end());

        printValues(stl_range_set, ft_range_set, testName);
        printSets(stl_range_set, ft_range_set);
    }

    {
        testName = "OPERATOR=";

        std::set<int> stl_range_set(myset.begin(), myset.end());
        ft::set<int> ft_range_set(myset.begin(), myset.end());

        std::set<int> stl_assign_set = stl_range_set;
        ft::set<int> ft_assign_set = ft_range_set;

        printValues(stl_assign_set, ft_assign_set, testName);
        printSets(stl_assign_set, ft_assign_set);
    }

    {
        testName = "GET ALLOCATOR";

        std::set<int> stl_set(myset.begin(), myset.end());
        ft::set<int> ft_set(myset.begin(), myset.end());

        printValues(stl_set, ft_set, testName);
        printSets(stl_set, ft_set);
        if (stl_set.get_allocator() == ft_set.get_allocator()) {
            std::cout << "stl_set.get_allocator() == ft_set.get_allocator()" <<
                      GREEN " OK" REST << std::endl;
        } else {
            std::cout << "std_set.get_allocator() != ft_set.get_allocator()" <<
                     RED " NOT OK" REST << std::endl;
        }
        std::cout << "\n";
        std::cout << "**********************************************************************" << std::endl;
        std::cout << "\n\n";
    }

    {
        testName = "ITER BEGIN()";

        std::set<int> stl_set(myset.begin(), myset.end());
        ft::set<int> ft_set(myset.begin(), myset.end());

        int from_stl = *(stl_set.begin());
        int from_ft = *(ft_set.begin());

        printValues(stl_set, ft_set, testName);
        std::cout << ".begin() from STL — " << from_stl << std::endl;
        std::cout << "\n";
        std::cout << ".begin() from FT — " << from_ft << std::endl;
        std::cout << "\n";
        printSets(stl_set, ft_set);

    }

    {
        testName = "CONST ITER BEGIN()";

        std::set<int> stl_range_set(myset.begin(), myset.end());
        ft::set<int> ft_range_set(myset.begin(), myset.end());

        int from_stl = *(stl_range_set.begin());
        int from_ft = *(ft_range_set.begin());

        printValues(stl_range_set, ft_range_set, testName);
        std::cout << ".const_begin() from STL — " << from_stl << std::endl;
        std::cout << "\n";
        std::cout << ".const_begin() from FT — " << from_ft << std::endl;
        std::cout << "\n";
        printSets(stl_range_set, ft_range_set);

    }

    {
        testName = "REVERSE ITER BEGIN()";

        std::set<int> stl_range_set(myset.begin(), myset.end());
        ft::set<int> ft_range_set(myset.begin(), myset.end());

        int from_stl = *(stl_range_set.rbegin());
        int from_ft = *(ft_range_set.rbegin());


        printValues(stl_range_set, ft_range_set, testName);
        std::cout << ".rbegin() from STL — " << from_stl << std::endl;
        std::cout << "\n";
        std::cout << ".rbegin() from FT — " << from_ft << std::endl;
        std::cout << "\n";
        printSets(stl_range_set, ft_range_set);

    }

    {
        testName = "CONST REVERSE ITER BEGIN()";

        std::set<int> stl_range_set(myset.begin(), myset.end());
        ft::set<int> ft_range_set(myset.begin(), myset.end());

        int from_stl = *(stl_range_set.rbegin());
        int from_ft = *(ft_range_set.rbegin());

        printValues(stl_range_set, ft_range_set, testName);
        std::cout << ".const_rbegin() from STL — " << from_stl << std::endl;
        std::cout << "\n";
        std::cout << ".const_rbegin() from FT — " << from_ft << std::endl;
        std::cout << "\n";
        printSets(stl_range_set, ft_range_set);
    }

    {
        testName = "ITERATORS";

        std::set<int> stl_set(myset.begin(), myset.end());
        ft::set<int> ft_set(myset.begin(), myset.end());

        printValues(stl_set, ft_set, testName);
        ft::set<int>::iterator ft_iter = ft_set.begin();
        std::set<int>::iterator std_iter = stl_set.begin();
        std::cout << "Enter: " << "++iter" << std::endl;
        ++ft_iter;
        ++std_iter;
        if (*ft_iter == *std_iter) {
            std::cout << GREEN " OK " REST << std::endl;
        } else {
            std::cout << RED " NOT OK " REST << std::endl;
        }
        std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
        std::cout << "Enter: " << "iter++" << std::endl;
        ft_iter++;
        std_iter++;
        if (*ft_iter == *std_iter) {
            std::cout << GREEN " OK " REST << std::endl;
        } else {
            std::cout << RED " NOT OK " REST << std::endl;
        }
        std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
        std::cout << "Enter: " << "--iter" REST << std::endl;
        --ft_iter;
        --std_iter;
        if (*ft_iter == *std_iter) {
            std::cout << GREEN " OK " REST << std::endl;
        } else {
            std::cout << RED " NOT OK " REST << std::endl;
        }
        std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
        std::cout << "Enter: " << "iter--" << std::endl;
        ft_iter--;
        std_iter--;
        if (*ft_iter == *std_iter) {
            std::cout << GREEN " OK " REST << std::endl;
        } else {
            std::cout << RED " NOT OK " REST << std::endl;
        }
        std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
        printSets(stl_set, ft_set);
    }

    {
        testName = "REVERSE ITERATORS";

        std::set<int> stl_set(myset.begin(), myset.end());
        ft::set<int> ft_set(myset.begin(), myset.end());

        printValues(stl_set, ft_set, testName);
        ft::set<int>::reverse_iterator ft_rev_iter = ft_set.rbegin();
        std::set<int>::reverse_iterator std_rev_iter = stl_set.rbegin();
        std::cout << "Enter: " << "++rev_iter" << std::endl;
        ++ft_rev_iter;
        ++std_rev_iter;
        if (*ft_rev_iter == *std_rev_iter) {
            std::cout << GREEN " OK " REST << std::endl;
        } else {
            std::cout << RED " NOT OK " REST << std::endl;
        }
        std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
        std::cout << "Enter: " << "rev_iter++" << std::endl;
        ft_rev_iter++;
        std_rev_iter++;
        if (*ft_rev_iter == *std_rev_iter) {
            std::cout << GREEN " OK " REST << std::endl;
        } else {
            std::cout << RED " NOT OK " REST << std::endl;
        }
        std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
        std::cout << "Enter: " << "--rev_iter" << std::endl;
        --ft_rev_iter;
        --std_rev_iter;
        if (*ft_rev_iter == *std_rev_iter) {
            std::cout << GREEN " OK " REST << std::endl;
        } else {
            std::cout << RED " NOT OK " REST << std::endl;
        }
        std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
        std::cout << "Enter: " << "rev_iter--" << std::endl;
        ft_rev_iter--;
        std_rev_iter--;
        if (*ft_rev_iter == *std_rev_iter) {
            std::cout << GREEN " OK " REST << std::endl;
        } else {
            std::cout << RED " NOT OK " REST << std::endl;
        }
        std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
        printSets(stl_set, ft_set);
    }
    {
        testName = "MODIFIERS";

        std::set<int> stl_set(myset.begin(), myset.end());
        ft::set<int> ft_set(myset.begin(), myset.end());

        printValues(stl_set, ft_set, testName);
        printSets(stl_set, ft_set);
        std::cout << "Enter: " << "set.clear()" << std::endl;
        ft_set.clear();
        stl_set.clear();
        printSets(stl_set, ft_set);
        std::cout << "Enter: " << "set.insert(21)" << std::endl;
        ft_set.insert(21);
        stl_set.insert(21);
        printSets(stl_set, ft_set);
    }

    {
        testName = "INSERT SINGLE ELEMENT";

        std::set<int> stl_set;
        ft::set<int> ft_set;

        printValues(stl_set, ft_set, testName);
        printSets(stl_set, ft_set);
        std::cout << "Enter: " << "set.insert(21)" << std::endl;
        ft_set.insert(42);
        stl_set.insert(42);
        std::cout << "Enter: " << "set.insert(-12)" << std::endl;
        ft_set.insert(-55);
        stl_set.insert(-55);
        std::cout << "Enter: " << "set.insert(-12)" << std::endl;
        ft_set.insert(-55);
        stl_set.insert(-55);
        std::cout << "Enter: " << "set.insert(0)" << std::endl;
        ft_set.insert(1);
        stl_set.insert(1);
        std::cout << "Enter: " << "set.insert(7)" << std::endl;
        ft_set.insert(11);
        stl_set.insert(11);
        printSets(stl_set, ft_set);
    }

    {
        testName = "SWAP";

        std::set<int> stl_set;
        ft::set<int> ft_set;
        for(int i = 1000; i > 799; i -= 50)
        {
            stl_set.insert(i);
            ft_set.insert(i);
        }
        printValues(stl_set, ft_set, testName);
        printSets(stl_set, ft_set);

        ft::set<int> ft_for_swap(myset.begin(), myset.end());
        std::set<int> stl_for_swap(myset.begin(), myset.end());

        printSets2(stl_for_swap, ft_for_swap);

        ft_set.swap(ft_for_swap);
        stl_set.swap(stl_for_swap);

        printSets(stl_set, ft_set);

    }
    {
        testName = "SPEED TEST";
        std::cout << "\n";
        std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
        std::set<int> stl_set;
        ft::set<int> ft_set;

        time_t start, end;
        double time_taken_stl, time_taken_ft, total_stl, total_ft;

        // вставка
        start = clock();
        for (int i = 0; i < 3000; i++)
            stl_set.insert(i);
        end = clock();

        time_taken_stl = end - start;
        total_stl = time_taken_stl;
        std::cout << "STL Insertion time is " << time_taken_stl << " ms" << std::endl;

        start = clock();
        for (int i = 0; i < 3000; i++)
            ft_set.insert(i);
        end = clock();

        time_taken_ft = end - start;
        total_ft = time_taken_ft;
        std::cout << "FT Insertion time is " << time_taken_ft << " ms" << std::endl;

        if (time_taken_ft / time_taken_stl > 1)
            std::cout << "FT Insertion set slower in " << time_taken_ft / time_taken_stl << " times";
        else
            std::cout << "FT Insertion set faster in " << time_taken_stl  / time_taken_ft << " times";
        std::cout << "\n\n";

        //поиск
        srand(time(0));
        int value = rand() % 3000;

        start = clock();
        stl_set.find(value);
        end = clock();

        time_taken_stl = end - start;
        total_stl += time_taken_stl;
        std::cout << "STL find time is " << time_taken_stl << " ms" << std::endl;

        start = clock();
        ft_set.find(value);
        end = clock();

        time_taken_ft = end - start;
        total_ft += time_taken_ft;
        std::cout << "FT find time is " << time_taken_ft << " ms" << std::endl;

        if (time_taken_ft / time_taken_stl > 1)
            std::cout << "FT find set slower in " << time_taken_ft / time_taken_stl << " times";
        else
            std::cout << "FT find set faster in " << time_taken_stl  / time_taken_ft << " times";
        std::cout << "\n\n";

        //удаление
        start = clock();
        for (int i = 0; i < 2500; i++)
            stl_set.erase(i);
        end = clock();

        time_taken_stl = end - start;
        total_stl += time_taken_stl;
        std::cout << "STL deletion time is " << time_taken_stl << " ms" << std::endl;

        start = clock();
        for (int i = 0; i < 2500; i++)
            ft_set.erase(i);
        end = clock();

        time_taken_ft = end - start;
        total_ft += time_taken_ft;
        std::cout << "FT deletion time is " << time_taken_ft << " ms" << std::endl;
        if (time_taken_ft / time_taken_stl > 1)
            std::cout << "FT deletion set slower in " << time_taken_ft / time_taken_stl << " times";
        else
            std::cout << "FT deletion set faster in " << time_taken_stl  / time_taken_ft << " times";
        std::cout << "\n\n";
    }
}