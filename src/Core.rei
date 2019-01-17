type client = PostgreSQL | SQLite3 | MySQL | MSSQL;
type t;
let make:
    (~host: string=?, ~user: string=?, ~password: string=?, ~database: string=?,
     client) => t;
let destroy: (~callback: (unit => unit)=?, t) => unit;
