//
// Created by Vikram Singh Rathore
//

#ifndef __QVIEW_H_INCLUDED__
#define __QVIEW_H_INCLUDED__

#include <bits/stdc++.h>
#include "../dataframe/dataframe.h"
using namespace std;

class QueryView;
QueryView * view(Dataframe*);

class QueryView {

    Dataframe * _df;
    string _as;

    public:
        QueryView(Dataframe * df) : _df(df) {}
        QueryView * as(string alias) {
            _as = alias;
            return this;
        }
        Dataframe * dataframe() { return _df; }
        void print() {
            cout << "QueryView {as: " << _as << "}\n";
        }

};

QueryView * view(Dataframe * df) {
    return new QueryView(df);
}

#endif