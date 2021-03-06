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
#include <functional>
#include <map>

class Quote {
public:
	Quote() = default;
	Quote(const string &book, double sales_price) :bookNo(book), price(sales_price) {}
	string isbn() const { return bookNo; }
	virtual double net_price(size_t n) const { return n * price; }
	virtual ~Quote() = default;
private:
	string bookNo;
protected:
	double price = 0.0;
};

class Bulk_quote :public Quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const string&,double, size_t, double);
	double net_price(size_t) const;
private:
	size_t min_qty = 0;
	double discount = 0.0;
};

Bulk_quote::Bulk_quote(const string &book, double sales_price, size_t n, double disc_price)
	:Quote(book,sales_price),min_qty(n),discount(disc_price){}

double Bulk_quote::net_price(size_t n) const {
	if (n > min_qty)
		return n * (1 - discount)*price;
	else
		return n * price;
}

double print_total(std::ostream &os, const Quote &item, const size_t n) {
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

int main() {
	Quote q("bbb", 3);
	Bulk_quote quote("aaa", 3, 6, 0.5);
	print_total(cout, q, 7);
	print_total(cout, quote, 7);
	system("pause");
	return 0;
}