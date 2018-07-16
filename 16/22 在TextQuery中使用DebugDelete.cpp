#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include<fstream>
using std::ifstream;
#include<string>
using std::string;
#include<sstream>
using std::istringstream;
#include<vector>
using std::vector;
#include<map>
using std::map;
#include<set>
using std::set;
#include<memory>
using std::shared_ptr;

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

class QueryResult;
class TextQuery {
public:
	using line_no = vector<string>::size_type;
	TextQuery(std::istream &);
	QueryResult query(const string&) const;
private:
	shared_ptr<vector<string>> file;
	map<string, shared_ptr<set<line_no>>> wm;
};


TextQuery::TextQuery(std::istream &is) :file(new vector<string>, DebugDelete()) {
	string text;
	while (std::getline(is, text)) {
		file->push_back(text);
		int n = file->size() - 1;
		string word;
		istringstream line(text);
		while (line >> word) {
			if (!wm[word]) wm[word].reset(new set<line_no>);
			wm[word]->insert(n);
		}
	}
}

class QueryResult {
	using line_no = vector<string>::size_type;
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f) :sought(s), lines(p), file(f) {};
private:
	string sought;
	shared_ptr<set<line_no>> lines;
	shared_ptr<vector<string>> file;
};

QueryResult TextQuery::query(const string &sought) const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end()) {
		return QueryResult(sought, nodata, file);
	}
	else return QueryResult(sought, loc->second, file);
}

std::ostream& print(std::ostream& os, const QueryResult &qr) {
	auto linesBegin = qr.lines->begin();
	os << "一共出现在了" << qr.lines->size() << "行中。" << endl;
	while (linesBegin != qr.lines->end()) {
		os << "(line " << *linesBegin << ") " << qr.file->at(*linesBegin) << endl;
		linesBegin++;
	}
	return os;
}

void runQueries(ifstream &infile) {
	TextQuery tq(infile);
	while (true) {
		cout << "输入需要查询的单词，或输入q退出：";
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;

	}
}

int main() {
	ifstream infile("what faith can do");
	runQueries(infile);
	system("pause");
	return 0;
}