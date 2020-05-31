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

    unordered_map<string, string> _document;
    DataframeRow *_next, *_prev;

    public:
        // todo: set Id (string) for internal reference
        // todo: clone function? to return copy of this while generating result dataset?
        DataframeRow();
        void set(string, string);
        string get(string);
        void setNext(DataframeRow*);
        DataframeRow * getNext();
        void setPrev(DataframeRow*);
        DataframeRow * getPrev();
        void setId(string);
        string getId();
        DataframeRow * getRowWithFields(vector<string>);
        void print();

};

DataframeRow::DataframeRow() {
    _next = _prev = NULL;
}

void DataframeRow::set(string key, string val) {
    _document[to_lower(key)] = val;
}

string DataframeRow::get(string key) {
    key = to_lower(key);
    if (_document.find(key) != _document.end()) return _document[key];
    return "";
}

void DataframeRow::setNext(DataframeRow *n) {
    _next = n;
}

DataframeRow * DataframeRow::getNext() {
    return _next;
}

void DataframeRow::setPrev(DataframeRow *p) {
    _prev = p;
}

DataframeRow * DataframeRow::getPrev() {
    return _prev;
}

DataframeRow * DataframeRow::getRowWithFields(vector<string> requiredFields) {
    DataframeRow * r = new DataframeRow();
    for (string field: requiredFields)
        r -> set(field, get(field));
    return r;
}

void DataframeRow::print() {
    cout << "{\n";
    for (unordered_map<string, string>::iterator it = _document.begin(); it != _document.end(); it++)
        cout << "    " << it -> first << ": " << it -> second << "\n";
    cout << "}\n";
}

#endif