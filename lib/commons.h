//
// Created by Vikram Singh Rathore
//

#ifndef __COMMONS_H_INCLUDED__
#define __COMMONS_H_INCLUDED__

using namespace std;

enum  Datatype {INT, LONG, LONGLONG, STRING, FLOAT, DOUBLE, CSV};

string to_lower(string s) {
    string ans = "";
    for (int i = 0; i < s.length(); i++) ans += tolower(s[i]);
    return ans;
}

#endif