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
    unsigned int _length;
    bool _nullable, _indexed;

    public:
        DataframeSchemaField(string, Datatype);
        DataframeSchemaField* length(unsigned int);
        DataframeSchemaField* nullable(bool);

        DataframeSchemaField* defaultValue(int);
        DataframeSchemaField* defaultValue(long);
        DataframeSchemaField* defaultValue(long long);
        DataframeSchemaField* defaultValue(string);
        DataframeSchemaField* defaultValue(float);
        DataframeSchemaField* defaultValue(double);

        DataframeSchemaField* ignoreInvalidTypeValues(double);

        string name();
        string type();

};

DataframeSchemaField::DataframeSchemaField(string name, Datatype type) : _name(name), _type(type) {}

string DataframeSchemaField::name() { return _name; }

string DataframeSchemaField::type() { return dataTypeToString(_type); }

DataframeSchemaField* DataframeSchemaField::length(unsigned int len) { _length = len; return this; }

#endif