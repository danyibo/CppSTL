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
#include <type_traits>
#include <algorithm>




namespace TestPair {
	// ����Pair��һЩ��������

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
		// std::tuple_element<0, IntFloatPair>::type ���ص��ǵ�һ��Ԫ�ص�����
		// std::tuple_element<1, IntFloatPair>::type ���ص��ǵڶ���Ԫ�ص�����
		std::tuple_element<0, IntFloatPair>::type x = 1;
		std::tuple_element<1, IntFloatPair>::type y = 1.4;

		// ����������ķ�ʽ�����������
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

		// ʹ��tie����ref�ķ�ʽ����һ��tuple
		std::tuple<int, float, std::string> t(44, 1.9, "more light");
		int i;
		float f;
		std::string ss;
		std::tie(i, f, ss) = t;

		
		std::cout << "i = " << i << std::endl;
		std::cout << "f = " << f << std::endl;
		std::cout << "ss = " << ss << std::endl;
		 
		// ʹ��ignore������ĳЩԪ��
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

/// ����ָ��



namespace SmartPoint {

	// ʹ�� shared_ptr
	void test01() {

		std::shared_ptr<std::string> pNico(new std::string("nico"));
		std::shared_ptr<std::string> pJutta(new std::string("jutta"));

		// �޸����е�Ԫ��
		(*pNico)[0] = 'N';
		pJutta->replace(0, 1, "J"); // replace ǰ������������ǵ������ķ�Χ
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

		std::cout << whoMadeCoffee[0].use_count() << std::endl;  // ���������4����Ϊ������ʹ����3�Σ�ǰ��Ҳʹ����һ��
	}

	// ����ָ��ļ��ֳ�ʼ����ʽ
	void test02() {
		//1. newһ��ָ�룬���빹�캯����
		std::shared_ptr<std::string> p1(new std::string("test"));
		//2. ʹ��make_shared
		std::shared_ptr<std::string> p2 = std::make_shared<std::string>("test");
		auto p3 = std::make_shared<std::string>("test");
		std::cout << *p3.get() << std::endl;
		//3. ʹ��reset
		std::shared_ptr<std::string> p4;
		p4.reset(new std::string("test"));
		std::cout << *p4 << std::endl;
	}

	// ����һ��ɾ����
	void test03() {
		// ����һ��Ԫ��
		std::shared_ptr<std::string> PPP (new std::string("nice"), 
			[](std::string* p) {std::cout << "Delete " << *p << std::endl;
		delete p; });

		// ����һ��array
		std::shared_ptr<int> pArray(new int[5], [](int* p) {delete[] p;
		std::cout << "array ���� " << std::endl; });
		/*std::shared_ptr<int> pArray(new int[5],
			std::default_delete<int[]>());*/
		memset(pArray.get(), 0, sizeof(int) * 5);
		for (int i = 0; i < 5; i++) {
			std::cout << pArray.get()[i] << " ";
		}std::cout << std::endl;

		std::shared_ptr<int[]> pppppp(new int[10]);
		std::unique_ptr<int[]> p22222(new int[10]);

	}

	// �������ڴ�---??? �ⲿ��Ҫ��linux�Ͻ���


	// weak_ptr��������ӵ�У�
	// ʹ��weak_ptr
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
		// �鿴weak_ptr�Ƿ񻹴���
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

	//unique����array
	//ʹ���Լ��ṩ��ɾ����
	void test07() {
		///// 01: ָ������
		///*unique_ptr<int, void(*)(int*)> up(new int[3]
		//	, 
		//	[](int* p) {
		//		delete[] p;
		//		std::cout << "������������" << std::endl;}
		//	);*/
		///// 02��ʹ��function
		//unique_ptr<int, std::function<void(int*)>> up(new int[3]
		//	,
		//	[](int* p) {
		//		delete[] p;
		//		std::cout << "������������" << std::endl; }
		//);
		///// 03��ʹ��decltype
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
		std::cout << "���Ϊ��" << *result << std::endl;
	}


	




};


namespace TypeTrait{
	template<typename T>
	void foo(const T& val) {
		// std::is_pointer<T>::value  Ϊһ��������
		if (std::is_pointer<T>::value) {
			std::cout << "foo() called for a pointer" << std::endl;
		}
		else {
			std::cout << "foo() called for a value" << std::endl;
		}
	}

	// �ڶ���ʵ�ַ���
	template<typename T>
	void foo_impl(const T& val, std::true_type) {
		std::cout << "foo() called for pointer to " << *val << std::endl;
	}

	template<typename T>
	void foo_impl(const T& val, std::false_type) {
		std::cout << "foo() called for value to " << val << std::endl;
	}
	
	template<typename T>
	void foo2(const T& val) {
		foo_impl(val, std::is_pointer<T>());
	}

	void test01() {
		int a{ 10 };
		int* pa = &a;
        // ʹ��ָ����Ϊ����
		foo(pa);
		// ʹ��ֵ��Ϊ����
		foo(a);

		std::cout << "ʹ�õڶ���ʵ�ַ�ʽ��" << std::endl;
		foo2(pa);
		foo2(a);
	}

	// ���ɵ��ö�����Ϊ������
	// ����÷���python�е������Ƶĵط�
	int func(int x, int y) { return x * y; }
	void test02() {
		std::vector<std::function<int(int, int)>> task;
		task.push_back(func);
		task.push_back([](int a, int b) {return a + b; });
		for (auto it = task.begin(); it != task.end(); ++it) {
			std::cout << (*it)(3, 6) << " ";
		}
	}
		

};


// �ṩһЩ��������
namespace SomeHelpFunction {
	// �Ƚ����ֵ����Сֵ
	bool int_ptr_less(int* a, int* b) {
		return *a < *b;
	}


	void test01() {
		int x = 13;
		int y = 1;
		int z = 3;
		int* px = &x;
		int* py = &y;
		int* pz = &z;

		int* pmax = std::max(px, py, int_ptr_less);
		std::cout << "max = " << *pmax << std::endl;

		// std::pair<int*, int*> extrems = std::minmax({ px, py, pz }, int_ptr_less);

		std::pair<int*, int*> extrems = std::minmax({ px, py, pz },
			[](int* a, int* b) {return *a < *b; });
		std::cout << "max = " << *extrems.second << std::endl;
		std::cout << "min = " << *extrems.first << std::endl;
	
	}

	// ��������ֵ
	class MyCountainer {
	private:
		int* elem;
		int numElem;
	public:
		MyCountainer(const int n):numElem(n) {
			elem = new int[n];
			for (int i = 0; i < n; ++i)
				elem[i] = i;
		}
		~MyCountainer() {
			std::cout << "������������" << std::endl;
			delete[] elem;
		}
		void swap(MyCountainer& x) {
			std::swap(elem, x.elem);
			std::swap(numElem, x.numElem);
		}
		void show() {
			for (int i = 0; i < numElem; ++i) {
				std::cout << elem[i] << " ";
			}std::cout << std::endl;
		}
	};

	inline void swap(MyCountainer& c1, MyCountainer& c2) {
		c1.swap(c2);
	}

	void test02() {
		MyCountainer c1(10);
		c1.show();
		MyCountainer c2(20);
		c2.show();
		std::cout << "���н���" << std::endl;
		c1.swap(c2);
		std::cout << "c1 = ";
		c1.show();
		


	}
};


int main() {
	SomeHelpFunction::test02();
	
	return 0;
}