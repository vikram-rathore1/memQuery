//=================================
// include guard
//#ifndef __CSV_H_INCLUDED__
//#define __CSV_H_INCLUDED__
//
////=================================
//// forward declared dependencies
//class Csv;
//
////=================================
//// included dependencies
//#include <bits/stdc++.h>
//using namespace std;
//
////=================================
//
//class Csv {
//
//    vector<string> _headers;
//    vector< vector<string> > _rows;
//    int
//
//};

vector<string> splitRow(string str, char ch) {
	vector<string> ans;
	string cur = "";
	bool quotes = false;

	for (int i = 0; i < str.length(); i++) {

		if (str[i] == ch) {
			if (quotes) cur += str[i];
			else {
				ans.push_back(cur);
				// cout << "Pushed " << cur << ", ";
				cur = "";
			}
		}
		else if (str[i] == '"') quotes = !quotes;
		else cur += str[i];

	}
	ans.push_back(cur);
	// cout << "Pushed " << cur << ", ";

	return ans;
}

//#endif // __CSV_H_INCLUDED__