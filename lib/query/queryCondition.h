//
// Created by Vikram Singh Rathore
//

#ifndef __QCONDTN_H_INCLUDED__
#define __QCONDTN_H_INCLUDED__

enum QueryConditionOperator {EQUALS, AND, OR};
enum QueryConditionType {FIELD, BOOLEAN, NESTED};
class QueryCondition;

#include <bits/stdc++.h>
#include "../dataframe/dataframeRow.h"
using namespace std;

class QueryCondition {

    string field;
    string value;
    QueryConditionOperator condOperator;
    vector<QueryCondition*> children;

    public:
        QueryCondition(QueryConditionOperator qco) : condOperator(qco) {}
        QueryCondition(string fl, QueryConditionOperator cond, string val) : field(fl), condOperator(cond), value(val) {}
        QueryCondition(vector<QueryCondition*> chld) : children(chld) {}
        QueryConditionType getType();
        bool evaluateRow(DataframeRow*);
        bool evaluateBoolean(bool, bool);
        void print();

};

QueryConditionType QueryCondition::getType() {
    if (field.length()) return FIELD;
    if (children.size()) return NESTED;
    return BOOLEAN;
}

bool QueryCondition::evaluateRow(DataframeRow * row) {
    if (children.size()) {
        bool ans = true;
        QueryCondition * boolean = NULL;

        for (QueryCondition* child: children) {
            if (child -> getType() == BOOLEAN)
                boolean = children[i];
            else {
                if (boolean) {
                    ans = boolean -> evaluateBoolean(ans, child -> evaluateRow(row));
                    boolean = NULL;
                }
                else ans &= child -> evaluateRow(row);
            }
        }
        return ans;

    }
    string fieldVal = row -> get(field);
    // todo: allow checking field equal to null
    // todo: switch case for various other operators
    return fieldVal == value;
}

bool QueryCondition::evaluateBoolean(bool prev, bool next) {
    if (condOperator == AND) return prev && next;
    return prev || next;
}

void QueryCondition::print() {
    cout << "QueryCondition: {field: " << field << ", value: " << value << ", condOperator: " << condOperator << ", children: [";
    if (children.size()) cout << "\n";
    for (int i = 0; i < children.size(); i++) {
        children[i] -> print();
    }
    cout << "]}\n";
}

#endif