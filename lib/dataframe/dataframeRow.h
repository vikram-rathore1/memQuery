//
// Created by Vikram Singh Rathore
//

#ifndef __DFROW_H_INCLUDED__
#define __DFROW_H_INCLUDED__

class DataframeRow;

#include <bits/stdc++.h>
#include "../commons.h"
using namespace std;

class DataframeRow {

    unordered_map<string, string> _rowMap;

    public:
        DataframeRow * set(string, string);
        string get(string);
        void print();

};

DataframeRow * DataframeRow::set(string key, string val) {
    _rowMap[to_lower(key)] = val;
    return this;
}

string DataframeRow::get(string key) {
    key = to_lower(key);
    if (_rowMap.find(key) != _rowMap.end()) return _rowMap[key];
    return NULL;
}

void DataframeRow::print() {
    cout << "{\n";
    for (unordered_map<string, string>::iterator it = _rowMap.begin(); it != _rowMap.end(); it++)
        cout << "    " << it -> first << ": " << it -> second << "\n";
    cout << "}\n";
}

#endif