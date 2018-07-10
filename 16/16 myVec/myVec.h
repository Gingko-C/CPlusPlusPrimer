#pragma once
#ifndef MYVEC_H
#define MYVEC_H
#include <utility>
#include <memory>
using std::uninitialized_copy;
using std::allocator;
#include <algorithm>

template <typename T> class myVec {
public:
	myVec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	myVec(std::initializer_list<T>);
	myVec(const myVec&);
	myVec(myVec&&) noexcept;
	myVec &operator=(const myVec&);
	myVec &operator=(myVec&&) noexcept;
	~myVec() { free(); }
	void push_back(const T&);
	void reserve(size_t);
	void resize(size_t, const T&);
	T& at(size_t n) { return *(elements + n); }
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	T *begin() const { return elements; }
	T *end() const { return first_free; }
private:
	static allocator<T> alloc;
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	std::pair<T*, T*> alloc_n_copy(const T*, const T*);
	void free();
	void reallocate();
	void reallocate_n(size_t);
	T *elements;//首指针
	T *first_free;//指向最后一个实际元素之后
	T *cap;//指向分配内存尾后位置
};
template <typename T>
myVec<T>::myVec(std::initializer_list<T>li) {
	auto newdata = alloc_n_copy(li.begin(), li.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

template <typename T>
myVec<T>::myVec(const myVec &sv) {
	auto newdata = alloc_n_copy(sv.begin(), sv.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

template <typename T>
myVec<T>::myVec(myVec &&sv) noexcept
	:elements(sv.elements), first_free(sv.first_free), cap(sv.cap) {
	sv.elements = sv.first_free = sv.cap = nullptr;
}

template <typename T>
myVec<T> &myVec<T>::operator=(const myVec &rhs) {
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}

template <typename T>
myVec<T>& myVec<T>::operator=(myVec &&rhs) noexcept {
	if (this != &rhs) {
		free();
		elements = std::move(rhs.elements);
		first_free = std::move(rhs.first_free);
		cap = std::move(rhs.cap);
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

template <typename T>
void myVec<T>::push_back(const T &s) {
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

template <typename T>
void myVec<T>::reserve(size_t n) {
	if (n > capacity())
		reallocate_n(n);
}

template <typename T>
void myVec<T>::resize(size_t n, const T& s) {
	while (n > size())
		push_back(s);
	while (n < size())
		alloc.destroy(--first_free);
}

template <typename T>
std::pair<T*, T*> myVec<T>::alloc_n_copy(const T *b, const T *e) {
	auto data = alloc.allocate(e - b);
	return { data, std::uninitialized_copy(b, e, data) };
}

template <typename T>
void myVec<T>::free() {
	if (elements) {
		std::for_each(elements, first_free, [](T p) {alloc.destroy(&p);});
		alloc.deallocate(elements, cap - elements);
	}
}

template <typename T>
void myVec<T>::reallocate() {
	auto newcapacity = size() ? size() * 2 : 1;
	reallocate_n(newcapacity);
}

template <typename T>
void myVec<T>::reallocate_n(size_t n) {
	auto newdata = alloc.allocate(n);
	auto elem = elements;
	auto dest = newdata;
	for (size_t i = 0;i != size();i++)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + n;
}

template <typename T>
allocator<T> myVec<T>::alloc{};//static成员使用需要定义

#endif // !STRVEC_H
