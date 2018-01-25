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
        |> whereEx(() => { open! Expression; open! Params;
            Expression.make
                |> whereParam("a = ?", ?? 9)
                |> orWhere("a > 20")
                |> orWhereEx(() => {
                    Expression.make
                        |> whereParam("?? = ??", ?? 9 |? 10)
                        |> where("10 = 11")
                })
        })
        |> toString
        |> Js.log
);

/* Insert.(
    make()
        |> into("tbl")
        |> setString("a", "ay")
        |> setInt("b", 99)
        |> setBool("bool", true)
        |> toString
        |> Js.log
); */