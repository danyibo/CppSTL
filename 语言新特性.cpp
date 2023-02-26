#include<iostream>
#include<vector>
#include<string>



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
