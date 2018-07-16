#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <memory>
using std::shared_ptr;
using std::make_shared;

template <typename> class BlobPtr;
template <typename> class Blob;

template <typename T> class Blob {
	friend class BlobPtr<T>;
	template <typename T> friend bool operator==(const Blob<T>&, const Blob<T>&);
	template <typename T> friend bool operator!=(const Blob<T>&, const Blob<T>&);
	template <typename T> friend bool operator<(const Blob<T>&, const Blob<T>&);
public:
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;
	//构造函数
	Blob();
	Blob(std::initializer_list<T>);
	template <typename It> Blob(It b, It e);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const T &t) { data->push_back(t); }
	void push_back(T &&t) { data->push_back(std::move(t)); }
	void pop_back();
	T& back();
	T& operator[](size_type);
	const T& operator[](size_type) const;
	BlobPtr<T> begin();
	BlobPtr<T> end();
private:
	std::shared_ptr<std::vector<T>> data;
	void check(size_type i, const std::string &msg) const;
};

template <typename T>
template <typename It>
Blob<T>::Blob(It b, It e) :data(make_shared<vector<T>>(b, e)) {}

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const {
	if (i >= data->size())
		throw std::out_of_range(msg);
}

template <typename T>
T& Blob<T>::back() {
	check(0, "back on empty Blob");
	return data->back();
}

template <typename T>
T& Blob<T>::operator[](size_type i) {
	check(i, "subscript out of range");
	return data->operator[](i);
}

template <typename T>
const T& Blob<T>::operator[](size_type i) const {
	check(i, "subscript out of range");
	return data->operator[](i);
}

template <typename T>
void Blob<T>::pop_back() {
	check(0, "pop_back on empty Blob");
	data->pop_back;
}

template <typename T>
Blob<T>::Blob() :data(std::make_shared<std::vector<T>>()) {}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<vector<T>>(il)) {}

template <typename T>
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) {
	return *lhs.data == *rhs.data;
}

template <typename T>
bool operator!=(const Blob<T> &lhs, const Blob<T> &rhs) {
	return *lhs.data != *rhs.data;
}

template <typename T>
bool operator<(const Blob<T> &lhs, const Blob<T> &rhs) {
	return *lhs.data < *rhs.data;
}

template <typename T> class BlobPtr {
	template <typename T> friend bool operator==<T>(const BlobPtr<T>&, const BlobPtr<T>&);
	template <typename T> friend bool operator!=<T>(const BlobPtr<T>&, const BlobPtr<T>&);
	template <typename T> friend bool operator<(const BlobPtr<T>&, const BlobPtr<T>&);
public:
	BlobPtr() :curr(0) {}
	BlobPtr(Blob<T> &a, size_t sz = 0) :wptr(a.data), curr(sz) {}
	T& operator*() const {
		auto p = check(curr, "dereference past end");
		return p->operator[](curr);
	}
	T& operator[](const int n) { return (*wptr.lock())[n]; }
	const T& operator[](const int n) const { return (*wptr.lock())[n]; }
	BlobPtr& operator++();//在类代码内可以简化模板类名，等同于BlobPtr<T>& operator++();
	BlobPtr& operator--();
	BlobPtr& operator++(int);
	BlobPtr& operator--(int);
private:
	std::shared_ptr<std::vector<T>> check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<T>> wptr;
	std::size_t curr;
};

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t i, const std::string& msg) const {
	auto ret = wptr.lock();
	if (!ret) {
		throw std::runtime_error("unbound StrBlobPtr");
	}
	if (i >= ret->size() || i < 0) {
		throw std::out_of_range(msg);
	}
	return ret;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
	--curr;
	check(curr, "decrement past begin of StrBlobPtr");
	return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++(int) {
	BlobPtr ret = *this;
	++*this;
	return ret;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--(int) {
	BlobPtr ret = *this;
	--*this;
	return ret;
}

template <typename T>
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
	return lhs.curr == rhs.curr
		&& lhs.wptr.lock() == rhs.wptr.lock();
}

template <typename T>
bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
	return !(lhs == rhs);
}

template <typename T>
bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
	if (lhs.wptr.lock() != rhs.wptr.lock()) return false;
	return lhs.curr < rhs.curr;
}

template <typename T>
BlobPtr<T> Blob<T>::begin() {
	return BlobPtr<T>(*this);
}

template <typename T>
BlobPtr<T> Blob<T>::end() {
	return BlobPtr<T>(*this, data->size());
}

int main() {
	vector<int> vi{ 1,2,3,4,5,6,7 };
	Blob<int> a(vi.begin(), vi.end());
	Blob<string> b{ "aaaasdsdsafdsfdgghgfjh" };
	Blob<string> c{ "fdfgdjhsjdfhakhdfjsaf" };
	cout << (b < c) << endl;
	auto bb = a.begin();
	while (bb != a.end()) {
		cout << *bb << " ";
		bb++;
	}

	cout << endl;
	system("pause");
	return 0;
}
