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
    DataframeRow *_head, *_tail;
    int _totalRows;

    public:
        Dataframe();
        // todo: evaluate whether to return self pointer in these methods
        // todo: handle int vs unsigned int cases, e.g. param to show() function should be unsigned
        Dataframe * addRow(DataframeRow*);
        Dataframe * loadCsv(Csv*);
        unordered_map<string, DataframeSchemaField*> getSchema();
        DataframeRow * getHead();
        DataframeRow * getTail();
        int size();
        void printSchema();
        void show(int);
        void show();
};

Dataframe::Dataframe() {
    _head = _tail = NULL;
    _totalRows = 0;
}

Dataframe * Dataframe::addRow(DataframeRow *row) {
    if (!row) return NULL;
    _totalRows++;
    if (!_tail) {
        _head = _tail = row;
        return this;
    }
    _tail -> setNext(row);
    row -> setPrev(_tail);
    _tail = row;
    return this;
}

Dataframe * Dataframe::loadCsv(Csv * csv) {
    _schema.clear();

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

        addRow(dfr);
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

DataframeRow * Dataframe::getHead() {
    return _head;
}

DataframeRow * Dataframe::getTail() {
    return _tail;
}

void Dataframe::show(int n) {
    n = min(n, _totalRows);
    DataframeRow * ptr = _head;
    for (int i = 0; i < n && ptr; i++) {
        ptr -> print();
        ptr = ptr -> getNext();
    }
    cout << "Showing " << n << " out of " << _totalRows << " rows\n";
}

void Dataframe::show() {
    show(10);
}

int Dataframe::size() {
    return _totalRows;
}



#endif