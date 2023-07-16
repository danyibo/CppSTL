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



int main() {
	test01();
	return 0;
}