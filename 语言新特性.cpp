#include<iostream>
#include<vector>
#include<string>
#include<set>





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
		P a(1, 2, 3); // 三个参数的构造，不允许隐式转换
		P b = { 1, 2,3 }; // 列表初始化的构造

	}
	
	void test_move() {
		/*
		  对象被move掉后将处于：有效但是不确定状态！
		  move是针对临时对象的，该对象之后将不在使用。因此，如果不是临时对象，使用move后，最好将对象清理掉
		*/
		std::string x = { "test move" };
		std::vector<std::string> v;
		v.push_back(std::move(x));
		x.clear(); // 清理掉对象
		std::cout << v[0] << std::endl;

		//// 以下修改将不成功，因为已经将x对象moved掉了
		//x[0] = 'T';
		//std::cout << x << std::endl;
	}
	
	
	void test_RowString() {
		std::string x = R"nc(a\
			b\nc()"
			)nc";
		std::cout << x << std::endl;
	}
	
	//constexpr int square(int x) {
	//	return x * x;
	//}
	//void test_constexpr() {
	//	float a[square(9)];
	//	std::cout << a[square(9)] << std::endl;
	//}

	void print_template(){}
	template<typename T, typename... Types>
	void print_template(const T& firstArg, const Types&... args) {
		std::cout << firstArg << std::endl;
		print_template(args...);
	}
	void test_varidiac_template() {
		print_template(7.5, "hello", 45, 56);
	}

	auto lambda_test = [] {std::cout << "hello lambda" << std::endl; };

}



int main() {
	bool b = Ch3::l(4);
	std::cout << b << std::endl;

	Ch3::show_values();
	std::cout << std::endl;
	Ch3::Initializer();
	Ch3::print({ 12, 3, 4, 5, 9 });
	Ch3::test_P();

	Ch3::test_move();
	Ch3::test_RowString();
	// Ch3::test_constexpr();
	Ch3::test_varidiac_template();
	Ch3::lambda_test();
	
	
}
