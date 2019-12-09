open Knex;
open Params.Infix;
open Jest;
open Expect;

let knex = Knex.make(PostgreSQL);

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
