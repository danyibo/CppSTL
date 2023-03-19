#include <array>
#include <algorithm>
#include <numeric>
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>





template<typename T>
inline void PRINT_ELEMENTS(const T & coll, const std::string & optstr = "") {
	std::cout << optstr;
	for (const auto& elem : coll) {
		std::cout << elem << " ";
	}std::cout << std::endl;
}


void test_array() {
	std::array<int, 10> a = { 11, 22, 3, 44 };
	PRINT_ELEMENTS(a);
	a.back() = 99999;
	a[a.size() - 2] = 42;
	PRINT_ELEMENTS(a);

	std::cout << "sum: "
		<< std::accumulate(a.begin(), a.end(), 0)
		<< std::endl;

	std::transform(a.begin(), a.end(), a.begin(), std::negate<int>());
	PRINT_ELEMENTS(a);
}


void test_vector() {
	std::vector<std::string> sentence;
	sentence.reserve(5);

	sentence.push_back("Hello,");
	sentence.insert(sentence.end(), { "how", "are", "you", "?" });
	std::copy(sentence.cbegin(), sentence.cend(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << std::endl;

	std::cout << " max_size(): " << sentence.max_size() << std::endl;
	std::cout << " size(): " << sentence.size() << std::endl;
	std::cout << " capacity() " << sentence.capacity() << std::endl;

	std::swap(sentence[1], sentence[3]);
	sentence.insert(std::find(sentence.begin(), sentence.end(), "?"), "always");
	std::copy(sentence.cbegin(), sentence.cend(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << std::endl;
	std::cout << " size(): " << sentence.size() << std::endl;
	std::cout << " capacity() " << sentence.capacity() << std::endl;

	sentence.pop_back();
	sentence.pop_back();
	std::cout << " size(): " << sentence.size() << std::endl;
	std::cout << " capacity() " << sentence.capacity() << std::endl;

	sentence.shrink_to_fit();
	std::cout << " size(): " << sentence.size() << std::endl;
	std::cout << " capacity() " << sentence.capacity() << std::endl;
}

void test_deque() {
	std::deque<std::string> coll;
	coll.assign(3, std::string("string"));
	coll.push_back("last string");
	coll.push_front("first string");

	std::copy(coll.cbegin(), coll.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));
	std::cout << std::endl;

	coll.pop_front();
	coll.pop_back();

	for (unsigned int i = 0; i < coll.size(); ++i) {
		coll[i] = "anoter " + coll[i];
	}
	coll.resize(4, "resize string");
	std::copy(coll.cbegin(), coll.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));
	std::cout << std::endl;


}


void printLists(const std::list<int>& l1, const std::list<int>& l2) {
	std::cout << "list1: ";
	std::copy(l1.cbegin(), l1.cend(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	std::cout << "list2: ";
	std::copy(l2.cbegin(), l2.cend(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

void test_list() {
	std::list<int> list1, list2;
	for (int i = 0; i < 6; ++i) {
		list1.push_back(i);
		list2.push_front(i);
	}
	printLists(list1, list2);

	std::cout << "insert all elements of list1 before the first element with value 3 of list2 " << std::endl;
	list2.splice(std::find(list2.begin(), list2.end(), 3),
		list1);
	printLists(list1, list2);
	std::cout << "move first elements of list2 to the end" << std::endl;
	list2.splice(list2.end(), list2, list2.begin());
	printLists(list1, list2);


	list2.sort();
	list1 = list2;
	printLists(list1, list2);

	list1.merge(list2);
	printLists(list1, list2);

}

void test_forward_list() {
	/*
	  forward_list 只能向前，无法向后
	  因此，找到满足条件的元素的时候，往往已经是找过头了，这时候是无法回头的
	  这往往用两个迭代器来进行，一个表示满足条件的位置，一个表示之前元素的位置
	*/

	std::forward_list<int> list = { 1, 2, 3, 4, 5, 6 };
	auto posBefore = list.before_begin();
	for (auto pos = list.begin(); pos != list.end(); ++pos, ++posBefore) {
		if (*pos % 2 == 0) {
			break;
		}
		
	}
	list.insert_after(posBefore, 444444444);
	PRINT_ELEMENTS(list);

}


int main() {
	// test_array();
	// test_vector();
	// test_deque();
	// test_list();
	test_forward_list();
	return 0;
}
