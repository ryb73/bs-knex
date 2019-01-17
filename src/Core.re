type connection;
[@bs.obj] external connection:
    (~host: string=?, ~user: string=?, ~password: string=?, ~database: string=?)
    => connection = "";

type opts;
[@bs.obj] external opts: (~client: string, ~connection: connection) => opts = "";

type client = PostgreSQL | SQLite3 | MySQL | MSSQL;
let clientToString = fun
    | PostgreSQL => "pg"
    | SQLite3 => "sqlite3"
    | MySQL => "mysql"
    | MSSQL => "pmssql";

type t;

[@bs.module] external make: opts => t = "knex";
let make = (~host=?, ~user=?, ~password=?, ~database=?, client) =>
    make(opts(
        ~client=clientToString(client),
        ~connection=connection(~host?, ~user?, ~password?, ~database?),
    ));

[@bs.send.pipe: t] external destroy: (~callback: (unit => unit)=?) => unit = "";
