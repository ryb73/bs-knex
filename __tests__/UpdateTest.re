open Knex;
open Update;
open Params.Infix;
open Jest;
open Expect;

let knex = Knex.make(PostgreSQL);

test("", () => {
    Update.make("tbl", knex)
    |> set("v", 39)
    |> where("a = 9")
    |> whereParam("a = ?", ?? 10)
    |> toString
    |> expect
    |> toEqual({|update "tbl" set "v" = 39 where a = 9 and a = 10|})
});
