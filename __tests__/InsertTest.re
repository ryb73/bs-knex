open Knex;
open Insert;
open Jest;
open Expect;

let knex = Knex.make(PostgreSQL);

test("", () =>
    Insert.make(knex)
    |> into("tbl")
    |> set("a", "a\"'y")
    |> set("b", 99)
    |> set("bool", true)
    |> returning([|"id"|])
    |> toString
    |> expect
    |> toEqual({|insert into "tbl" ("a", "b", "bool") values ('a"''y', 99, true) returning "id"|})
);
