module Types = { include KnexTypes; };
module Delete = { include Delete; };
module Expression = { include Expression; };
module Insert = { include Insert; };
module Params = { include Params; };
module Select = { include Select; };
module Update = { include Update; };

module MSSQL = { include MSSQL; };
module MySQL = { include MySQL; };
module PostgreSQL = { include PostgreSQL; };
module SQLite3 = { include SQLite3; };

type t('resultTypes) = Types.knex('resultTypes);

type connection;
[@bs.obj] external connection:
    (~host: string=?, ~user: string=?, ~password: string=?, ~database: string=?)
    => connection = "";

type opts;
[@bs.obj] external opts: (~connection: connection=?, ~client: string) => opts = "";

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
    (type a, ~host=?, ~user=?, ~password=?, ~database=?, client: client(a)): t(a) => {
        /* Don't make connection object if none of the options are set. knex treats the
        existence of `connection` as enabling connections even if it's empty */
        let connection =
            [| host, user, password, database |]
            |> Js.Array.some((!==)(None))
            ? Some(connection(~host?, ~user?, ~password?, ~database?))
            : None;

        opts(
            ~connection?,
            ~client=clientToString(client),
        )
        |> make
        |> Obj.magic;
    };

[@bs.send] external raw: t(_) => string => Reduice.Promise.t(Js.Json.t) = "";

[@bs.send] external transaction:
    t('a) => (t('a) => Reduice.Promise.t(_)) => Reduice.Promise.t(_) = "";

[@bs.send.pipe: t(_)] external destroy: unit => Reduice.Promise.t(unit) = "";
