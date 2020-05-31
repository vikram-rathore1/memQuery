//
// Created by Vikram Singh Rathore
//

#ifndef __DATAFRAME_H_INCLUDED__
#define __DATAFRAME_H_INCLUDED__

class Dataframe;

#include <bits/stdc++.h>
#include "../commons.h"
#include "../csv.h"
#include "dataframeRow.h"
#include "dataframeSchemaField.h"
using namespace std;

class Dataframe {

    unordered_map<string, DataframeSchemaField*> _schema;
    vector<DataframeRow*> _rows;

    public:
        Dataframe * addRow(DataframeRow*);
        Dataframe * loadCsv(Csv*);
        unordered_map<string, DataframeSchemaField*> getSchema();
        DataframeRow * getRowByIndex(int);
        DataframeRow * getRowFieldsByIndex(int, vector<string>);
        int size();
        void printSchema();
        void printRow(int);
        void show(int);
        void show();
};

Dataframe * Dataframe::addRow(DataframeRow *row) {
    _rows.push_back(row);
    return this;
}

Dataframe * Dataframe::loadCsv(Csv * csv) {
    _schema.clear();
    _rows.clear();

    vector<string> headers = csv -> getHeaders();
    for (int i = 0; i < headers.size(); i++) {
        // todo: auto schema detection, if chosen
        DataframeSchemaField * sf = new DataframeSchemaField(headers[i], STRING);
        sf -> length(50);
        _schema[to_lower(headers[i])] = sf;
    }

    for (int i = 0; i < csv -> size(); i++) {
        vector<string> row = csv->getRowByIndex(i);
        DataframeRow * dfr = new DataframeRow();

        for (int j = 0; j < headers.size(); j++)
            dfr -> set(headers[j], row[j]);

        _rows.push_back(dfr);
    }
    return this;
}

void Dataframe::printSchema() {
    cout << "{\n";
    for (unordered_map<string, DataframeSchemaField*>::iterator it = _schema.begin(); it != _schema.end(); it++) {
        cout << "\t" << it -> second -> name() << ": " << it -> second -> type() << "\n";
    }
    cout << "}\n";
}

unordered_map<string, DataframeSchemaField*> Dataframe::getSchema() { return _schema; }

void Dataframe::printRow(int index) {
    if (_rows.size() > index) _rows[index] -> print();
}

void Dataframe::show(int n) {
    n = min(n, (int)_rows.size());
    for (int i = 0; i < n; i++) {
        _rows[i] -> print();
    }
    cout << "Showing " << n << " out of " << _rows.size() << " _rows\n";
}

void Dataframe::show() {
    show(10);
}

int Dataframe::size() {
    return _rows.size();
}

DataframeRow * Dataframe::getRowByIndex(int index) {
    if (index >= _rows.size()) return NULL;
    DataframeRow * dfr = new DataframeRow();

    for (unordered_map<string, DataframeSchemaField*>::iterator it = _schema.begin(); it != _schema.end(); it++) {
        // todo: casting row according to schema
        dfr -> set(it -> second -> name(), _rows[index] -> get(it -> first));
    }

    return dfr;
}

DataframeRow * Dataframe::getRowFieldsByIndex(int index, vector<string> fields) {
    if (index >= _rows.size()) return NULL;
    DataframeRow * dfr = new DataframeRow();

    for (int i = 0; i < fields.size(); i++) {
        // todo: casting row according to schema
        string field = to_lower(fields[i]);
        if (_schema.find(field) != _schema.end()) dfr -> set(fields[i], _rows[index] -> get(field));
        else dfr -> set(field, NULL);
    }

    return dfr;
}


#endif