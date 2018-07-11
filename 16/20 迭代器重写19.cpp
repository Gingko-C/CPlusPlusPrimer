#define _SCL_SECURE_NO_WARNINGS
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

template <typename T> void myprint(T &v) {
	for (auto b = v.begin();b != v.end();b++) {
		cout << *b << " ";
	}
}

int main() {
	vector<int> v{ 1,2,3,4,5 };
	myprint(v);
	system("pause");
	return 0;
}
