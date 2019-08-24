open Knex;
open Params.Infix;
open Jest;
open Expect;
open PromEx;
open Js.Promise;

let knex = Knex.make(PostgreSQL);

describe("Select", () => {
    open Select;

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
});

test("Insert", () => {
    open Insert;

    Insert.make(knex)
    |> into("tbl")
    |> set("a", "a\"'y")
    |> set("b", 99)
    |> set("bool", true)
    |> returning([|"id"|])
    |> toString
    |> expect
    |> toEqual({|insert into "tbl" ("a", "b", "bool") values ('a"''y', 99, true) returning "id"|});
});

test("Update", () => {
    open Update;

    Update.make("tbl", knex)
    |> set("v", 39)
    |> where("a = 9")
    |> whereParam("a = ?", ?? 10)
    |> toString
    |> expect
    |> toEqual({|update "tbl" set "v" = 39 where a = 9 and a = 10|})
});

test("Delete", () => {
    open Delete;

    Delete.make("tbl", knex)
    |> where("a = 9")
    |> orWhereParam("a = ?", ?? 10)
    |> toString
    |> expect
    |> toEqual({|delete from "tbl" where a = 9 or a = 10|})
});

describe("Raw", () => {
    test("no params", () =>
        Knex.raw(knex, "Select 1")
        |> Raw.toString
        |> expect
        |> toEqual("Select 1")
    );

    test("params", () =>
        Knex.raw(~params=(?? "f" |? "t" |? "f2" |? 1), knex, "Select ?? from ?? where ?? = ?")
        |> Raw.toString
        |> expect
        |> toEqual({|Select "f" from "t" where "f2" = 1|})
    )
});

[@decco.decode]
type config = {
    host: string,
    user: string,
    password: string,
    database: string,
};

[@decco.decode]
type row = {
    vc: string,
};

describe("transactions", () => {
    let {host, user, password, database} =
        Config.get("test")
        |> config_decode
        |> Belt.Result.getExn;

    let knex = Knex.make(~host, ~user, ~password, ~database, PostgreSQL);

    let tableName = ref(Uuid.V4.uuidv4());

    beforeEachPromise(() =>
        (?? tableName^)
        |> Knex.raw(~params=_, knex, {|
            CREATE TABLE ?? (
                id SERIAL,
                vc VARCHAR
            );
        |})
        |> Raw.execute
    );

    afterEachPromise(() =>
        (?? tableName^)
        |> Knex.raw(~params=_, knex, "DROP TABLE ??")
        |> Raw.execute
        |> tap(_ => tableName := Uuid.V4.uuidv4())
    );

    testPromise("success", () =>
        transaction(knex, tx => Insert.(
            Insert.make(tx)
            |> into(tableName^)
            |> set("vc", "heya")
            |> execute
        ))
        |> then_(_ => Select.(
            Select.make(knex)
            |> from(tableName^)
            |> column("vc")
            |> execute
        ))
        |> map(Js.Array.map(row_decode))
        |> map(Js.Array.map(Belt.Result.getExn))
        |> map(expect) |> map(toEqual([|{vc:"heya"}|]))
    );

    testPromise("failure", () =>
        transaction(knex, tx => Insert.(
            Insert.make(tx)
            |> into(tableName^)
            |> set("vc", "heya")
            |> execute
            |> map(_ => failwith(""))
        ))
        |> catch(_ => resolve())
        |> then_(_ => Select.(
            Select.make(knex)
            |> from(tableName^)
            |> column("vc")
            |> execute
        ))
        |> map(Js.Array.map(row_decode))
        |> map(Js.Array.map(Belt.Result.getExn))
        |> map(expect) |> map(toEqual([||]))
    );

    testPromise("rollback", () =>
        transaction(knex, tx => Insert.(
            Insert.make(tx)
            |> into(tableName^)
            |> set("vc", "heya")
            |> execute
            // ignore to test that it's not the promise rejection that causes rollback
            |> map(_ => rollback(tx) |> ignore)
        ))
        |> catch(_ => resolve())
        |> then_(_ => Select.(
            Select.make(knex)
            |> from(tableName^)
            |> column("vc")
            |> execute
        ))
        |> map(Js.Array.map(row_decode))
        |> map(Js.Array.map(Belt.Result.getExn))
        |> map(expect) |> map(toEqual([||]))
    );
});
