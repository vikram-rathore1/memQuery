//
// Created by Vikram Singh Rathore
//

#include<bits/stdc++.h>
using namespace std;


// class ICell {
//   // list of cell methods
// };

// template <class T>
// class Cell : public ICell {
//   T data;
//   // implementation of cell methods
// };

// class Row {
//   vector <ICell *> cells;
// };



// struct cell {

// public:
	
// 	template<typename T> void setValue(T value) {
// 		_value = value;
// 	}
	
// 	T value() {
// 		return _value;
// 	}

// private:
// 	T _value;

// };

vector<string> splitRow(string str, char ch) {
	vector<string> ans;
	string cur = "";
	bool quotes = false;

	for (int i = 0; i < str.length(); i++) {

		if (str[i] == ch) {
			if (quotes) cur += str[i];
			else {
				ans.push_back(cur);
				cur = "";
			}
		}
		else if (str[i] == '"') quotes = !quotes;
		else cur += str[i];

	}
	ans.push_back(cur);

	return ans;
}

vector<vector<string> > filter(vector< vector<string> > &data) {
	vector<vector<string> > ans;
	for (int i = 0; i < data.size(); i++) {
		if (data[i][16] == "1995") ans.push_back(data[i]);
	}
	return ans;
}

int main() {
	timespec ts_beg, ts_end;


    ifstream input("imdb.csv");
    int count = 0;

    vector<string> headers;
    vector<vector<string> > rows;
    
    for( std::string line; getline( input, line ); ) {
		if (!count) headers = splitRow(line, ',');
    	else rows.push_back(splitRow(line, ','));
	    count++;
	}


	for (int i = 0; i < rows[1].size(); i++) {
		cout << rows[1][i] << "\n\n";
	}

	// cout << "Headers are: \n";
	// for (int i = 0; i < headers.size(); i++) cout << headers[i] << "\n";

	// cout << "\n\nRows are: \n";
	// for (int j = 0; j < 10; j++) {
	// 	for (int i = 0; i < rows[j].size(); i++) {
	// 		cout << rows[j][i] << "\n";
	// 	}
	// 	cout << "\n\n";
	// }

	// clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);
	// vector< vector<string> > ans = filter(rows);
	// clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
	// cout << (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9 << " sec\n\n";

	// cout << "Count: " << ans.size() << " / " << rows.size() << "\n";

	// cell c;
	// vector<cell> v;
	// v.push_back(c);
	// cout << "value is: " << c.value();

    return 0;
}