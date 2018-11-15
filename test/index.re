open Whereable;
open Params.Infix;

let knex = Core.make("mysql");

Select.(
    make(knex)
    |> count("blah as b")
    |> column(~alias="ha", "huh")
    |> from(~alias="t", "tbl")
    |> groupBy("ha")
    |> where("b = b")
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
    |> innerJoin("something as st", "st.id", "=", "b.id")
    |> orderBy("theorder", Ascending)
    |> toString
    |> Js.log
);

Insert.(
    make(knex)
    |> into("tbl")
    |> set("a", "a\"'y")
    |> set("b", 99)
    |> set("bool", true)
    |> toString
    |> Js.log
);

Update.(
    make("tbl", knex)
    |> set("v", 39)
    |> where("a = 9")
    |> whereParam("a = ?", ?? 10)
    |> toString
    |> Js.log
);

Delete.(
    make("tbl", knex)
    |> where("a = 9")
    |> whereParam("a = ?", ?? 10)
    |> toString
    |> Js.log
);