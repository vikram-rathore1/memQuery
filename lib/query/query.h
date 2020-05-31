//
// Created by Vikram Singh Rathore
//

#ifndef __QUERY_H_INCLUDED__
#define __QUERY_H_INCLUDED__

class Query;

#include <bits/stdc++.h>
#include "../dataframe/dataframe.h"
#include "queryCondition.h"
#include "queryView.h"
#include "queryField.h"
using namespace std;

class Query {

    vector<QueryField*> _select;
    QueryCondition* _where;
    bool _select_all;
    QueryView * _from;
    int _limit;

    public:

        Query() {
            _limit = -1;
            _select_all = false;
            _where = NULL;
        }

        template <typename T>
        Query * select(T t) {
            _select.push_back(t);
            if (t -> name() == "*") _select_all = true;
            return this;
        }
        template<typename T, typename... Args>
        Query * select(T t, Args... args) {
            select(t);
            return select(args...);
        }
        Query * from(QueryView * qv) {
            // todo: make sure select is done
            _from = qv;
            return this;
        }
        Query * limit(int lim) {
            // todo: check ordering
            _limit = lim;
            return this;
        }
        Dataframe * getDataframe() {
            int rowsToFetch = (_limit == -1) ? _from -> dataframe() -> size() : min(_limit, _from -> dataframe() -> size());
            Dataframe * df = new Dataframe();

            vector<string> requiredFields;
            if (!_select_all) {
                for (int i = 0; i < _select.size(); i++) requiredFields.push_back(_select[i] -> name());
            }

            DataframeRow *dfr_raw = _from -> dataframe() -> getHead();
            while (dfr_raw && df -> size() < rowsToFetch) {
                DataframeRow * dfr = (_select_all) ? dfr_raw : dfr_raw -> getRowWithFields(requiredFields);

                if (!_where || _where -> evaluateRow(dfr_raw))
                    df -> addRow(dfr);

                dfr_raw = dfr_raw -> getNext();
            }

            return df;
        }
        Query * where(QueryCondition * qc) {
            _where = qc;
            return this;
        }

        void print() {
            cout << "Query {\n";
            cout << "select: \n";
            for (int i = 0; i < _select.size(); i++) _select[i] -> print();
            cout << "from: \n";
            _from -> print();
            cout << "limit: " << _limit << "\n";
            cout << "where: ";
            _where -> print();
            cout << "}\n";
        }

};

#endif