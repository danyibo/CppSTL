#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<cstdlib>
#include<algorithm>


class Tv {
public:

	/*
	* 枚举类型：定义一个符号常量，用来替代const
	* 每个常量都有一个值，这个值从0开始以此类推；也可以给这个值进行赋值
	*/
	
	friend class Remote;
	enum{off, on}; 
	enum{min_val, max_val = 20};
	enum{antenna, cable};
	enum{TV, DVD};

	Tv(int s = off, int mc = 125) : state(s), volume(5), maxvhannel(mc), channel(12), mode(cable), input(TV) 
	{}

	void onoff() { state = (state == on) ? off : on; }
	bool ison()const { return state == on; }
	bool volup() {
		if (volume < max_val) {
			volume++;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool voldown() {
		if (volume > min_val) {
			volume--;
			return true;
		}
		else {
			return false;
		}
	}
	void chanup() {
		if (channel < maxvhannel) {
			channel++;
		}
		else {
			channel = 1;
		}
	}
	void chandown() {
		if (channel > 1) {
			channel--;
		}
		else {
			channel = maxvhannel;
		}
	}
	void set_mode() { mode = (mode == antenna) ? cable : antenna; }
	void set_input() { input = (input == TV) ? DVD : TV; }
	void setting()const {
		std::cout << "TV is " << (state == off ? "Off" : "On") << std::endl;
		if (state == on) {
			std::cout << "Volume setting = " << volume << std::endl;
			std::cout << "Channel setting = " << channel << std::endl;
			std::cout << "Mode = " << (mode == antenna ? "antenna" : "cable") << std::endl;
			std::cout << "Input = " << (input == TV ? "TV" : "DVD") << std::endl;
		}
	}

private:
	int state;
	int volume;
	int maxvhannel;
	int channel;
	int mode;
	int input;



};


class Remote {
private:
	int mode;
public:
	Remote(int m = Tv::TV) : mode(m){}
	bool volup(Tv& v) { return v.volup(); }
	bool vodown(Tv& v) { return v.voldown(); }
	void onoff(Tv& t) { t.onoff(); }
	void chanup(Tv& t) { t.chanup(); }
	void chandown(Tv& t) { t.chandown(); }
	void set_chan(Tv& t, int c) { t.channel = c; }
	void set_mode(Tv& t) { t.set_mode(); }
	void set_input(Tv& t) { t.set_input(); }

};


void test_tv() {
	Tv s42;
	std::cout << "initial-----" << std::endl;
	s42.setting();
	s42.onoff();
	s42.chanup();
	std::cout << "setting-----" << std::endl;
	s42.setting();
	Remote grey;

	grey.set_chan(s42, 10);
	grey.volup(s42);
	grey.volup(s42);
	std::cout << "setting after using remote-----" << std::endl;
	s42.setting();


}

double hmean(double a, double b) {
	if (a == -b) {
		std::cout << "untenable arguments to hmean " << std::endl;
		std::abort();
	}
	return 2.0 * a * b / (a + b);
}

void test_hmean() {
	// 获取某个容器的起始地址的方法
	std::vector<int> v = { 1, 2, 43, 9 };
	std::cout << &*v.begin() << std::endl;
	std::cout << v.data() << std::endl;
	std::cout << &v[0] << std::endl;


	//std::cout << hmean(1, 2) << std::endl;
	//std::cout << hmean(1, -1) << std::endl;

}
void test_string01() {
	using namespace std;
	//string one("Lottery Winter");
	//cout << one << endl;
	//string two(20, '*');
	//cout << two << endl;
	//string three(one);
	//cout << three << endl;
	//one += "Opps";
	//cout << one << endl;
	//two = "Sorry";
	//three[0] = 'P';
	//string four;
	//four = two + three;
	//cout << four << endl;


	std::string file_path = "E:\\C++\\tobuy.txt";

	ifstream fin;
	fin.open(file_path);
	if (fin.is_open() == false) {
		std::cout << "打开失败" << std::endl;
		cerr << "Can't open file ";
		exit(EXIT_FAILURE);
	}
	std::string item;
	int count = 0;
	getline(fin, item);
	cout << item << endl;
	//while (fin) {
	//	++count;
	//	cout << count << ": " << item << endl;
	//	getline(fin, item, ':');
	//}
	cout << "Done" << endl;
	fin.close();

	std::string x;
	std::cout << x.npos << std::endl;


	
}

#include<memory>
class Report {
private:
	std::string str;
public:
	Report(const std::string s) : str(s) {
		std::cout << "构造函数被调用" << std::endl;
	}
	~Report(){
		std::cout << "析构函数被调用" << std::endl;
	}
	void comment()const { std::cout << str << std::endl; }
};

void test_report() {
	std::shared_ptr<Report> ps(new Report("using auto ptr"));
	ps->comment();
}


void test02() {
	std::shared_ptr<std::string> file[3] = {
		std::shared_ptr<std::string>(new std::string("good")),
		std::shared_ptr<std::string>(new std::string("bad")),
		std::shared_ptr<std::string>(new std::string("test"))
	};
	std::shared_ptr<std::string> temp = file[2];
	for (int i = 0; i < 3; i++) {
		std::cout << *file[i] << std::endl;
	}
}

void test03() {
	std::unique_ptr<std::string> p1(new std::string("auto"));
	std::unique_ptr<std::string> p2;
	p2 = std::move(p1);
	// std::cout << *p1 << std::endl;
	std::cout << *p2 << std::endl;

	std::unique_ptr<double[]> pda(new double(5));


}


//struct Review {
//	std::string title;
//	int rating;
//};
//
//bool FillReview(Review& rr) {
//	std::cout << "Enter book title: " << std::endl;
//	std::getline(std::cin, rr.title);
//	if (rr.title == "quit") {
//		return false;
//	}
//	std::cout << "Enter book rating: " << std::endl;
//	std::cin >> rr.rating;
//	if (!std::cin) {
//		return false;
//	}
//	while (std::cin.get() != '\n')
//	{
//		continue;
//	}
//	return true;
//
//}
//void showReview(const Review& rr) {
//	std::cout << rr.rating << "\t" << rr.title << std::endl;
//}
//void test04() {
//	std::vector<Review> books;
//	Review temp;
//	while (FillReview(temp)) {
//		books.push_back(temp);
//	}
//	int num = books.size();
//
//	if (num > 0) {
//		std::cout << "Thanks you. Your enterd following: " << std::endl;
//		// 使用下标进行遍历
//		std::cout << "下表进行遍历" << std::endl;
//		for (int i = 0; i < num; i++) {
//			showReview(books[i]);
//		}
//		// 使用迭代器进行遍历
//		std::cout << "迭代器遍历，使用函数对象进行" << std::endl;
//		std::vector<Review>::iterator pr;
//		/*for (pr = books.begin(); pr != books.end(); pr++) {
//			showReview(*pr);
//		}*/
//		std::for_each(books.begin(), books.end(), showReview);
//		std::vector<Review> oldlist(books); //拷贝构造
//
//		if (num > 3) {
//			books.erase(books.begin() + 1, books.begin() + 3);
//			std::cout << "after erasure: " << std::endl;
//			for (pr = books.begin(); pr != books.end(); pr++) {
//				showReview(*pr);
//			}
//			books.insert(books.begin(), oldlist.begin() + 1, oldlist.begin() + 2);
//			std::cout << "after insert: " << std::endl;
//			for (pr = books.begin(); pr != books.end(); pr++) {
//				showReview(*pr);
//			}
//		}
//		books.swap(oldlist);
//		std::cout << "swapping old list with books " << std::endl;
//		for (pr = books.begin(); pr != books.end(); pr++) {
//			showReview(*pr);
//		}
//
//	}
//	else {
//		
//	}
//	
//	
//}
//
//// 测试随机打乱和排序
//
//bool operator<(const Review& r1, const Review& r2) {
//	if (r1.title < r2.title) {
//		return true;
//	}
//	else if (r1.title == r2.title && r1.rating < r2.rating) {
//		return true;
//
//	}
//	else {
//		return false;
//	}
//}
//
//void show(Review& r) {
//	std::cout << r.title << " " << r.rating << "  ";
//}
//
//void test05() {
//	Review book1 = { "三国", 4 };
//	Review book2 = { "水浒", 5 };
//	Review book3 = { "西游", 19 };
//	Review book4 = { "红楼", 1 };
//	std::vector<Review> books = { book1, book2, book3, book4 };
//	std::for_each(books.begin(), books.end(), show);
//	std::cout << std::endl;
//
//	std::random_shuffle(books.begin(), books.end());
//	std::for_each(books.begin(), books.end(), show);
//	std::cout << std::endl;
//
//	std::sort(books.begin(), books.end());
//	std::for_each(books.begin(), books.end(), show);
//
//}


void test06() {
	int cats[10] = { 5, 6, 7, 8, 2, 1, 0, 9, 10 };
	std::vector<int> dice(10);
	std::copy(cats, cats + 10, dice.begin());
	std::ostream_iterator<int, char> out_iter(std::cout, " ");
	std::copy(dice.begin(), dice.end(), out_iter);
	std::cout << std::endl;
	std::copy(dice.rbegin(), dice.rend(), out_iter);
	std::cout << std::endl;
	std::vector<int>::reverse_iterator ri;
	for (ri = dice.rbegin(); ri != dice.rend(); ++ri) {
		std::cout << *ri << " ";
	}
}

void output(const std::string& s) { std::cout << s << " "; }
void test07() {
	std::string s1[4] = { "Fine", "Fish", "Fanshion", "Fate" };
	std::string s2[2] = { "busy", "bats" };
	std::string s3[2] = { "silly", "singers" };

	std::vector<std::string> words(4);
	std::copy(s1, s1 + 4, words.begin());
	std::for_each(words.begin(), words.end(), output);
	std::cout << "  " << std::endl;
	std::copy(s2, s2 + 2, std::back_inserter<std::vector<std::string>>(words));
	std::for_each(words.begin(), words.end(), output);  
	std::cout << words.size() << std::endl;

	std::cout << "  " << std::endl;
	std::copy(s3, s3 + 2, std::insert_iterator<std::vector<std::string>>(words, words.begin()));
	std::for_each(words.begin(), words.end(), output);
	std::cout << words.size() << std::endl;
}

#include<list>
void output2(int i) { std::cout << i << " "; }
void test08() {
	std::list<int> one(5, 2);
	std::for_each(one.begin(), one.end(), output2);
}
#include<windows.h>

#include<tuple>
void test09() {
	std::tuple<std::string, std::vector<double>, std::list<int>> someVla("constance", { 1.1, 23 }, { 1,2, 3,4 });
	auto item = std::make_tuple("09--99898", 3, 20.09);
	auto book = std::get<0>(item);
	std::cout << book << std::endl;
	typedef decltype(item) trans;
	


}
template<typename T>
void show(T& c) {
	auto it = c.begin();
	// 注意这里可以写不等于，但是不能写小于
	for (; it != c.end(); it++) {
		std::cout << *it << " ";
	}std::cout << std::endl;

}

void test10() {
	// 测试list程序
	std::list<int> one(5, 2);
	int stuff[5] = { 1, 2, 4, 8, 6 };
	std::list<int> two;

	// insert
	// 第一个参数是插入的位置
	// 后面两个参数对应于要插入内容的迭代器范围，或者是指针范围
	two.insert(two.begin(), stuff, stuff + 5);
	show(two);

	int more[6] = { 6,4,2, 4, 6,5 };
	std::list<int> three(two);
	three.insert(three.end(), more, more + 6);
	show(three); 

	three.unique();
	std::cout << "unique " << std::endl;
	show(three);  // unique是什么东西？

	std::cout << "sort" << std::endl;
	three.sort();
	show(three);

	std::cout << "merge" << std::endl;
	two.sort(); // merge之前必须排序？？？
	three.merge(two);
	show(three);
	


}

#include<set>
void test11() {
	using namespace std;
	const int N = 6;
	string s1[N] = { "buffoon", "thinkers", "for", "heavy", "can", "for" };
	string s2[N] = { "metal", "any", "food", "elegant", "deliver","for" };

	set<string> A(s1, s1 + N);
	set<string> B(s2, s2 + N);
	ostream_iterator<string, char> out(cout, " ");
	cout << "Set A: " << endl;
	copy(A.begin(), A.end(), out);
	cout << endl;
	cout << "Set B: "  << endl;
	copy(B.begin(), B.end(), out);
	cout << endl;

	cout << "Union of A and B: " << endl; // 并集
	set_union(A.begin(), A.end(), B.begin(), B.end(), out);
	cout << endl;

	cout << "Insersection of A and B:" << endl;
	set_intersection(A.begin(), A.end(), B.begin(), B.end(), out);
	cout << endl;

	cout << "Difference of A and B: " << endl;
	set_difference(A.begin(), A.end(), B.begin(), B.end(), out);
	cout << endl;

	set<string> C;
	cout << "Set C " << endl;
	set_union(A.begin(), A.end(), B.begin(), B.end(),
		insert_iterator<set<string>>(C, C.begin()));
	copy(C.begin(), C.end(), out);
	cout << endl;

	string s3("GGGG");
	C.insert(s3);
	cout << "        " << endl;
	copy(C.begin(), C.end(), out);
	cout << endl;

	cout << "Showing a range" << endl;
	copy(C.lower_bound("gohost"), C.upper_bound("spook"), out);
	cout << endl;









}


#include <map>
#include <algorithm>
void test12() {
	typedef int KeyType;
	typedef std::pair<const KeyType, std::string> Pair;
	typedef std::multimap<KeyType, std::string> MapCode;
	using namespace std;
	MapCode codes;

	codes.insert(Pair(415, "San Francisco"));
	codes.insert(Pair(510, "Oakland"));
	codes.insert(Pair(718, "Brooklyn"));
	codes.insert(Pair(718, "Staten Island"));
	codes.insert(Pair(415, "San Rafael"));
	codes.insert(Pair(510, "Berkeley"));

	cout << codes.count(415) << endl;







}

template<class T>
class TooBig {
private:
	T cutoff;
public:
	TooBig(const T &t):cutoff(t){}
	bool operator()(const T& v) { return v > cutoff; }
};

void outint(int n) {
	std::cout << n << " ";
}


void test13() {

	using std::list;
	using std::cout;
	using std::endl;
	using std::for_each;
	using std::remove_if;

	// 仿函数
	TooBig<int> f100(100);
	int vals[10] = { 50, 100, 90, 180, 60, 210, 415, 88, 188, 201 };
	list<int> yadayada(vals, vals + 10); // range constructor
	list<int> etcetera(vals, vals + 10);
	cout << "Original lists:\n";
	for_each(yadayada.begin(), yadayada.end(), outint);
	cout << endl;
	for_each(etcetera.begin(), etcetera.end(), outint);
	cout << endl;

	yadayada.remove_if(f100); // 删除大于100的数字
	for_each(yadayada.begin(), yadayada.end(), outint);
	cout << "         " << endl;
	etcetera.remove_if(TooBig<int>(200)); // 删除大于200的数字
	for_each(etcetera.begin(), etcetera.end(), outint);

}

#include <functional>
void Show(double v)
{
	std::cout.width(6);
	std::cout << v << ' ';
}
void test14() {
	// 函数适配器
	const int LIM = 6;
	using namespace std;
	double arr1[LIM] = { 28, 29, 30, 35, 38, 59 };
	double arr2[LIM] = { 63, 65, 69, 75, 80, 99 };
	vector<double> gr8(arr1, arr1 + LIM);
	vector<double> m8(arr2, arr2 + LIM);
	cout.setf(ios_base::fixed);
	cout.precision(1);
	cout << "gr8:\t";
	for_each(gr8.begin(), gr8.end(), Show);
	cout << endl;
	cout << "m8: \t";
	for_each(m8.begin(), m8.end(), Show);
	cout << endl;

	vector<double> sum(LIM);
	transform(gr8.begin(), gr8.end(), m8.begin(), sum.begin(), plus<double>());
	cout << "sum:\t";
	for_each(sum.begin(), sum.end(), Show);
	cout << endl;

	vector<double> prob(LIM);
	transform(gr8.begin(), gr8.end(), prob.begin(), bind1st(multiplies<double>(), 2.5));
	cout << "prod:\t";
	for_each(prob.begin(), prob.end(), Show);
	cout << endl;
}

void test15() {
	using namespace std;
	string letters("gioadsjhgkhadkg");
	cout << "Permutations of " << letters << endl;
	sort(letters.begin(), letters.end());
	cout << letters << endl;
	next_permutation(letters.begin(), letters.end());
	cout << "   " << endl;
	cout << letters << endl;

}

void test16() {
	using namespace std;
	const int LIM = 10;
	int ar[LIM] = { 4, 5, 4, 2, 2, 3, 4, 8, 1, 4 };
	list<int> la(ar, ar + LIM);
	list<int> lb(la);
	cout << "Original list contents:\n\t";
	for_each(la.begin(), la.end(), Show);
	la.remove(4);
	cout << endl;
	cout << "After using the remove() method:\n";
	cout << "la:\t";
	for_each(la.begin(), la.end(), Show);
	cout << endl;
	list<int>::iterator last;
	last = remove(lb.begin(), lb.end(), 4);
	cout << "After using the remove() function:\n";
	cout << "lb:\t";
	for_each(lb.begin(), lb.end(), Show);
	cout << endl;

}

namespace test {

	using namespace std;
	char toLower(char ch) { return tolower(ch); }
	string& ToLower(string& st);
	void display(const string& s);
	string& ToLower(string& st)
	{
		transform(st.begin(), st.end(), st.begin(), toLower);
		return st;
	}

	void display(const string& s)
	{
		cout << s << " ";
	}

	void test17() {
		vector<string> words;
		cout << "Enter words (enter quit to quit):\n";
		string input;
		while (cin >> input && input != "quit")
			words.push_back(input);

		cout << "You entered the following words:\n";
		for_each(words.begin(), words.end(), display);
		cout << endl;
		
		set<string> wordset;
		transform(words.begin(), words.end(),
			insert_iterator<set<string>>(wordset, wordset.begin()), ToLower);
		cout << "\nAlphabetic list of words:\n";
		for_each(wordset.begin(), wordset.end(), display);
		cout << endl;

		map<string, int> wordmap;
		set<string>::iterator si;
		for (si = wordset.begin(); si != wordset.end(); si++) {
			 // si = wordset.begin(); si != wordset.end(); si++
			 wordmap[*si] = count(words.begin(), words.end(), *si);
		}

		cout << "\nWord frequency:\n";
		for (si = wordset.begin(); si != wordset.end(); si++)
			cout << *si << ": " << wordmap[*si] << endl;
	}


};


#include<thread>

void hello() {
	std::cout << "hello word" << std::endl;
}

class backgorund_taks {
public:
	void operator()()const{
		std::cout << "执行任务" << std::endl;
	}
};

void test17() {
	backgorund_taks f;
	std::thread my_thread(f);
	my_thread.join();
}

struct func {
	int& i;
	func(int& i_) :i(i_) {}
	void operator()() {
		for (unsigned j = 0; j < 10; j++) {
			std::cout << "执行任务..." << std::endl;
		}
	}
};

void opp() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	try
	{
		std::cout << "主现场的任务" << std::endl;
	}
	catch (const std::exception&)
	{
		my_thread.join();
		throw;
	}
	my_thread.join();
}

class thread_guard {
	std::thread& t;
public:
	explicit thread_guard(std::thread & t_):t(t_){}
	~thread_guard() {
		if (t.joinable()) {
			t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;

};


void sort01(int* a, int length) {
	int N = length;
	for (int i = 0; i < N; i++) {
		int min = i;
		for (int j = i + 1; j < N; j++) {
			if (a[j] < a[min]) {
				min = j;
				std::swap(a[i], a[min]);

			}
		}
	}
}


void testsort01() {
	int a[] = { 3, 4, 1, 9, 0, 8 };
	sort01(a, 6);
	for (int i = 0; i < 6; i++) {
		std::cout << a[i] << " ";
	}
}

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int v) :val(v), next{ nullptr }{}
};


struct Node {
	int data;
	Node* next;
	Node(int d) : data{ d }, next{ nullptr }{}
};

void insert(ListNode*& head, int v) {
	// 首先创建一个新的节点
	ListNode* newNode = new ListNode(v);
	
	// 如果是个空的列表，就让首节点等于刚刚创建的节点
	if (head == nullptr) {
		head = newNode;
	}
	// 否则：插入在最后一个节点后面
	// 1. 首先要找到最后一个节点
	// 2. 插入到最后一个节点后面
	else {
		ListNode* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
}


void iteraterList(ListNode* head) {
	while (head) {
		std::cout << head->val << "-->";
		head = head->next;
	}
	std::cout << "NULL" << std::endl;
}



void insert(Node*& head, int data) {
	// 首先判断头是不是空指针，如果是空的就说明是个空的链表
	if (head == nullptr) {
		head = new Node(data);
	}

	// 否则，从头找到尾，然后插入这个新的值
	Node* temp = head; 
	// 说明后面有值
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = new Node(data);

}

void printList(Node* head) {
	while (head) {
		std::cout << head->data << "-->";
		head = head->next;
	}
	std::cout << "null" << std::endl;
}

ListNode* nthToLastNode(ListNode* head, int n)
{
	// find N'th node from end
	ListNode* ptr1 = head;
	ListNode* ptr2 = head;

	int i = 1;
	while (ptr1 && i <= n) {
		ptr1 = ptr1->next;
		++i;
	}
	return ptr1;
	//while (ptr1) {
	//	ptr1 = ptr1->next;
	//	ptr2 = ptr2->next;
	//}
	//return ptr2;
}




void swapSpecial(Node*& head, int x, int y) {
	if (head == nullptr) { return; }
	if (x == y) { return; }

	Node* prev_x = nullptr;
	Node* prev_y = nullptr;

	Node* curr_x = head;
	Node* curr_y = head;

	// 查找 x 和 y 所在的位置
	while (curr_x && curr_x->data != x) {
		prev_x = curr_x;
		curr_x = curr_x->next;
	}
	while (curr_y && curr_y->data != y) {
		prev_y = curr_y;
		curr_y = curr_y->next;
	}

	// 如果没有找到
	if (curr_x == nullptr || curr_y == nullptr) {
		return;
	}

	// 如果找到了
	// 1. 如果 x 在头
	if (prev_x == nullptr) {
		head = curr_y;
	}
	// 2. 如果 x 在中间
	else {
		prev_x->next = curr_y;
	}

	if (prev_y == nullptr) {
		head = curr_x;
	}
	else {
		prev_y->next = curr_x;
	}


	// 交换尾
	Node* temp = curr_y->next;
	curr_y->next = curr_x->next;
	curr_x->next = temp;


}



void push(Node*& head, int data) {
	Node* newNode = new Node(data);
	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		curr->next = newNode;
	}
}

void reverseIter(Node*& head) {
	// 如果只有一个节点，就直接返回，不需要反转
	if (head == nullptr || (head != nullptr && head->next == nullptr)) {
		return;
	}

	Node* newHead = nullptr;
	Node* curr = head;
	Node* prev = nullptr;

	while (curr != nullptr) {
		prev = curr;
		curr = curr->next;

		prev->next = newHead;
		newHead = prev;
	}
	head = newHead;
}

void reverseRecur(Node*& head) {
	if (head == nullptr || (head != nullptr && head->next == nullptr)) {
		return;
	}
	Node* first = head;
	Node* rest = head->next;
	reverseRecur(rest);
	first->next->next = first;
	first->next = nullptr;
	head = rest;
}

void deleteNode(Node* node) {
	if (node == nullptr) {
		return;
	}
	
	if (node->next == nullptr) {
		return;
	}

	Node* nextNode = node->next;
	node->data = nextNode->data;
	node->next = nextNode->next;
	delete nextNode;
}


void deleteList(Node*& head) {
	while (head) {
		Node* nextNode = head->next;
		delete(head);
		head = nextNode;
	}
}


Node* middleNode(Node*& head) {
	Node* fastPtr = head;
	Node* slowPtr = head;
	while (fastPtr != nullptr && fastPtr->next != nullptr) {
		slowPtr = slowPtr->next;
		fastPtr = fastPtr->next->next;
	}
	return slowPtr;
}

int main() {
	Node* head = nullptr;
	insert(head, 1);
	insert(head, 2);
	insert(head, 3);
	insert(head, 4);
	insert(head, 5);
	printList(head);
	std::cout << "Middle node is : ";
	Node* mid = middleNode(head);
	std::cout << mid->data << std::endl;
	return 0;
}