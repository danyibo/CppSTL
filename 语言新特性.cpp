#include<iostream>
#include<vector>
#include<string>
#include<set>





namespace Ch3 {
	
	//// 3.1.2 auto���������ԣ�һ��Ҫ��ʼ��
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

	// һ�³�ʼ������ֵ��
	int values[]{ 1, 2, 3, 4, 5 };
	void show_values() {
		for (int i : values)
		{
			std::cout << i << " ";
		}
	}

	// ��ֵ�У�ǿ�������ν�ĳ�ʼ��
	// ע��խ��������ʹ��{}
	// խ�������;��ȳ�ʼ�� �磺int{5.6} // ERROR
	void Initializer() {
		int i;
		int j{};
		int* p;
		int* q{};
		// std::cout << "i = " << i << std::endl; // ���벻����δ��ʼ��
		std::cout << "j = " << j << std::endl;
		// std::cout << "p = " << p << std::endl; // ���벻��
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
			std::cout << "���������Ĺ���" << std::endl;
		}
		P(std::initializer_list<int>) {
			std::cout << "�б��ʼ���Ĺ���" << std::endl;
		}
		explicit P(int a, int b, int c) {
			std::cout << "���������Ĺ��죬��������ʽת��" << std::endl;
		}
	};

	void test_P() {
		P x(5, 5); // ���������Ĺ���
		P y{ 3, 10 }; // �б��ʼ���Ĺ���
		P z = { 8,9 }; // �б��ʼ���Ĺ���
		P a(1, 2, 3); // ���������Ĺ��죬��������ʽת��
		P b = { 1, 2,3 }; // �б��ʼ���Ĺ���

	}
	
	void test_move() {
		/*
		  ����move���󽫴��ڣ���Ч���ǲ�ȷ��״̬��
		  move�������ʱ����ģ��ö���֮�󽫲���ʹ�á���ˣ����������ʱ����ʹ��move����ý����������
		*/
		std::string x = { "test move" };
		std::vector<std::string> v;
		v.push_back(std::move(x));
		x.clear(); // ���������
		std::cout << v[0] << std::endl;

		//// �����޸Ľ����ɹ�����Ϊ�Ѿ���x����moved����
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
