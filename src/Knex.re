module Types = { include KnexTypes; };
module Delete = { include Delete; };
module Expression = { include Expression; };
module Insert = { include Insert; };
module Params = { include Params; };
module Select = { include Select; };
module Update = { include Update; };
module Raw = { include Raw; };

module MSSQL = { include MSSQL; };
module MySQL = { include MySQL; };
module PostgreSQL = { include PostgreSQL; };
module SQLite3 = { include SQLite3; };

type t('resultTypes) = Types.knex('resultTypes);

type connection;
[@bs.obj] external connection:
    (~host: string=?, ~user: string=?, ~password: string=?, ~database: string=?)
    => connection = "";

type pool;
[@bs.obj] external pool: (~min: int=?, ~max: int=?) => pool = "";

type opts;
[@bs.obj]
external opts:
    (~connection: connection=?, ~pool: pool=?, ~client: string) => opts = "";

type client('resultTypes) =
    | PostgreSQL: client(PostgreSQL.resultTypes)
    | SQLite3: client(SQLite3.resultTypes)
    | MySQL: client(MySQL.resultTypes)
    | MSSQL: client(MSSQL.resultTypes);

let clientToString = (type a, client: client(a)) =>
    switch client {
        | PostgreSQL => "pg"
        | SQLite3 => "sqlite3"
        | MySQL => "mysql"
        | MSSQL => "mssql"
    };

[@bs.module] external make: opts => Js.Json.t = "knex";
let make =
    (type a, ~host=?, ~user=?, ~password=?, ~database=?, ~poolMin=?, ~poolMax=?,
        client: client(a)): t(a) =>
    {
        /* Don't make connection object if none of the options are set. knex treats the
        existence of `connection` as enabling connections even if it's empty */
        let connection =
            [| host, user, password, database |]
            |> Js.Array.some((!==)(None))
            ? Some(connection(~host?, ~user?, ~password?, ~database?))
            : None;

        opts(
            ~connection?,
            ~pool=pool(~min=?poolMin, ~max=?poolMax),
            ~client=clientToString(client),
        )
        |> make
        |> Obj.magic;
    };

[@bs.send] external raw: (t(_), string, ~params: Params.t=?, unit) => Raw.t = "";
let raw = (~params=?, knex, query) => raw(knex, query, ~params?, ());

[@bs.send] external transaction:
    t('a) => (t('a) => Js.Promise.t(_)) => Js.Promise.t(_) = "";

[@bs.send] external destroy: t(_) => Js.Promise.t(unit) = "";

[@bs.send] external rollback: t(_) => Js.Promise.t(unit) = "";
