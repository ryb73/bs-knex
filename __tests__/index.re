open Knex;
open Params.Infix;
open Jest;
open Expect;
open PromEx;
open Js.Promise;

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

    afterAllPromise(() => destroy(knex));

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
