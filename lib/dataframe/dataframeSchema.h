//
// Created by Vikram Singh Rathore
//

#ifndef __DFSCHEMA_H_INCLUDED__
#define __DFSCHEMA_H_INCLUDED__

class DataframeSchemaField;
class DataframeSchema;

#include <bits/stdc++.h>
#include "dataframeSchemaField.h"
using namespace std;

class DataframeSchema {

    unordered_map<string, DataframeSchemaField*> _fields;

    public:
        template<typename ...SchemaFields>
        DataframeSchema(SchemaFields...);

};

template<typename ...SchemaFields>
DataframeSchema::DataframeSchema(SchemaFields... schemaFields) {
//    vector<DataframeSchemaField*>
}

#endif