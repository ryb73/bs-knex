open Knex;
open Delete;
open Params.Infix;
open Jest;
open Expect;

let knex = Knex.make(PostgreSQL);

test("Delete", () => {
    Delete.make("tbl", knex)
    |> where("a = 9")
    |> orWhereParam("a = ?", ?? 10)
    |> toString
    |> expect
    |> toEqual({|delete from "tbl" where a = 9 or a = 10|})
});
