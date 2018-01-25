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
            make
                |> where(build(knex, "a = ?") |?. 9)
                |> orWhere("a > 20")
                |> orWhereEx(() => {
                    make
                        |> where(build(knex, "?? = ??") |? 9 |?. 10)
                        |> where("10 = 11")
                })
        })
        |> toString
        |> Js.log
);