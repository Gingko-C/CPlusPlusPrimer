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
#include "myVec.h"

int main() {
	myVec<string> ms {"aaa","bbb" };
	myVec<int> mi{ 1,2,3,4,5,6 };
	mi.push_back(7);
	for (auto i : mi) {
		cout << i << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}
