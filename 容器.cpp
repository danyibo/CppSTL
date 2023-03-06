#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <forward_list>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

// ���·ǳ���Ҫ�Ƕ������ĸ��ֽ��ܣ���Ҫ�ǳ����������ո����������÷�

// �ȼ򵥵�ʹ��һ�¸�������
namespace AllContainerAndAlgorithm {
	void test_vector() {
		std::vector<int> coll;
		for (int i = 0; i <= 6; ++i) {
			coll.push_back(i);
		}
		for (int i = 0; i <= 6; ++i) {
			std::cout << coll[i] << " ";
		}std::cout << std::endl;
	}

	void test_deque() {
		std::deque<float> coll;
		for (int i = 0; i <= 6; ++i) {
			coll.push_front(i * 1.1);
		}
		for (int i = 0; i <= 6; ++i) {
			std::cout << coll[i] << " ";
		}std::cout << std::endl;
	}

	void test_array() {
		std::array<std::string, 5> coll = { "hello", "world" };
		for (int i = 0; i < coll.size(); ++i) {
			std::cout << i << ": " << coll[i] << " ";
		}std::cout << std::endl;
	}

	void test_list() {
		std::list<char> coll;
		for (char c = 'a'; c <= 'z'; ++c) {
			coll.push_back(c);
		}
		for (auto elem : coll) {
			std::cout << elem << " ";
		}std::cout << std::endl;
		
		while (!coll.empty()) {
			std::cout << coll.front() << " ";
			coll.pop_front();
		}std::cout << std::endl;
	}

	void test_forward_list() {
		std::forward_list<long> coll = { 2, 3, 5, 7, 11, 14, 3, 10 };
		coll.resize(9);
		coll.resize(10, 99);
		for (auto elem : coll) {
			std::cout << elem << " ";
		}std::cout << std::endl;
	}

	bool sort_by_size(std::string& s1, std::string& s2) {
		return s1.size() < s2.size();
	}

	void test_multiset() {
		std::multiset<std::string> cities{
			"shanghai", "beijing", "shenzheng", "guangzhou"
		}; // ��ʼ����ʱ����Ѿ��Զ�������
		for (const auto& elem : cities) {
			std::cout << elem << " ";
		}std::cout << std::endl;

	}


	void test_map() {
		std::multimap<int, std::string> coll;
		coll = {
			{5, "shanghai"},
			{3, "beijing"},
			{1, "guangdong"},
			{34, "lanzhou"}
		};
		for (auto elem : coll) {
			std::cout << elem.first << "->" << elem.second << " ";
		}std::cout << std::endl;
	}

	void test_associative_array() {
		// ���Թ���ʽ���飬����ֵ��Ϊ����
		std::unordered_map<std::string, float> coll;

		coll["V1"] = 0.19;
		coll["V2"] = 0.88;
		coll["V3"] = 0.99;

		std::cout << coll["V1"] - coll["V2"] << std::endl;
		// std::cout << coll.at("V1") - coll.at("V5") << std::endl;
	
	}


	void test_algorithm() {
		std::vector<int> coll = { 2, 4, 5, 1, 6, 3 };
		
		auto minpos = std::min_element(coll.begin(), coll.end());
		std::cout << "��СֵΪ��" << *minpos << std::endl;
		auto maxpos = std::max_element(coll.begin(), coll.end());
		std::cout << "���ֵΪ��" << *maxpos << std::endl;

		std::sort(coll.begin(), coll.end());

		auto pos3 = std::find(coll.begin(), coll.end(), 3);
		std::reverse(pos3, coll.end());

		for (auto elem : coll) {
			std::cout << elem << " ";
		}std::cout << std::endl;
	} 

	void test_range() {
		std::list<int> coll;
		for (int i = 20; i < 40; ++i) {
			coll.push_back(i);
		}
		auto pos3 = std::find(coll.begin(), coll.end(), 3);
		if (pos3 == coll.end()) {
			std::cout << "û���ҵ���" << std::endl;
		}
		std::reverse(pos3, coll.end());

		std::list<int>::iterator pos25, pos35;
		pos25 = std::find(coll.begin(), coll.end(), 25);
		pos35 = std::find(coll.begin(), coll.end(), 35);

		std::cout << "max: " << *std::max_element(pos25, pos35) << std::endl;
		std::cout << "min: " << *std::min_element(pos25, pos35) << std::endl;

		// ���Կ��������ҵ�����34���������ֵ35�����������������û�а���35����
		++pos35; // ��������������Ϳ�����

		std::cout << "max: " << *std::max_element(pos25, pos35) << std::endl;
		
		// �����֪�� 25 ��35֮ǰ����Ҫ��ô����
		auto pos = std::find_if(coll.begin(), coll.end(), [](int i) {
			return i == 35 || i == 35;
			});
		if (pos == coll.end()) {
			std::cout << "������������Ԫ��" << std::endl;
		}
		else if (*pos == 25) {
			auto pos25 = pos;
			std::cout << "�ҵ���25" << std::endl;
			auto pos35 = find(++pos, coll.end(), 35);
		}
		else {
			auto pos35 = pos;
			std::cout << "�ҵ���35" << std::endl;
		}


	}


	void test_copy() {
		std::list<int> coll1 = { 1, 2, 3, 4, 5, 6 };
		std::vector<int> coll2;
		coll2.resize(coll1.size());
		std::copy(coll1.cbegin(), coll1.cend(), coll2.begin());
		for (auto elem : coll2) {
			std::cout << elem << " ";
		}std::cout << std::endl;
	}

};




int main() {
	AllContainerAndAlgorithm::test_vector();
	AllContainerAndAlgorithm::test_deque();
	AllContainerAndAlgorithm::test_array();
	AllContainerAndAlgorithm::test_list();
	AllContainerAndAlgorithm::test_forward_list();
	AllContainerAndAlgorithm::test_multiset();
	AllContainerAndAlgorithm::test_map();
	AllContainerAndAlgorithm::test_associative_array();
	AllContainerAndAlgorithm::test_algorithm();
	AllContainerAndAlgorithm::test_range();
	AllContainerAndAlgorithm::test_copy();
}
