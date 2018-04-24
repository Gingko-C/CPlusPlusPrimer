#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
struct Sales_data {
	//��Ԫ����
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::ostream &print(std::ostream&, const Sales_data&);
	friend std::istream &read(std::istream&, Sales_data&);
public:
	//���캯��
	Sales_data(const std::string &s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(n*p) { std::cout << "bur" << std::endl; }
	Sales_data() :Sales_data("", 0, 0) { std::cout << "000" << std::endl; } //Ĭ�Ϲ��캯��
	Sales_data(std::istream &is) :Sales_data() { read(is, *this); std::cout << "cin" << std::endl; }
	Sales_data(const std::string &s) :Sales_data(s, 0, 0) { std::cout << "b00" << std::endl; }

	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

//Sales_data �ӿڵķǳ�Ա��ɲ��ֵ�����
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);

inline double Sales_data::avg_price() const {
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

//1 IO�����ڲ��ܱ����������ͣ�ֻ��ͨ���������������� 2 print�������У�ִ���������ĺ���Ӧ�þ������ٶ��ڸ�ʽ�Ŀ���
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