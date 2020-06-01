//
// Created by Vikram Singh Rathore
//

#ifndef __GENERATOR_H_INCLUDED__
#define __GENERATOR_H_INCLUDED__

#include <bits/stdc++.h>
#include "./query/queryCondition.h"
#include "./query/queryField.h"
using namespace std;

template<typename ...Conditions>
QueryCondition * condition(Conditions... conditions) {
    vector<QueryCondition*> chld = {conditions...};
    return new QueryCondition(chld);
}

QueryCondition * And() {
    return new QueryCondition(AND);
}

QueryCondition * Or() {
    return new QueryCondition(OR);
}

QueryField * field(string name) {
    return new QueryField(name);
}

#endif