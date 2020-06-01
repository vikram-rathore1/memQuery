//
// Created by Vikram Singh Rathore
//

#include<bits/stdc++.h>
#include "lib/util/timer.h"
#include "lib/csv.h"
#include "lib/dataframe/dataframe.h"
#include "lib/query/query.h"
#include "lib/generators.h"
using namespace std;

int main() {

    Timer t;

    // Read csv file
    Csv * csv = new Csv("resources/imdb_1.csv", ',');
    cout << "Csv read in " << t.getElapsedTime() << " sec\n";

    // Load csv into dataframe
    t.restart();
	Dataframe *df = new Dataframe();
    df -> loadCsv(csv);
    df -> printSchema();
    cout << "Csv loaded to df in " << t.getElapsedTime() << " sec\n";

    // Process query
    t.restart();
	Query * q = new Query();
	q
	-> select(
            field("id"),
            field("title"),
            field("imdbId"),
		    field("imdbvotes"),
		    field("imdbrating"),
		    field("year"),
		    field("rated"),
		    field("bogus_field")
	)

	-> from(

		view(df)

	)

	-> where(
	        condition(
	                field("year")->Equals("1994"),
	                And(),
                    field("imdbrating")->Equals("7.3"),
	                And(),
	                condition(
                            field("rated")->Equals("PG-13"),
	                        Or(),
                            field("rated")->Equals("PG")
	                        )
	                )
	        )
//	-> limit(10)
	-> getDataframe()
	-> show(20);

    cout << "Query took " << t.getElapsedTime() << " sec\n";
	return 0;
}












// ----------------------------------------------------------------------------------------------------------------

//    DataframeSchema * schema = new DataframeSchema(
//      schemaField("id", Int) -> length(20) -> null(false) -> default(0) -> primaryKey(true),
//      schemaField("asd", String) -> default("aaaa")
//    );
//    schema ->
//        addField( IntField("id")->defaultValue(0) );


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
// .innerJoin(
// 	view(df2, "asda"),
// 	field("mop.asda").Equals(
// 		field("asda.ssas").multiply(10)
// 		)
// 	)
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