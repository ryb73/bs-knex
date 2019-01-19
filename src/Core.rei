type client('resultTypes) =
    | PostgreSQL: client(PostgreSQL.resultTypes)
    | SQLite3: client(SQLite3.resultTypes)
    | MySQL: client(MySQL.resultTypes)
    | MSSQL: client(MSSQL.resultTypes);

type t('resultTypes);
let make:
    (~host: string=?, ~user: string=?, ~password: string=?, ~database: string=?,
     client('resultType)) => t('resultType);
let destroy: (~callback: (unit => unit)=?, t(_)) => unit;
