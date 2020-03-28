//
// Created by Vikram Singh Rathore
//

#ifndef __DFSF_H_INCLUDED__
#define __DFSF_H_INCLUDED__

class DataframeSchemaField;

#include <bits/stdc++.h>
#include "../commons.h"
using namespace std;

class DataframeSchemaField {

    string _name;
    Datatype _type;
    int _length;
    bool _nullable;

    static string dataTypeToString(Datatype t) {
        switch (t) {
            case INT:      return "Int";
            case LONG:     return "Long";
            case LONGLONG: return "LongLong";
            case STRING:   return "String";
            case FLOAT:    return "Float";
            case DOUBLE:   return "Double";
            case CSV:      return "Csv";
            default:       return "";
        }
    }

public:
    DataframeSchemaField(string name, Datatype type, int length) : _name(name), _type(type), _length(length) {}
    DataframeSchemaField(string name, Datatype type) : _name(name), _type(type) {}
    string type() { return dataTypeToString(_type); }
    string name() { return _name; }

};

#endif