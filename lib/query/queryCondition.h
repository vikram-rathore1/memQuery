//
// Created by Vikram Singh Rathore
//

#ifndef __QCONDTN_H_INCLUDED__
#define __QCONDTN_H_INCLUDED__

enum QueryConditionOperator {EQUALS, AND, OR};
enum QueryConditionType {FIELD, BOOLEAN, NESTED};
class QueryCondition;

template<typename ...Conditions>
QueryCondition * condition(Conditions...);
QueryCondition * And();

#include <bits/stdc++.h>
#include "../dataframe/dataframeRow.h"
using namespace std;

class QueryCondition {

    string field;
    string value;
    QueryConditionOperator condOperator;
    vector<QueryCondition*> children;

    public:
        QueryCondition() {}
        QueryCondition(QueryConditionOperator qco) : condOperator(qco) {}
        QueryCondition(string fl, QueryConditionOperator cond, string val) : field(fl), condOperator(cond), value(val) {}
        QueryCondition(vector<QueryCondition*> chld) : children(chld) {}
        void addChild(QueryCondition* qc) { children.push_back(qc); }
        QueryConditionType getType() {
            if (field.length()) return FIELD;
            if (children.size()) return NESTED;
            return BOOLEAN;
        }
        bool evaluateRow(DataframeRow * row) {
            if (children.size()) {

                bool ans = true;
                for (int i = 0; i < children.size(); i++) {
                    QueryConditionType qt = children[i] -> getType();
                    QueryCondition * boolean = NULL;

                    if (qt == BOOLEAN) {
                        boolean = children[i];
                    }
                    else {
                        if (boolean) {
                            ans = boolean -> evaluateBoolean(ans, children[i] -> evaluateRow(row));
                            boolean = NULL;
                        }
                        else ans &= children[i] -> evaluateRow(row);
                    }
                }
                return ans;

            }
            string fieldVal = row -> get(field);
            // todo: allow checking field equal to null
            // todo: switch case for various other operators
            return fieldVal == value;
        }
        bool evaluateBoolean(bool prev, bool next) {
            if (condOperator == AND) return prev && next;
            return prev || next;
        }
        void print() {
            cout << "QueryCondition: {field: " << field << ", value: " << value << ", condOperator: " << condOperator << ", children: [";
            if (children.size()) cout << "\n";
            for (int i = 0; i < children.size(); i++) {
                children[i] -> print();
            }
            cout << "]}\n";
        }

};

template<typename ...Conditions>
QueryCondition * condition(Conditions... conditions) {
    vector<QueryCondition*> chld = {conditions...};
    return new QueryCondition(chld);
}

QueryCondition * And() {
    return new QueryCondition(AND);
}

#endif