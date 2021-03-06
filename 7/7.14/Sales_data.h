#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
struct Sales_data {
	friend std::istream &read(std::istream&, Sales_data&);
	//构造函数
	//Sales_data() = default;
	Sales_data();
	Sales_data(std::istream&);
	Sales_data(const std::string &s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(n*p) {}
	Sales_data(const std::string &s) :bookNo(s) {}

	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);

double Sales_data::avg_price() const {
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}

Sales_data& Sales_data::combine(const Sales_data &rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs;
	return sum.combine(rhs);
}

//构造函数
//7.14 用类内初始值显式的初始化成员
Sales_data::Sales_data() {
	this->bookNo = bookNo;
	this->units_sold = units_sold;
	this->revenue = revenue;
}
Sales_data::Sales_data(std::istream &is) {
	read(is, *this);
}

//1 IO类属于不能被拷贝的类型，只能通过引用来传递它们 2 print不负责换行，执行输出任务的函数应该尽量减少对于格式的控制
std::ostream &print(std::ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
	return os;
}

std::istream &read(std::istream &is, Sales_data &item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = item.units_sold*price;
	return is;
}
#endif