#include<iostream>
#include<array>
#include<deque>
#include<list>
#include<forward_list>
#include<set>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<iterator>
#include<numeric>
#include<string>
#include<functional>


template<typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last) {
	for (int i = first; i < last; ++i) {
		coll.insert(coll.end(), i);
	}
}


template<typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optcstr = "") {
	std::cout << optcstr;
	for (auto elem : coll) {
		std::cout << elem << ' ';
	}std::cout << std::endl;
}


template<typename T>
inline void PRINT_MAPPED_ELEMENTS(const T& coll, const std::string& optcstr = "") {
	std::cout << optcstr;
	for (auto elem : coll) {
		std::cout << '[' << elem.first << ',' << elem.second << "] ";
	}
	std::cout << std::endl;
}

/*
* for_each()算法：对每个元素进行操作
* 复杂度：线性复杂度
*/


void print(int elem) {
	std::cout << elem << ' ';
}


template<typename T>
class AddValue {
private:
	T value;
public:
	AddValue(const T & v): value(v){}

	void operator()(T& elem)const {
		elem += value;
	}
};


void test01() {
	std::vector<int> coll;
	INSERT_ELEMENTS(coll, 1, 9);

	std::cout << "如何打印元素：" << std::endl;
	std::for_each(coll.begin(), coll.end(),
		[](int elem) {std::cout << elem << ' '; }
	);
	std::cout << std::endl;
	std::for_each(coll.begin(), coll.end(), print);

	std::cout << std::endl;
	std::cout << "如何改变每个元素： " << std::endl;

	std::for_each(coll.begin(), coll.end(),
		[](int& elem)
		{elem += 10; }
	);
	PRINT_ELEMENTS(coll);


	std::for_each(coll.begin(), coll.end(),
		[=](int& elem) {
			elem += *coll.begin();
		});
	PRINT_ELEMENTS(coll);


	std::for_each(coll.begin(), coll.end(), AddValue<int>(10));
	PRINT_ELEMENTS(coll);

	std::transform(coll.cbegin(), coll.cend(), coll.begin(), [=](int elem) {
		return elem -= 10;
		});
	PRINT_ELEMENTS(coll);
}



void test02() {
	// count 
	// count if
	std::vector<int> coll;
	int num;
	INSERT_ELEMENTS(coll, 1, 9);

	num = std::count(coll.begin(), coll.end(), 4);
	std::cout << "num if 4 is ：" << num << std::endl;

	num = std::count_if(coll.begin(), coll.end(),
		[](int elem)
		{
			return elem % 2 == 0;
		}
	);
	std::cout << "num of even is :" << num << std::endl;


	num = std::count_if(coll.begin(), coll.end(),
		[](int elem)
		{
			return elem > 4;
		}
	);

	std::cout << "num of greater than 4 : " << std::endl;


	std::cout << "bind" << std::endl;

	num = std::count_if(coll.cbegin(), coll.cend(),
		std::bind(std::logical_not<bool>(), std::bind(std::modulus<int>(), std::placeholders::_1, 2)
	));
	std::cout << "num of even is :" << num << std::endl;

}




bool absLess(int elem1, int elem2) {
	return std::abs(elem1) < std::abs(elem2);
}


void test03() {
	//  最大值最小值算法
	std::deque<int> coll;
	INSERT_ELEMENTS(coll, 2, 6);
	INSERT_ELEMENTS(coll, -3, 6);
	PRINT_ELEMENTS(coll);

	std::cout << "min: " <<
		*std::min_element(coll.cbegin(), coll.cend()) << std::endl;

	std::cout << "max: " <<
		*std::max_element(coll.cbegin(), coll.cend()) << std::endl;

	auto m = std::minmax_element(coll.cbegin(), coll.cend());
	std::cout << "min: " << *(m.first) << std::endl;
	std::cout << "max: " << *(m.second) << std::endl;


	std::cout << "min of abs values: ";
	std::cout << *std::min_element(coll.cbegin(), coll.cend(), absLess);
	std::cout << "max of abs values: ";
	std::cout << *std::max_element(coll.cbegin(), coll.cend(), absLess);

}



void test04() {
	// 查找算法
	std::list<int> coll;
	INSERT_ELEMENTS(coll, 1, 9);
	INSERT_ELEMENTS(coll, 1, 9);
	PRINT_ELEMENTS(coll);


	std::list<int>::iterator pos1, pos2;
	pos1 = std::find(coll.begin(), coll.end(), 4);
	if (pos1 != coll.end()) {
		pos2 = std::find(++pos1, coll.end(), 4);
	}

	if (pos1 != coll.end() && pos2 != coll.end()) {
		std::copy(--pos1, ++pos2, std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}


}

void test05() {
	std::vector<int> coll;
	std::vector<int>::iterator pos;

	INSERT_ELEMENTS(coll, 1, 9);
	PRINT_ELEMENTS(coll, "coll: ");

	pos = std::find_if(coll.begin(), coll.end(),
		std::bind(std::greater<int>(), std::placeholders::_1, 3));
	std::cout << "the "
		<< std::distance(coll.begin(), pos) + 1
		<< " elemnt is the first greater than 3" << std::endl;


	pos = std::find_if(coll.begin(), coll.end(),
		[](int elem) {
			return elem % 3 == 0;
		}
	);

	std::cout << "the " << std::distance(coll.begin(), pos) + 1 << std::endl;


}

void test06() {
	std::deque<int> coll;
	coll = { 1, 2, 7, 7,  6, 3, 9, 5, 7,7,7,3,6 };
	PRINT_ELEMENTS(coll);

	std::deque<int>::iterator pos;
	pos = std::search_n(coll.begin(), coll.end(), 
		3, // count
		7); // value

	if (pos != coll.end()) {
		std::cout << "there consecutive elements wiht value 7  strat wtih " <<
			std::distance(coll.begin(), pos) + 1 << " element" << std::endl;
	}
	else {
		std::cout << "not find!" << std::endl;
	}


	pos = std::search_n(coll.begin(), coll.end(),
		4,
		0,
		[](int elem, int value) {
			return elem % 2 == 1;
		}
	);

	//if (pos != coll.end()) {
	//	std::cout << "first four consective odd elemnet are: ";
	//	for (int i = 0; i < 4; ++i, ++pos) {
	//		std::cout << *pos << " ";
	//	}std::cout << std::endl;
	//} 
	//else {
	//	std::cout << "not find! " << std::endl;
	//}

}


void test07() {
	std::deque<int> coll;
	std::list<int> subcoll;

	INSERT_ELEMENTS(coll, 1, 7);
	INSERT_ELEMENTS(coll, 1, 7);
	INSERT_ELEMENTS(subcoll, 3, 6);

	PRINT_ELEMENTS(coll, "coll: ");
	PRINT_ELEMENTS(subcoll, "subcoll: ");

	std::deque<int>::iterator pos;
	pos = std::search(coll.begin(), coll.end(), subcoll.begin(), subcoll.end());

	while (pos != coll.end()) {
		std::cout << "sub coll found starting with element "
			<< std::distance(coll.begin(), pos) + 1
			<< std::endl;
		pos++;
	}







}




void test08() {
	std::deque<int> coll;
	std::list<int> subcoll;

	INSERT_ELEMENTS(coll, 1, 7);
	INSERT_ELEMENTS(coll, 1, 7);
	INSERT_ELEMENTS(subcoll, 3, 6);
	PRINT_ELEMENTS(coll, "coll: ");
	PRINT_ELEMENTS(subcoll, "subcoll: ");
	std::deque<int>::iterator pos = std::find_first_of(coll.begin(), coll.end(),
		subcoll.begin(), subcoll.end());
	std::cout << "第一个位置：" << std::distance(coll.begin(), pos) + 1 << std::endl;
	
	std::deque<int>::reverse_iterator pos2 = std::find_first_of(coll.rbegin(), coll.rend(),
		subcoll.begin(), subcoll.end());
	std::cout << "最后一个位置：" << std::distance(coll.begin(), pos2.base()) << std::endl;
}


bool bothEvenOrOdd(int elem1, int elem2) {
	return elem1 % 2 == elem2 % 2;
}

void test09() {
	std::vector<int> coll1;
	std::list<int> coll2;
	INSERT_ELEMENTS(coll1, 1, 7);
	INSERT_ELEMENTS(coll2, 3, 9);

	PRINT_ELEMENTS(coll1, "coll1: ");
	PRINT_ELEMENTS(coll2, "coll2: ");
	if (std::equal(coll1.begin(), coll1.end(), coll2.begin())) {
		std::cout << "coll1 == coll2" << std::endl;
	}
	else {
		std::cout << "coll1 != coll2" << std::endl;
	}

	if (std::equal(coll1.begin(), coll1.end(), coll2.begin(), bothEvenOrOdd)) {
		std::cout << "even and odd correspond " << std::endl;
	}
	else {
		std::cout << "not correspond" << std::endl;
	}
}


int main() {
	test09();
	// test08();
	// test07();
	// test06();
	// test05();
	// test04();
	// test03();
	// test02();
	// test01();
	return 0;
}