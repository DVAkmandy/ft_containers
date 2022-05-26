#include "../src/stack.hpp"
#include <stack>
#include <iostream>
#include <iomanip>

template<class T>
std::string
is_equal(const T &t1, const T &t2) { return t1 == t2 ? "ok" : "not ok"; }

template<class T>
std::string
is_equal_content(std::stack<T> &stl_stack, ft::stack<T> &ft_stack) {

  if (ft_stack.size() != stl_stack.size())
	return ("NOT EQUAL");
  if (!ft_stack.empty() && !stl_stack.empty()) {
	if (stl_stack.top() != ft_stack.top())
	  return ("NOT EQUAL");
  }
  return ("EQUAL");
}

template<class T>
void
printValues(
	std::stack<T> &stl_stack,
	ft::stack<T> &ft_stack, std::string testName
) {
  //stl_stack
  std::string stl_empty = ((stl_stack.empty() == 1) ? "true" : "false");
  size_t stl_size = stl_stack.size();

  //ft_stack
  std::string ft_empty = ((ft_stack.empty() == 1) ? "true" : "false");
  size_t ft_size = ft_stack.size();

  //сравнение
  std::string empty = is_equal(ft_empty, stl_empty);
  std::string size = is_equal(ft_size, stl_size);
  std::string content = is_equal_content(stl_stack, ft_stack);

  std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
  std::cout << std::setfill(' ') << std::setw(20) << std::left << "Attribute";
  std::cout << std::setfill(' ') << std::setw(20) << std::left << "STL Stack";
  std::cout << std::setfill(' ') << std::setw(20) << std::left << "FT Stack";
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
  if (empty == "not ok" || size == "not ok" || content == "NOT EQUAL")
	std::cout << "\33[1;31m" << "TOTAL: NOT OK" << "\33[1;0m" << std::endl;
  else
	std::cout << "\33[1;32m" << "TOTAL: OK" << "\33[1;0m" << std::endl;
  std::cout << "**********************************************************************" << std::endl;
}

template<class T>
void
printPop(std::stack<T> &stl_stack, ft::stack<T> &ft_stack) {

  if (!ft_stack.empty() && !stl_stack.empty()) {
	//печать STL
	std::cout << "STL Stack top: " << stl_stack.top() << std::endl;
	//печать FT
	std::cout << "FT Stack top: " << ft_stack.top() << std::endl;
  } else
	std::cout << "CONTENT IS EMPTY " << std::endl;

  std::cout << "**********************************************************************" << std::endl;
  std::cout << "\n\n";
}

void
test_stack() {
  std::string testName;
  std::cout << "**********STACK TEST**********\n";

  {
	testName = "DEFAULT CONSTRUCTOR";

	std::stack<int> stl_stack;
	ft::stack<int> ft_stack;

	printValues(stl_stack, ft_stack, testName);
	printPop(stl_stack, ft_stack);
  }

  {
	testName = "EMPTY TRUE";
	std::stack<int> stl_stack;
	ft::stack<int> ft_stack;

	printValues(stl_stack, ft_stack, testName);
	printPop(stl_stack, ft_stack);
  }

  {
	testName = "RELATION OPERATORS";
	std::stack<int> stl_stack;
	ft::stack<int> ft_stack;
	std::stack<int> stl_stack2;
    ft::stack<int> ft_stack2;

	for (int i = 10; i < 0; i--) {
	  stl_stack2.push(i);
	  ft_stack2.push(i);
	}

	bool stl;
	bool ft;

	printValues(stl_stack, ft_stack, testName);
	stl = (stl_stack == stl_stack2);
	ft = (ft_stack == ft_stack2);
	std::cout << "STL: stack1 == stack2? " << stl << std::endl;
	std::cout << "FT: stack1 == stack2?  " << ft << std::endl;
	std::cout << "\n";

	stl = (stl_stack != stl_stack2);
	ft = (ft_stack != ft_stack2);
	std::cout << "STL: stack1 != stack2? " << stl << std::endl;
	std::cout << "FT: stack1 != stack2?  " << ft << std::endl;
	std::cout << "\n";

	stl = (stl_stack < stl_stack2);
	ft = (ft_stack < ft_stack2);
	std::cout << "STL: stack1 < stack2? " << stl << std::endl;
	std::cout << "FT: stack1 < stack2?  " << ft << std::endl;
	std::cout << "\n";

	stl = (stl_stack > stl_stack2);
	ft = (ft_stack > ft_stack2);
	std::cout << "STL: stack1 > stack2? " << stl << std::endl;
	std::cout << "FT: stack1 > stack2?  " << ft << std::endl;
	std::cout << "\n";

	stl = (stl_stack <= stl_stack2);
	ft = (ft_stack <= ft_stack2);
	std::cout << "STL: stack1 <= stack2? " << stl << std::endl;
	std::cout << "FT: stack1 <= stack2?  " << ft << std::endl;
	std::cout << "\n";

	stl = (stl_stack <= stl_stack2);
	ft = (ft_stack <= ft_stack2);
	std::cout << "STL: stack1 >= stack2? " << stl << std::endl;
	std::cout << "FT: stack1 >= stack2?  " << ft << std::endl;
	std::cout << "\n";

	printPop(stl_stack, ft_stack);
  }
}