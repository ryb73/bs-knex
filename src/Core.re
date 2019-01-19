type connection;
[@bs.obj] external connection:
    (~host: string=?, ~user: string=?, ~password: string=?, ~database: string=?)
    => connection = "";

type opts;
[@bs.obj] external opts: (~client: string, ~connection: connection) => opts = "";

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

type t('resultTypes);

[@bs.module] external make: opts => Js.Json.t = "knex";
let make = (type a, ~host=?, ~user=?, ~password=?, ~database=?, client: client(a)): t(a) =>
    opts(
        ~client=clientToString(client),
        ~connection=connection(~host?, ~user?, ~password?, ~database?),
    )
    |> make
    |> Obj.magic;

[@bs.send.pipe: t(_)] external destroy: (~callback: (unit => unit)=?) => unit = "";
