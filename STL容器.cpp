#include <array>
#include <algorithm>
#include <numeric>
#include <string>
#include <iostream>
#include <functional>
#include <vector>




template<typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "") {
	std::cout << optstr;
	for (const auto& elem : coll) {
		std::cout << elem << " ";
	}std::cout << std::endl;
}


void test_array() {
	std::array<int, 10> a = { 11, 22, 3, 44 };
	PRINT_ELEMENTS(a);
	a.back() = 99999;
	a[a.size() - 2] = 42;
	PRINT_ELEMENTS(a);

	std::cout << "sum: "
		<< std::accumulate(a.begin(), a.end(), 0)
	<< std::endl;

	std::transform(a.begin(), a.end(), a.begin(), std::negate<int>());
	PRINT_ELEMENTS(a);
}


void test_vector() {
	std::vector<std::string> sentence;
	sentence.reserve(5);

	sentence.push_back("Hello,");
	sentence.insert(sentence.end(), { "how", "are", "you", "?" });
	std::copy(sentence.cbegin(), sentence.cend(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << std::endl;

	std::cout << " max_size(): " << sentence.max_size() << std::endl;
	std::cout << " size(): " << sentence.size() << std::endl;
	std::cout << " capacity() " << sentence.capacity() << std::endl;

	std::swap(sentence[1], sentence[3]);
	sentence.insert(std::find(sentence.begin(), sentence.end(), "?"), "always");
	std::copy(sentence.cbegin(), sentence.cend(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << std::endl;
	std::cout << " size(): " << sentence.size() << std::endl;
	std::cout << " capacity() " << sentence.capacity() << std::endl;
	
	sentence.pop_back();
	sentence.pop_back();
	std::cout << " size(): " << sentence.size() << std::endl;
	std::cout << " capacity() " << sentence.capacity() << std::endl;

	sentence.shrink_to_fit();
	std::cout << " size(): " << sentence.size() << std::endl;
	std::cout << " capacity() " << sentence.capacity() << std::endl;




}



int main() {
	// test_array();
	test_vector();
	return 0;
}