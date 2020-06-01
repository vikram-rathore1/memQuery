//
// Created by Vikram Singh Rathore
//

#ifndef __QFIELD_H_INCLUDED__
#define __QFIELD_H_INCLUDED__

#include <bits/stdc++.h>
#include "queryCondition.h"
using namespace std;

class QueryField;

class QueryField {

    string _name;
    string _as;

    public:
        QueryField(string name) : _name(name) {}
        QueryField * as(string);
        string name();
        QueryCondition * Equals(string);
        void print();

};

QueryField * QueryField::as(string alias) {
    _as = alias;
    return this;
}

string QueryField::name() {
    return _name;
}

QueryCondition * QueryField::Equals(string val) {
    return new QueryCondition(_name, EQUALS, val);
}

void QueryField::print() {
    cout << "QueryField {" << "name: " << _name << ", as: " << _as << "}\n";
}

#endif