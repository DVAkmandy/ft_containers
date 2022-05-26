#include "../src/map.hpp"
#include <map>
#include <iostream>
#include <iomanip>

template<class T>
std::string
is_equal(const T &t1, const T &t2) { return t1 == t2 ? "ok" : "not ok"; }

template<class Ta, class Tb>
std::string is_equal_content(
	const std::map<Ta, Tb> &stl_map,
	const ft::map<Ta, Tb> &ft_map
) {
  typename ft::map<Ta, Tb>::const_iterator ft_it;
  typename std::map<Ta, Tb>::const_iterator stl_it;
  if (ft_map.size() != stl_map.size())
	return ("NOT EQUAL");
  stl_it = stl_map.begin();
  for (ft_it = ft_map.begin(); ft_it != ft_map.end(); ft_it++) {
	if ((*ft_it).first != (*stl_it).first || (*ft_it).second != (*stl_it).second)
	  return ("NOT EQUAL");
	stl_it++;
  }
  return ("EQUAL");
}

template<class Ta, class Tb>
void
printValues(
	std::map<Ta, Tb> &stl_map,
	ft::map<Ta, Tb> &ft_map, const std::string &testName
) {
  //stl map
  std::string stl_empty = ((stl_map.empty() == 1) ? "true" : "false");
  size_t stl_size = stl_map.size();
  size_t stl_max_size = stl_map.max_size();

  //ft map
  std::string ft_empty = ((ft_map.empty() == 1) ? "true" : "false");
  size_t ft_size = ft_map.size();
  size_t ft_max_size = ft_map.max_size();

  //сравнение
  std::string empty = is_equal(ft_empty, stl_empty);
  std::string size = is_equal(ft_size, stl_size);
  std::string max_size = is_equal(ft_max_size, stl_max_size);
  std::string content = is_equal_content(stl_map, ft_map);

  std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
  std::cout << std::setfill(' ') << std::setw(20) << std::left << "Attribute";
  std::cout << std::setfill(' ') << std::setw(20) << std::left << "STL Map";
  std::cout << std::setfill(' ') << std::setw(20) << std::left << "FT Map";
  std::cout << std::setfill(' ') << std::setw(20) << std::left << "Result" << std::endl;

  std::cout << std::setfill(' ') << std::setw(20) << std::left << "Empty";
  std::cout << std::setfill(' ') << std::setw(20) << std::left << stl_empty;
  std::cout << std::setfill(' ') << std::setw(20) << std::left << ft_empty;
  std::cout << std::setfill(' ') << std::setw(20) << std::left << empty << std::endl;

  std::cout << std::setfill(' ') << std::setw(20) << std::left << "Size";
  std::cout << std::setfill(' ') << std::setw(20) << std::left << stl_size;
  std::cout << std::setfill(' ') << std::setw(20) << std::left << ft_size;
  std::cout << std::setfill(' ') << std::setw(20) << std::left << size << std::endl;

  std::cout << std::setw(20) << std::left << "Max_size";
  std::cout << std::setw(20) << std::left << stl_max_size;
  std::cout << std::setw(20) << std::left << ft_max_size;
  std::cout << std::setw(20) << std::left << max_size << std::endl;
  std::cout << "\n";

  std::cout << std::left << "Result of content comparison: " << content << std::endl;
  if (empty == "not ok" || size == "not ok" || max_size == "not ok" || content == "NOT EQUAL")
	std::cout << "\33[1;31m" << "TOTAL: NOT OK" << "\33[1;0m" << std::endl;
  else
	std::cout << "\33[1;32m" << "TOTAL: OK" << "\33[1;0m" << std::endl;
  std::cout << "**********************************************************************" << std::endl;
}

template<class Ta, class Tb>
void
printMaps(
	std::map<Ta, Tb> &stl_map,
	ft::map<Ta, Tb> &ft_map
) {
  typename ft::map<Ta, Tb>::const_iterator ft_it;
  typename std::map<Ta, Tb>::const_iterator stl_it;
  stl_it = stl_map.begin();
  ft_it = ft_map.begin();

  //печать STL
  std::cout << "STL Map content: ";
  while (stl_it != stl_map.end()) {
	std::cout << "[";
	std::cout << (*stl_it).first;
	std::cout << ", ";
	std::cout << (*stl_it).second;
	std::cout << "]";
	stl_it++;
	if (stl_it != stl_map.end())
	  std::cout << ", ";
  }
  std::cout << "\n";

  //печать FT
  std::cout << "FT Map content: ";
  while (ft_it != ft_map.end()) {
	std::cout << "[";
	std::cout << (*ft_it).first;
	std::cout << ", ";
	std::cout << (*ft_it).second;
	std::cout << "]";
	ft_it++;
	if (ft_it != ft_map.end())
	  std::cout << ", ";
  }

  std::cout << "\n";
  std::cout << "**********************************************************************" << std::endl;
  std::cout << "\n\n";
}

void
test_map() {
  std::cout << "**********MAP TEST**********\n";
  std::string testName;
  const std::string string_array[] = {"one", "two", "three", "four", "five"};
  const int int_array[] = {1, 2, 3, 4, 5};

  {
	testName = "DEFAULT CONSTRUCTOR";

	std::map<int, std::string> stl_map;
	ft::map<int, std::string> ft_map;

	printValues(stl_map, ft_map, testName);
	printMaps(stl_map, ft_map);

  }

  {
	testName = "RANGE CONSTRUCTOR";

	std::map<std::string, int> stl_map;
	ft::map<std::string, int> ft_map;

	for (int i = 0; i < 5; i++) {
	  stl_map.insert(std::make_pair(string_array[i], int_array[i]));
	  ft_map.insert(ft::make_pair(string_array[i], int_array[i]));
	}

	printValues(stl_map, ft_map, testName);
	printMaps(stl_map, ft_map);

	testName = "COPY CONSTRUCTOR";

	ft::map<std::string, int> ft_map_copy(ft_map);
	std::map<std::string, int> stl_map_copy(stl_map);

	printValues(stl_map_copy, ft_map_copy, testName);
	printMaps(stl_map_copy, ft_map_copy);

	testName = "OPERATOR=";

	ft::map<std::string, int> ft_map_assign(ft_map);
	std::map<std::string, int> stl_map_assign(stl_map);

	ft_map_assign = ft_map;
	stl_map_assign = stl_map;

	printValues(stl_map_assign, ft_map_assign, testName);
	printMaps(stl_map_assign, ft_map_assign);

	testName = "BEGIN / END";

	std::map<std::string, int>::iterator stl_it_beg = stl_map.begin();
	ft::map<std::string, int>::iterator ft_it_beg = ft_map.begin();

	std::map<std::string, int>::iterator stl_it_end = stl_map.end();
	ft::map<std::string, int>::iterator ft_it_end = ft_map.end();
	stl_it_end--;
	ft_it_end--;

	printValues(stl_map, ft_map, testName);
	std::cout << " STL Map begin = ";
	std::cout << "[";
	std::cout << (*stl_it_beg).first;
	std::cout << ", ";
	std::cout << (*stl_it_beg).second;
	std::cout << "]";
	std::cout << "\n";
	std::cout << " STL Map end = ";
	std::cout << "[";
	std::cout << (*stl_it_end).first;
	std::cout << ", ";
	std::cout << (*stl_it_end).second;
	std::cout << "]";
	std::cout << "\n";

	std::cout << " FT Map begin = ";
	std::cout << "[";
	std::cout << (*ft_it_beg).first;
	std::cout << ", ";
	std::cout << (*ft_it_beg).second;
	std::cout << "]";
	std::cout << "\n";
	std::cout << " STL Map end = ";
	std::cout << "[";
	std::cout << (*ft_it_end).first;
	std::cout << ", ";
	std::cout << (*ft_it_end).second;
	std::cout << "]";
	std::cout << "\n";
	printMaps(stl_map, ft_map);

	testName = "RBEGIN / REND";

	std::map<std::string, int>::reverse_iterator stl_it_rbeg = stl_map.rbegin();
	ft::map<std::string, int>::reverse_iterator ft_it_rbeg = ft_map.rbegin();

	std::map<std::string, int>::reverse_iterator stl_it_rend = stl_map.rend();
	ft::map<std::string, int>::reverse_iterator ft_it_rend = ft_map.rend();

	stl_it_rend--;
	ft_it_rend--;

	printValues(stl_map, ft_map, testName);
	std::cout << " STL Map rbegin = ";
	std::cout << "[";
	std::cout << (*stl_it_rbeg).first;
	std::cout << ", ";
	std::cout << (*stl_it_rbeg).second;
	std::cout << "]";
	std::cout << "\n";
	std::cout << " STL Map rend = ";
	std::cout << "[";
	std::cout << (*stl_it_rend).first;
	std::cout << ", ";
	std::cout << (*stl_it_rend).second;
	std::cout << "]";
	std::cout << "\n";

	std::cout << " FT Map begin = ";
	std::cout << "[";
	std::cout << (*ft_it_rbeg).first;
	std::cout << ", ";
	std::cout << (*ft_it_rbeg).second;
	std::cout << "]";
	std::cout << "\n";
	std::cout << " FT Map rend = ";
	std::cout << "[";
	std::cout << (*ft_it_rend).first;
	std::cout << ", ";
	std::cout << (*ft_it_rend).second;
	std::cout << "]";
	std::cout << "\n";
	printMaps(stl_map, ft_map);

	testName = "OPERATOR []";

	printValues(stl_map, ft_map, testName);
	std::cout << " STL Map[two] = " << stl_map["two"] << std::endl;
	std::cout << " FT Map[two] = " << ft_map["two"] << std::endl;
	std::cout << "\n";
	printMaps(stl_map, ft_map);

	testName = "INSERT SINGLE";

	stl_map.insert(std::make_pair("six", 6));
	ft_map.insert(ft::make_pair("six", 6));

	printValues(stl_map, ft_map, testName);
	printMaps(stl_map, ft_map);

	testName = "INSERT WITH HINT";
	//Вставка с подсказкой. Даёт возможность оптимизировать время встравки за счет указания элемента, после которого нужно вставить
	//Не гарантирует, что элемент будет вставлен именно так

	stl_map.insert(--stl_map.end(), std::make_pair("seven", 7));
	ft_map.insert(--ft_map.end(), ft::make_pair("seven", 7));

	printValues(stl_map, ft_map, testName);
	printMaps(stl_map, ft_map);

	testName = "INSERT RANGE";

	std::map<char, int> mymap_stl;
	ft::map<char, int> mymap_ft;

	// first insert function version (single parameter):
	mymap_stl.insert(std::pair<char, int>('a', 100));
	mymap_stl.insert(std::pair<char, int>('z', 200));
	mymap_ft.insert(ft::pair<char, int>('a', 100));
	mymap_ft.insert(ft::pair<char, int>('z', 200));

	// second insert function version (with hint position):
	std::map<char, int>::iterator it_stl = mymap_stl.begin();
	ft::map<char, int>::iterator it_ft = mymap_ft.begin();
	mymap_stl.insert(it_stl, std::pair<char, int>('b', 300));  // max efficiency inserting
	mymap_stl.insert(it_stl, std::pair<char, int>('c', 400));  // no max efficiency inserting
	mymap_ft.insert(it_ft, ft::pair<char, int>('b', 300));  // max efficiency inserting
	mymap_ft.insert(it_ft, ft::pair<char, int>('c', 400));  // no max efficiency inserting

	// third insert function version (range insertion):
	std::map<char, int> anothermap_stl;
	ft::map<char, int> anothermap_ft;
	anothermap_stl.insert(mymap_stl.begin(), mymap_stl.find('c'));
	anothermap_ft.insert(mymap_ft.begin(), mymap_ft.find('c'));

	printValues(anothermap_stl, anothermap_ft, testName);
	printMaps(anothermap_stl, anothermap_ft);

	testName = "ERASE SINGLE";

	stl_map.erase(stl_map.begin());
	ft_map.erase(ft_map.begin());

	printValues(stl_map, ft_map, testName);
	printMaps(stl_map, ft_map);

	testName = "ERASE RANGE";//DVAkmandy

	std::map<std::string, int>::iterator stl_erase_start = stl_map.begin();
	std::map<std::string, int>::iterator stl_erase_end = stl_map.end();

	ft::map<std::string, int>::iterator ft_erase_start = ft_map.begin();
	ft::map<std::string, int>::iterator ft_erase_end = ft_map.end();

	for (int i = 0; i < 6; i++) {
	  stl_erase_start++;
	  ft_erase_start++;
	}

	stl_map.erase(stl_erase_start, stl_erase_end);
	ft_map.erase(ft_erase_start, ft_erase_end);

	printValues(stl_map, ft_map, testName);
	printMaps(stl_map, ft_map);

	testName = "SWAP";

	std::map<std::string, int> stl_map_swap;
	ft::map<std::string, int> ft_map_swap;

	stl_map_swap = stl_map_assign;
	ft_map_swap = ft_map_assign;

	stl_map.swap(stl_map_swap);
	ft_map.swap(ft_map_swap);

	printValues(stl_map, ft_map, testName);
	printMaps(stl_map, ft_map);

	testName = "CLEAR";

	stl_map.clear();
	ft_map.clear();

	printValues(stl_map, ft_map, testName);
	printMaps(stl_map, ft_map);

	testName = "KEY COMPARE";

	std::map<std::string, int>::key_compare stl_key = std::map<std::string, int>().key_comp();
	ft::map<std::string, int>::key_compare ft_key = ft::map<std::string, int>().key_comp();

	printValues(stl_map, ft_map, testName);
	bool stl_res = stl_key("A", "B");
	std::cout << "STL key compare result (A < B?) = " << stl_res << std::endl;
	stl_res = stl_key("X", "A");
	std::cout << "STL key compare result (X < A?) = " << stl_res << std::endl;
	std::cout << "\n";

	bool ft_res = ft_key("A", "B");
	std::cout << "FT key compare result (A < B?) = " << ft_res << std::endl;
	ft_res = ft_key("X", "A");
	std::cout << "FT key compare result (X < A?) = " << ft_res << std::endl;
	std::cout << "\n";
	printMaps(stl_map, ft_map);
  }

  {
	testName = "VALUE COMPARE";

	std::map<std::string, int> stl_map;
	ft::map<std::string, int> ft_map;

	std::map<std::string, int>::value_compare stl_key = std::map<std::string, int>().value_comp();
	ft::map<std::string, int>::value_compare ft_key = ft::map<std::string, int>().value_comp();

	printValues(stl_map, ft_map, testName);

	bool stl_res = stl_key(std::make_pair("A", 1), std::make_pair("B", 2));
	std::cout << "STL value compare result= " << stl_res << std::endl;
	stl_res = stl_key(std::make_pair("A", 10), std::make_pair("A", 2));
	std::cout << "STL value compare result = " << stl_res << std::endl;
	std::cout << "\n";

	bool ft_res = ft_key(ft::make_pair("A", 1), ft::make_pair("B", 2));
	std::cout << "FT value compare result2 = " << ft_res << std::endl;
	ft_res = ft_key(ft::make_pair("A", 10), ft::make_pair("A", 2));
	std::cout << "FT value compare result2 = " << ft_res << std::endl;
	std::cout << "\n";

	printMaps(stl_map, ft_map);

	testName = "FIND";

	for (int i = 0; i < 5; i++) {
	  stl_map.insert(std::make_pair(string_array[i], int_array[i]));
	  ft_map.insert(ft::make_pair(string_array[i], int_array[i]));
	}

	std::map<std::string, int>::iterator stl_it = stl_map.find("two");
	ft::map<std::string, int>::iterator ft_it = ft_map.find("two");

	printValues(stl_map, ft_map, testName);

	std::cout << "STL Map find (two) = ";
	std::cout << "[";
	std::cout << (*stl_it).first;
	std::cout << ", ";
	std::cout << (*stl_it).second;
	std::cout << "]";
	std::cout << "\n";

	std::cout << "FT Map find (two) = ";
	std::cout << "[";
	std::cout << (*ft_it).first;
	std::cout << ", ";
	std::cout << (*ft_it).second;
	std::cout << "]";
	std::cout << "\n";
	std::cout << "\n";

	ft_it = ft_map.find("fefef");
	stl_it = stl_map.find("fefef");

	if (stl_it == stl_map.end() && ft_it == ft_map.end())
	  std::cout << "Non existing find test OK";
	else
	  std::cout << "Non existing find test NOT OK";
	std::cout << "\n";
	std::cout << "\n";
	printMaps(stl_map, ft_map);

	testName = "COUNT";

	printValues(stl_map, ft_map, testName);

	std::cout << "STL Map count = " << stl_map.count("one") << std::endl;
	std::cout << "FT Map count = " << ft_map.count("one") << std::endl;

	printMaps(stl_map, ft_map);

	testName = " LOWER / UPPER BOUND";

	printValues(stl_map, ft_map, testName);
	stl_it = stl_map.lower_bound("two");

	std::cout << "STL Map lower bound (two) = ";
	std::cout << "[";
	std::cout << (*stl_it).first;
	std::cout << ", ";
	std::cout << (*stl_it).second;
	std::cout << "]";
	std::cout << "\n";
	stl_it = stl_map.upper_bound("seven");
	std::cout << "STL Map upper bound (seven) = ";
	std::cout << "[";
	std::cout << (*stl_it).first;
	std::cout << ", ";
	std::cout << (*stl_it).second;
	std::cout << "]";
	std::cout << "\n";

	ft_it = ft_map.lower_bound("two");
	std::cout << "FT Map lower bound  (two) = ";
	std::cout << "[";
	std::cout << (*ft_it).first;
	std::cout << ", ";
	std::cout << (*ft_it).second;
	std::cout << "]";
	std::cout << "\n";

	ft_it = ft_map.upper_bound("seven");
	std::cout << "FT Map upper bound  (seven) = ";
	std::cout << "[";
	std::cout << (*ft_it).first;
	std::cout << ", ";
	std::cout << (*ft_it).second;
	std::cout << "]";
	std::cout << "\n";
	std::cout << "\n";

	printMaps(stl_map, ft_map);

	testName = "EQUAL RANGE";

	printValues(stl_map, ft_map, testName);

	std::cout << "STL Map equal range (four) = ";
	std::cout << "[";
	std::cout << (*(stl_map.equal_range("four").first)).first;
	std::cout << ", ";
	std::cout << (*(stl_map.equal_range("four").second)).first;
	std::cout << "]";
	std::cout << "\n";

	std::cout << "FT Map equal range (four) = ";
	std::cout << "[";
	std::cout << (*(ft_map.equal_range("four").first)).first;
	std::cout << ", ";
	std::cout << (*(ft_map.equal_range("four").second)).first;
	std::cout << "]";
	std::cout << "\n";
	std::cout << "\n";

	printMaps(stl_map, ft_map);
  }
    {
        testName = "SPEED TEST";
        std::cout << "\n";
        std::cout << std::setfill('*') << std::setw(70) << std::left << testName << std::endl;
        time_t start, end;
        double time_taken_stl, time_taken_ft, time_taken, total_stl, total_ft;

        srand(time(0));
        std::map<int, int> stl_map;
        ft::map<int, int> ft_map;

        int value1 = rand();
        int value2 = rand();

        //вставка
        start = clock();
        for (int i = 0; i < 5000; i++)
            stl_map.insert(std::make_pair(value1, value2));
        end = clock();

        time_taken_stl = end - start;
        total_stl = time_taken_stl;
        std::cout << "STL Insertion time is " << time_taken_stl << " ms" << std::endl;

        start = clock();
        for (int i = 0; i < 5000; i++)
            ft_map.insert(ft::make_pair(value1, value2));
        end = clock();

        time_taken_ft = end - start;
        total_ft = time_taken_ft;
        std::cout << "FT Insertion time is " << time_taken_ft << " ms" << std::endl;

        if (time_taken_ft / total_stl > 1)
            std::cout << "FT Insertion map slower in " << time_taken_ft / time_taken_stl << " times";
        else
            std::cout << "FT Insertion map faster in " << time_taken_stl / time_taken_ft << " times";
        std::cout << "\n\n";

        //поиск
        value1 = rand() % 4900;
        start = clock();
        for (int i = 0; i < 3000; i++)
            stl_map.find(value1);
        end = clock();

        time_taken_stl = end - start;
        total_stl += time_taken_stl;
        std::cout << "STL find time is " << time_taken_stl << " ms" << std::endl;

        value1 = rand() % 4900;
        start = clock();
        for (int i = 0; i < 3000; i++)
            ft_map.find(value1);
        end = clock();

        time_taken_ft = end - start;
        total_ft += time_taken_ft;
        std::cout << "FT find time is " << time_taken_ft << " ms" << std::endl;

        if (time_taken_ft / total_stl > 1)
            std::cout << "FT find map slower in " << time_taken_ft / time_taken_stl << " times";
        else
            std::cout << "FT find map faster in " << time_taken_stl / time_taken_ft << " times";
        std::cout << "\n\n";

        //удаление
        value1 = rand() % 4900;
        start = clock();
        for (int i = 0; i < 3000; i++)
            stl_map.erase(value1);
        end = clock();

        time_taken_stl = end - start;
        total_stl += time_taken_stl;

        std::cout << "STL deletion time is " << time_taken_stl << " ms" << std::endl;

        value1 = rand() % 4900;
        start = clock();
        for (int i = 0; i < 3000; i++)
            ft_map.erase(value1);
        end = clock();

        time_taken_ft = end - start;
        total_ft += time_taken_ft;
        std::cout << "FT deletion time is " << time_taken_ft << " ms" << std::endl;

        if (time_taken_ft / total_stl > 1)
            std::cout << "FT deletion map slower in " << time_taken_ft / time_taken_stl << " times";
        else
            std::cout << "FT deletion map faster in " << time_taken_stl / time_taken_ft << " times";
        std::cout << "\n\n";

    }
}
