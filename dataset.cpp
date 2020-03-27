//
// Created by Vikram Singh Rathore
//

#include<bits/stdc++.h>
#include "util/csv.h"
#include "util/util.h"
using namespace std;

class DataframeRow {

	unordered_map<string, string> rowMap;

    public:

        DataframeRow * set(string key, string val) {
            rowMap[to_lower(key)] = val;
            return this;
        }

        string get(string key) {
            key = to_lower(key);
            if (rowMap.find(key) != rowMap.end()) return rowMap[key];
            return NULL;
        }

        void print() {
            cout << "{\n";
            for (unordered_map<string, string>::iterator it = rowMap.begin(); it != rowMap.end(); it++) {
                cout << "    " << it -> first << ": " << it -> second << "\n";
            }
            cout << "}\n";
        }

};

enum  DataframeDatatype {Int, Long, LongLong, String, Float, Double, Csv};
class DataframeSchemaField {

    string _name;
	DataframeDatatype _type;
	int _length;
	bool _nullable;

    inline const string dataTypeToString(DataframeDatatype t) {
        switch (t) {
            case Int:      return "Int";
            case Long:     return "Long";
            case LongLong: return "LongLong";
            case String:   return "String";
            case Float:    return "Float";
            case Double:   return "Double";
            case Csv:      return "Csv";
            default:       return "";
        }
    }

    public:
        DataframeSchemaField(string name, DataframeDatatype type, int length) : _name(name), _type(type), _length(length) {}
        DataframeSchemaField(string name, DataframeDatatype type) : _name(name), _type(type) {}
        string type() { return dataTypeToString(_type); }
        string name() { return _name; }

};

class Dataframe {

	unordered_map<string, DataframeSchemaField*> schema;
	vector<DataframeRow*> rows;

    public:

        Dataframe * addRow(DataframeRow *row) {
            rows.push_back(row);
            return this;
        }

        Dataframe * loadCsv(string filename) {
            ifstream input(filename);
            vector<string> headers;
            schema.clear();
            rows.clear();

            for( std::string line; getline( input, line ); ) {
                if (!headers.size()) {
                    headers = splitRow(line, ',');
                    for (int i = 0; i < headers.size(); i++) {
                        // todo: auto schema detection, if chosen
                        DataframeSchemaField * sf = new DataframeSchemaField(headers[i], String, 50);
                        schema[to_lower(headers[i])] = sf;
                    }
                }
                else {
                    vector<string> row = splitRow(line, ',');
                    DataframeRow * dfr = new DataframeRow();

                    for (int i = 0; i < headers.size(); i++) {
                        dfr -> set(headers[i], row[i]);
                    }

                    rows.push_back(dfr);
                }
            }
            return this;
        }

        void printSchema() {
            cout << "{\n";
            for (unordered_map<string, DataframeSchemaField*>::iterator it = schema.begin(); it != schema.end(); it++) {
                cout << "\t" << it -> second -> name() << ": " << it -> second -> type() << "\n";
            }
            cout << "}\n";
        }

        unordered_map<string, DataframeSchemaField*> getSchema() { return schema; }

        void printRow(int index) {
            if (rows.size() > index) rows[index] -> print();
        }

        void show(int n) {
            n = min(n, (int)rows.size());
            for (int i = 0; i < n; i++) {
                rows[i] -> print();
            }
            cout << "Showing " << n << " out of " << rows.size() << " rows\n";
        }

        void show() {
            show(10);
        }

        int size() {
            return rows.size();
        }

        DataframeRow * getRowByIndex(int index) {
            if (index >= rows.size()) return NULL;
            DataframeRow * dfr = new DataframeRow();

            for (unordered_map<string, DataframeSchemaField*>::iterator it = schema.begin(); it != schema.end(); it++) {
                // todo: casting row according to schema
                dfr -> set(it -> second -> name(), rows[index] -> get(it -> first));
            }

            return dfr;
        }

        DataframeRow * getRowFieldsByIndex(int index, vector<string> fields) {
            if (index >= rows.size()) return NULL;
            DataframeRow * dfr = new DataframeRow();

            for (int i = 0; i < fields.size(); i++) {
                // todo: casting row according to schema
                string field = to_lower(fields[i]);
                if (schema.find(field) != schema.end()) dfr -> set(fields[i], rows[index] -> get(field));
                else dfr -> set(field, NULL);
            }

            return dfr;
        }

};


enum QueryConditionOperator {EQUALS, AND, OR};
enum QueryConditionType {FIELD, BOOLEAN, NESTED};
class QueryCondition {

    string field;
    QueryConditionOperator condOperator;
    string value;
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

class QueryField {

	string _name;
	string _as;

    public:
        QueryField(string name) : _name(name) {}
        QueryField * as(string alias) {
            _as = alias;
            return this;
        }
        QueryCondition * Equals(string val) {
            return new QueryCondition(_name, EQUALS, val);
        }
        string name() { return _name; }
        void print() {
            cout << "QueryField {" << "name: " << _name << ", as: " << _as << "}\n";
        }

};

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

            int rowIndex = 0;
            while (rowIndex < _from -> dataframe() -> size() && df -> size() < rowsToFetch) {
                DataframeRow * dfr_raw = _from -> dataframe() -> getRowByIndex(rowIndex);
                DataframeRow * dfr = (_select_all) ? dfr_raw : _from -> dataframe() -> getRowFieldsByIndex(rowIndex, requiredFields);

                if (!_where || _where -> evaluateRow(dfr_raw)) {
                    df -> addRow(dfr);
                }
                rowIndex++;
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

QueryField * field(string name) {
	return new QueryField(name);
}

QueryView * view(Dataframe * df) {
	return new QueryView(df);
}

template<typename ...Conditions>
QueryCondition * condition(Conditions... conditions) {
    vector<QueryCondition*> chld = {conditions...};
    return new QueryCondition(chld);
}

QueryCondition * And() {
    return new QueryCondition(AND);
}

int main() {

    DataframeSchema * schema = new DataframeSchema();
    schema ->
        addField( IntField("id")->defaultValue(0) );

	Dataframe *df = new Dataframe();
    df -> loadCsv("resources/imdb_1.csv");
    df -> printSchema();
//	cout << "__________ Initial df\n";
//    df -> show();

    char ch;
    cout << "\n\nEnter anything to start query: ";
    cin >> ch;

    cout << "__________ Final df\n";

    clock_t start, end;
    start = clock();

    // V2, current fav
	Query * q = new Query();
	q -> 
	select(
            field("id"),
            field("title"),
            field("imdbId"),
		    field("imdbvotes"),
		    field("imdbrating"),
		    field("year")
	) ->

	from(

		view(df)
		// view(df) -> as("mop")

	) ->

	where(
	        condition(
	                field("year")->Equals("1994"),
	                And(),
	                field("rated")->Equals("PG-13")
	                )
	        ) ->
    limit(10) ->
	getDataframe() ->
	show();



    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Query took : " << fixed << time_taken << setprecision(5);
    cout << " sec\n\n";
//	-> print();

	// .where(

	// 	condition(
	// 		field("mop.asda").cast(Int).Equals(12),
	// 		And,
	// 		field("asd.aaa").greaterOrEqual(122),
	// 		And,
	// 		condition(
	// 			field("mopp").Equals("asd"),
	// 			Or,
	// 			field()
	// 			)
	// 		)

	// 	)

	// .innerJoin(
	// 	view(df2, "asda"),
	// 	field("mop.asda").Equals(
	// 		field("asda.ssas").multiply(10)
	// 		)
	// 	)

	return 0;
}

// ----------------------------------------------------------------------------------------------------------------


// V1
/*
q.select()
    .field("asda").cast(Int)
    .field("lop").as("lopeee")

.where()
    .field("asda").cast(Int).add(12).Equals(100)
    .and()
    .field("lop").greaterOrEqual(120)
    .and(
            field("sss").isNull()
            .or()
            field("asdad").greaterOrEqual(field("sdd"))
        )

.from(df, "user_table")
.limit(20)
*/

// ----------------------------------------------------------------------------------------------------------------

// V3
// q.select("asda", cast("asda", Int), multiply("asda", 12))

// q.select(field("asd"), field("op").cast(Int), field("lopez").as("lop"))
// 	.from(df)
// 	.where(
// 		filter("a", greaterOrEqual, 12).and(
// 											filter("b", equal, 11.2)
// 											.or("c", lessThan, 22)
// 											)
// 		)