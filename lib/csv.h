//
// Created by Vikram Singh Rathore
//

#ifndef __CSV_H_INCLUDED__
#define __CSV_H_INCLUDED__

class Csv;

#include <bits/stdc++.h>
using namespace std;

class Csv {

    vector<string> _headers;
    vector< vector<string> > _rows;
    static vector<string> _splitRow(string, char);

    public:
        Csv(string, char);
        vector<string> getRowByIndex(unsigned int);
        vector<string> getHeaders();
        unsigned int size();

};

vector<string> Csv::_splitRow(string rowString, char delimiter) {
    vector<string> row;
    string cur = "";
    bool quotes = false;

    for (int i = 0; i < rowString.length(); i++) {

        if (rowString[i] == delimiter) {
            if (quotes)
                cur += rowString[i];
            else {
                row.push_back(cur);
                cur = "";
            }
        }
        else if (rowString[i] == '"') quotes = !quotes;
        else cur += rowString[i];

    }
    row.push_back(cur);

    return row;
}

Csv::Csv(string filePath, char delimiter) {
    ifstream input(filePath);

    for (string line; getline(input, line);) {
        vector<string> row = _splitRow(line, delimiter);

        if (!_headers.size())
            _headers = row;
        else
            _rows.push_back(row);
    }
}

vector<string> Csv::getRowByIndex(unsigned int index) {
    vector<string> emptyRow;

    if (index < _rows.size())
        return _rows[index];

    return emptyRow;
}

unsigned int Csv::size() { return _rows.size(); }

vector<string> Csv::getHeaders() { return _headers; }

#endif