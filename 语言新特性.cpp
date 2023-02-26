#include<iostream>
#include<vector>
#include<string>



namespace Ch3 {
	
	//// 3.1.2 auto的语言特性：一定要初始化
	void test_auto() {
		auto i = 42;

		// double f();
		// auto d = f();
		static auto vat = 0.9;

		std::vector<std::string> v;

		auto pos = v.begin();
	}
	auto l = [](int x) -> bool {
		if (x > 0) { return true; }
		else { return false; }
	};

	////////////////////////////////////////////////////////////////////////

	// 一致初始化，初值列
	int values[]{ 1, 2, 3, 4, 5 };
	void show_values() {
		for (int i : values)
		{
			std::cout << i << " ";
		}
	}

	// 初值列：强迫造成所谓的初始化
	// 注意窄化不可以使用{}
	// 窄化，降低精度初始化 如：int{5.6} // ERROR
	void Initializer() {
		int i;
		int j{};
		int* p;
		int* q{};
		// std::cout << "i = " << i << std::endl; // 编译不过，未初始化
		std::cout << "j = " << j << std::endl;
		// std::cout << "p = " << p << std::endl; // 编译不过
		std::cout << "q = " << q << std::endl;

	}

	void print(std::initializer_list<int> vals) {
		for (auto p = vals.begin(); p != vals.end(); ++p) {
			std::cout << *p << " ";
		}std::cout << std::endl;
	}

	class P {
	public:
		P(int, int) {
			std::cout << "两个参数的构造" << std::endl;
		}
		P(std::initializer_list<int>) {
			std::cout << "列表初始化的构造" << std::endl;
		}
		explicit P(int a, int b, int c) {
			std::cout << "三个参数的构造，不允许隐式转换" << std::endl;
		}
	};

	void test_P() {
		P x(5, 5); // 两个参数的构造
		P y{ 3, 10 }; // 列表初始化的构造
		P z = { 8,9 }; // 列表初始化的构造
		P a(1, 2, 3);
		P b = { 1, 2,3 };
	}
	

	
	
}



int main() {
	bool b = Ch3::l(4);
	std::cout << b << std::endl;

	Ch3::show_values();
	std::cout << std::endl;
	Ch3::Initializer();
	Ch3::print({ 12, 3, 4, 5, 9 });
	Ch3::test_P();
	
}
