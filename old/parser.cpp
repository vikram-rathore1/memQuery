//
// Created by Vikram Singh Rathore
//

#include<bits/stdc++.h>
using namespace std;

string sanitize(string dirty) {
	string clean = "";
	for (int i = 0; i < dirty.length(); i++) {
		if (dirty[i] == ',') clean += ", ";
		else if (isspace(dirty[i])) {
			if (clean.length() && !isspace(clean[clean.length() - 1]))
				clean += " ";
		}
		else clean += dirty[i];
	}
	return clean;
}

void process(string prev, string query) {

	if (prev == "") {

		

	}

}

// struct node {
// 	string token;
// 	unordered_map<>
// };

int main() {
	cout << sanitize("select  asd, sss,  lpo from		cloop()		\n");
}