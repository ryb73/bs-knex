open Knex;
open Select;
open Params.Infix;
open Jest;
open Expect;

let knex = Knex.make(PostgreSQL);

let evaluate = (expected, query) =>
    Select.toString(query)
    |> expect
    |> toEqual(expected);

let mk = () => Select.make(knex);

describe("columns", () => {
    test("basic", () =>
        mk()
        |> column("col")
        |> evaluate({|select "col"|})
    );

    test("alias", () =>
        mk()
        |> column(~alias="c", "col")
        |> evaluate({|select "col" as "c"|})
    );

    test("count", () =>
        mk()
        |> count("col")
        |> evaluate({|select count("col")|})
    );

    test("count alias", () =>
        mk()
        |> count("col as c")
        |> evaluate({|select count("col") as "c"|})
    );

    test("countDistinct", () =>
        mk()
        |> countDistinct("col")
        |> evaluate({|select count(distinct "col")|})
    );

    test("countDistinct alias", () =>
        mk()
        |> countDistinct("col as c")
        |> evaluate({|select count(distinct "col") as "c"|})
    );
});

describe("from", () => {
    test("basic", () =>
        mk()
        |> from("tbl")
        |> evaluate({|select * from "tbl"|})
    );

    test("alias", () =>
        mk()
        |> from(~alias="t", "tbl")
        |> evaluate({|select * from "tbl" as "t"|})
    );

    test("innerJoin", () =>
        mk()
        |> from("tbl")
        |> innerJoin("tbl2", "tbl2.id", "=", "tbl.id")
        |> evaluate({|select * from "tbl" inner join "tbl2" on "tbl2"."id" = "tbl"."id"|})
    );

    test("innerJoin alias", () =>
        mk()
        |> from(~alias="t", "tbl")
        |> innerJoin("tbl2 as t2", "t2.id", "=", "t.id")
        |> evaluate({|select * from "tbl" as "t" inner join "tbl2" as "t2" on "t2"."id" = "t"."id"|})
    );
});

describe("where", () => {
    test("basic", () =>
        mk()
        |> where("2 = 3")
        |> evaluate({|select * where 2 = 3|})
    );

    describe("in", () => {
        test("number", () =>
            mk()
            |> whereIn("n", [| 3, 4, 5 |])
            |> evaluate({|select * where "n" in (3, 4, 5)|})
        );

        test("string", () =>
            mk()
            |> whereIn("s", [| "three", "four", "five" |])
            |> evaluate({|select * where "s" in ('three', 'four', 'five')|})
        );
    });

    test("param", () =>
        mk()
        |> whereParam("x = ?", ?? "ex")
        |> evaluate({|select * where x = 'ex'|})
    );

    test("or", () =>
        mk()
        |> where("a < 20")
        |> orWhere("a > 20")
        |> evaluate({|select * where a < 20 or a > 20|})
    );

    test("or param", () =>
        mk()
        |> where("a < 20")
        |> orWhereParam("a > ?", ?? 98.2)
        |> evaluate({|select * where a < 20 or a > 98.2|})
    );

    test("expression", () =>
        mk()
        |> whereEx(() => { open! Expression;
            Expression.make
            |> whereParam("a = ?", ?? 9)
            |> orWhere("a > 20")
            |> orWhereEx(() => {
                Expression.make
                |> whereParam("? = ?", ?? 9 |? 10)
                |> where("10 = 11")
            })
        })
        |> evaluate({|select * where (a = 9 or a > 20 or (9 = 10 and 10 = 11))|})
    );
});

describe("groupBy", () => {
    test("one", () =>
        mk()
        |> groupBy("col")
        |> evaluate({|select * group by "col"|})
    );

    test("many", () =>
        mk()
        |> groupBy("col")
        |> groupBy("col2")
        |> groupBy("col3")
        |> evaluate({|select * group by "col", "col2", "col3"|})
    );
});

describe("orderBy", () => {
    test("one", () =>
        mk()
        |> orderBy("theorder", Ascending)
        |> evaluate({|select * order by "theorder" asc|})
    );

    test("many", () =>
        mk()
        |> orderBy("theorder", Ascending)
        |> orderBy("id", Descending)
        |> evaluate({|select * order by "theorder" asc, "id" desc|})
    );
});

test("forUpdate", () =>
    mk()
    |> column("*")
    |> from("tbl")
    |> forUpdate
    |> evaluate({|select * from "tbl" for update|})
);

test("limit", () =>
    mk()
    |> limit(123)
    |> evaluate({|select * limit 123|})
);
