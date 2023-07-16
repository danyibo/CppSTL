#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

void test01() {
	vector<int> coll;
	for (int i = -3; i < 9; ++i) {
		coll.push_back(i);
	}

	cout << "distance = " << coll.end() - coll.begin() << endl;
}

class MeanValue {
private:
	long num;
	long sum;
public:
	MeanValue() :sum(0), num(0) {}

	void operator()(int elem) {
		++num;
		sum += elem;
	}

	double value() {
		return static_cast<double> (sum) / static_cast<double>(num);
	}
};


void test02() {
	std::vector<int> coll = { 1, 2, 3, 4,5 };
	MeanValue mv = std::for_each(coll.begin(), coll.end(), MeanValue());
	std::cout << "mean = " << mv.value() << std::endl;
}


void test03() {
	auto plus10 = std::bind(std::plus<int>(), std::placeholders::_1, 10);
	std::cout << plus10(7) << std::endl;

	auto plus10times2 = std::bind(std::multiplies<int>(), 
		std::bind(std::plus<int>(), std::placeholders::_1, 10), 2);
	std::cout << plus10times2(7) << std::endl;


	auto pow3 = std::bind(std::multiplies<int>(),
		std::bind(std::multiplies<int>(),
			std::placeholders::_1,
			std::placeholders::_1),
		std::placeholders::_1);
	std::cout << pow3(3) << std::endl;
}


int main() {
	//test01();
	test03();
	//system("puase");
	return 0;
}