#include <iostream>
#include <string>
#include <exception>   
#include <utility>
#include <typeinfo>
#include <tuple>
#include <complex>
#include <memory>
#include <vector>
#include <functional>





namespace TestPair {
	// 关于Pair的一些基本操作

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
		int i = 0;
		auto p = std::make_pair(std::ref(i), std::ref(i));
		++p.first;
		++p.second;
		std::cout << "i = " << i << std::endl;
	}

	void test03() {
		std::pair<char, char> p = std::make_pair('x', 'y');
		char c;
		std::tie(std::ignore, c) = p;
		std::cout << c << std::endl;
 	}

};


namespace TestTuple {
	using namespace std;
	void test01() {
		tuple<string, int, int, complex<double>> t;
		tuple<int, float, string> t1(3, 30.43, "nice");

		cout << get<0>(t1) << endl;
		cout << get<1>(t1) << endl;
		cout << get<2>(t1) << endl;

		auto t2 = make_tuple(22, 33, "nico");

		get<1>(t1) = get<1>(t2);

		if (t1 < t2) {
			t1 = t2;
		}

	}

	void test02() {
		// reference
		string s = "world";
		tuple<string&> t(s);
		get<0>(t) = "hello";
		cout << s << endl;
	}

	void test03() {
		std::string s = "test";
		auto x = std::make_tuple(s);
		std::get<0>(x) = "my value";

		std::cout << s << std::endl;
		auto y = std::make_tuple(ref(s));
		std::get<0>(y) = "my value";

		std::cout << s << std::endl;

		// 使用tie来以ref的方式构建一个tuple
		std::tuple<int, float, std::string> t(44, 1.9, "more light");
		int i;
		float f;
		std::string ss;
		std::tie(i, f, ss) = t;

		
		std::cout << "i = " << i << std::endl;
		std::cout << "f = " << f << std::endl;
		std::cout << "ss = " << ss << std::endl;
		 
		// 使用ignore来跳过某些元素
		int ii;
		std::string sss;
		std::tie(ii, std::ignore, sss) = t;
		std::cout << ii << std::endl;
		std::cout << sss << std::endl;
		
		typename std::tuple<int, float, std::string> TupleType;


		
	
	}

};


// tuple 

template<int IDX, int MAX, typename... Args>
struct PRINT_TUPLE {
	static void print(std::ostream& strm, const std::tuple<Args...>& t) {
		strm << std::get<IDX>(t) << (IDX + 1 == MAX ? " " : ",");
		PRINT_TUPLE<IDX + 1, MAX, Args...>::print(strm, t);
	}
};

/// 智能指针



namespace SmartPoint {

	// 使用 shared_ptr
	void test01() {

		std::shared_ptr<std::string> pNico(new std::string("nico"));
		std::shared_ptr<std::string> pJutta(new std::string("jutta"));

		// 修改其中的元素
		(*pNico)[0] = 'N';
		pJutta->replace(0, 1, "J"); // replace 前面的两个参数是迭代器的范围
        /*std::cout << *pNico.get() << std::endl;
		std::cout << *pJutta.get() << std::endl;*/

		std::vector<std::shared_ptr<std::string>> whoMadeCoffee;
		whoMadeCoffee.push_back(pJutta);
		whoMadeCoffee.push_back(pJutta);
		whoMadeCoffee.push_back(pNico);
		whoMadeCoffee.push_back(pJutta);
		whoMadeCoffee.push_back(pNico);

		for (auto ptr : whoMadeCoffee) {
			std::cout << *ptr << std::endl;
		}

		std::cout << whoMadeCoffee[0].use_count() << std::endl;  // 这里输出是4，因为容器中使用了3次，前面也使用了一次
	}

	// 智能指针的几种初始化方式
	void test02() {
		//1. new一个指针，传入构造函数中
		std::shared_ptr<std::string> p1(new std::string("test"));
		//2. 使用make_shared
		std::shared_ptr<std::string> p2 = std::make_shared<std::string>("test");
		auto p3 = std::make_shared<std::string>("test");
		std::cout << *p3.get() << std::endl;
		//3. 使用reset
		std::shared_ptr<std::string> p4;
		p4.reset(new std::string("test"));
		std::cout << *p4 << std::endl;
	}

	// 定义一个删除器
	void test03() {
		// 定义一个元素
		std::shared_ptr<std::string> PPP (new std::string("nice"), 
			[](std::string* p) {std::cout << "Delete " << *p << std::endl;
		delete p; });

		// 定义一个array
		std::shared_ptr<int> pArray(new int[5], [](int* p) {delete[] p;
		std::cout << "array 析构 " << std::endl; });
		/*std::shared_ptr<int> pArray(new int[5],
			std::default_delete<int[]>());*/
		memset(pArray.get(), 0, sizeof(int) * 5);
		for (int i = 0; i < 5; i++) {
			std::cout << pArray.get()[i] << " ";
		}std::cout << std::endl;

		std::shared_ptr<int[]> pppppp(new int[10]);
		std::unique_ptr<int[]> p22222(new int[10]);

	}

	// 处理共享内存---??? 这部分要在linux上进行


	// weak_ptr：共享但不拥有！
	// 使用weak_ptr
	using namespace std;
	class Person {
	private:
	public:
		string name;
		shared_ptr<Person> mother;
		shared_ptr<Person> father;
		vector<weak_ptr<Person>> kids;

		Person(const string& n, shared_ptr<Person> m = nullptr, shared_ptr<Person> f = nullptr) :
			name(n), mother(m), father(f) {}
		~Person() {
			cout << "delete " << name << endl;
		}
	};
	shared_ptr<Person> initFamily(const string& name) {
		shared_ptr<Person> mom(new Person(name + "'s mom"));
		shared_ptr<Person> dad(new Person(name + "'s data"));
		shared_ptr<Person> kid(new Person(name, mom, dad));
		mom->kids.push_back(kid);
		dad->kids.push_back(kid);
		return kid;

	}

	void test04() {
		shared_ptr<Person> p = initFamily("nico");
		cout << "nico family exists" << endl;
		cout << "- nice is shared " << p.use_count() << " times" << endl;
		cout << "- name of 1st kid of noic mom: " << p->mother->kids[0].lock()->name << endl;
	}

	void test05() {
		// 查看weak_ptr是否还存在
		try
		{
			shared_ptr<string> sp(new string("ni"));
			weak_ptr<string> wp = sp;
			sp.reset();
			cout << wp.use_count() << endl;
			cout << boolalpha << wp.expired() << endl;
			shared_ptr<string> p(wp);
		}
		catch (const std::exception& e)
		{
			cerr << "exception " << e.what() << endl;
		}
	} 

	// get_delter()
	void test06() {
		auto del = [](int* p) {delete p; };
		std::shared_ptr<int> p(new int(1), del);
		decltype(del)* pd = std::get_deleter<decltype(del)>(p);
		std::cout << pd << std::endl;

	}

	//unique处理array
	//使用自己提供的删除器
	void test07() {
		///// 01: 指明类型
		///*unique_ptr<int, void(*)(int*)> up(new int[3]
		//	, 
		//	[](int* p) {
		//		delete[] p;
		//		std::cout << "调用析构函数" << std::endl;}
		//	);*/
		///// 02：使用function
		//unique_ptr<int, std::function<void(int*)>> up(new int[3]
		//	,
		//	[](int* p) {
		//		delete[] p;
		//		std::cout << "调用析构函数" << std::endl; }
		//);
		///// 03：使用decltype
		//
		//up.get()[0] = 1;
		//up.get()[1] = 0;
		//up.get()[2] = 101000;

		//for (int i = 0; i < 3; i++) {
		//	std::cout << up.get()[0] << std::endl;
		//}

		std::string xxx = "test";
		std::unique_ptr<std::string> px(new std::string(xxx));
		std::string* result = px.release();
		std::cout << "结果为：" << *result << std::endl;
	}



};

int main() {
	SmartPoint::test07();
	return 0;
}