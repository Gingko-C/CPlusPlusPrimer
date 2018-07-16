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

class DebugDelete {
public:
	DebugDelete(std::ostream &s = std::cerr) :os(s) {}
	template <typename T> void operator()(T* p) const {
		os << "deleting unique_ptr" << endl;
		delete p;
	}
private:
	std::ostream &os;
};

int main() {
	DebugDelete d;
	double *p = new double;
	d(p);
	system("pause");
	return 0;
}
