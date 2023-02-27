#include<iostream>
#include<string>
#include<exception>   
#include<utility>
#include<typeinfo>
#include<tuple>
/*
  1. pair
 

*/

namespace Ch5 {

	template<typename T1, typename T2>
	std::ostream& operator<<(std::ostream& stm, const std::pair<T1, T2>& p) {
		return stm << "[" << p.first << " , " << p.second << "]" << std::endl;
	}
	void test01() {
		typedef std::pair<int, float> IntFloatPair;
		IntFloatPair p(43, 3.14);
		std::cout << "std::get<0>(p): " << std::get<0>(p) << std::endl;
		std::cout << "std::get<1>(p): " << std::get<1>(p) << std::endl;

		std::cout << "size = " << std::tuple_size<IntFloatPair>::value << std::endl;
		// std::tuple_element<0, IntFloatPair>::type 返回的是第一个元素的类型
		// std::tuple_element<1, IntFloatPair>::type 返回的是第二个元素的类型
		std::tuple_element<0, IntFloatPair>::type x = 1;
		std::tuple_element<1, IntFloatPair>::type y = 1.4;

		// 可以用下面的方式进行类型输出
		std::cout << typeid(std::tuple_element<0, IntFloatPair>::type).name() << std::endl;
		std::cout << typeid(std::tuple_element<1, IntFloatPair>::type).name() << std::endl;
		
	}

	class Foo {
	public:
		Foo(std::tuple<int, float>) {
			std::cout << "Foo::Foo(tuple)" << std::endl;
		}
		template<typename... Args>
		Foo(Args... arg) {
			std::cout << "Foo::Foo(arg...)" << std::endl;
		}
	};


	void test_foo() {
		std::tuple<int, float> t(1, 2.2);
		std::pair<int, Foo> p1(42, t); // Foo::Foo(tuple)
		std::pair<int, Foo> p2(std::piecewise_construct, std::make_tuple(43), t);

	}

	void test02() {

	}
};

int main() {
	Ch5::test01();
	Ch5::test_foo();
	return 0;
}