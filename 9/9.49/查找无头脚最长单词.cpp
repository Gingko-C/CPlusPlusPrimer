#include <string>
#include <algorithm>
using std::string;
#include <list>
using std::list;
#include <forward_list>
using std::forward_list;
#include <deque>
using std::deque;
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

vector<int> findLetter(string s) {
	string letter = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	vector<int> ltrpos;
	int pos = 0;
	while ((pos = s.find_first_of(letter, pos)) != string::npos) {
		ltrpos.push_back(pos);
		pos++;
	}
	return ltrpos;
}

vector<int> findLetter_2(string s) {
	string number = "1234567890";
	vector<int> ltrpos;
	int pos = 0;
	while ((pos = s.find_first_not_of(number, pos)) != string::npos) {
		ltrpos.push_back(pos);
		pos++;
	}
	return ltrpos;
}

vector<int> findNumber(string s) {
	string number = "1234567890";
	vector<int> numpos;
	int pos = 0;
	while ((pos = s.find_first_of(number, pos)) != string::npos) {
		numpos.push_back(pos);
		pos++;
	}
	return numpos;
}

vector<int> findNumber_2(string s) {
	string letter = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	vector<int> numpos;
	int pos = 0;
	while ((pos = s.find_first_not_of(letter, pos)) != string::npos) {
		numpos.push_back(pos);
		pos++;
	}
	return numpos;
}

string findLongestNoHeadOrFoot(std::istream& is) {
	string letterWithHF = "bdfghijklpqty";
	string word;
	string longestWithoutHF = "";
	while (is >> word) {
		if (word.find_first_of(letterWithHF) == string::npos && word.size() > longestWithoutHF.size()) {
			longestWithoutHF = word;
		}
	}
	return longestWithoutHF;
}

string findLongestNoHeadOrFootMinGW(std::istream& is) {
    string letterWithHF = "bdfghijklpqty";
    string word;
    is >> word;
    int pos = 0;
    vector<int> vecpos;
    while((pos = word.find_first_not_of(letterWithHF, pos)) != string::npos){
        vecpos.push_back(pos);
        pos++;
    }

    vector<pair<int, int>> lenIndex;
    int len = 0;
    for (int i = 0; i < vecpos.size() - 1; i++) {
        if(vecpos[i] + 1 == vecpos[i + 1]){
            len += 1;
            lenIndex.push_back(make_pair(len, vecpos[i]));
            if(i == vecpos.size() - 2){
                len += 1;
                lenIndex.push_back(make_pair(len, vecpos[i + 1]));
            }
        }else{
            len = 0;
        }
    }

    sort(lenIndex.begin(), lenIndex.end());
    len = lenIndex[lenIndex.size() - 1].first;
    return word.substr(lenIndex[lenIndex.size() - 1].second - len + 1, len);
}

int main() {
	string res = findLongestNoHeadOrFoot(cin);
	cout << res << endl;
	system("pause");
	return 0;
}
