module Types: {
    type knex('resultTypes);
};

type t('resultTypes) = Types.knex('resultTypes);

module Params: {
    type t = Params.t;
    let make: 'a => t;
    let bind: ('a, t) => t;

    module Infix: {
        let ( ?? ): 'a => t;
        let ( |? ): (t, 'a) => t;
    };
};
module Expression: {
    type t = Types.knex(unit);
    [@bs.val] external make: t = "this";
    let where: (string, t) => t;
    let whereParam: (string, Params.t, t) => t;
    let whereIn: (string, array('a), t) => t;
    let orWhere: (string, t) => t;
    let orWhereParam: (string, Params.t, t) => t;
    let whereEx: (unit => t, t) => t;
    let orWhereEx: (unit => t, t) => t;
};
module Delete: {
    type t('resultType);
    let make: (string, Types.knex((_, _, _, 'resultType))) => t('resultType);

    let where: (string, t('a)) => t('a);
    let whereParam: (string, Params.t, t('a)) => t('a);
    let whereIn: (string, array(_), t('a)) => t('a);
    let orWhere: (string, t('a)) => t('a);
    let orWhereParam: (string, Params.t, t('a)) => t('a);
    let whereEx: (unit => Expression.t, t('a)) => t('a);
    let orWhereEx: (unit => Expression.t, t('a)) => t('a);

    let toString: t(_) => string;
    let execute: t('a) => Js.Promise.t('a);
};
module Insert: {
    type t('a);
    let make: Types.knex((_, 'result, _, _)) => t('result);

    let set: (Js.Dict.key, 'a, t('b)) => t('b);
    let into: (string, t('a)) => t('a);
    let returning: (array(string), t('a)) => t('a);

    let toString: t(_) => string;
    let execute: t('a) => Js.Promise.t('a);
};
module Select: {
    type t('a);
    let make: Types.knex(('a, _, _, _)) => t('a);

    let column: (~alias: Js.Dict.key=?, string, t('a)) => t('a);

    let count: (string, t('a)) => t('a);
    let countDistinct: (string, t('a)) => t('a);

    let from: (~alias: Js.Dict.key=?, string, t('a)) => t('a);
    let innerJoin: (string, string, string, string, t('a)) => t('a);

    let groupBy: (string, t('a)) => t('a);

    type order = Ascending | Descending;
    let orderBy: (string, order, t('a)) => t('a);

    let where: (string, t('a)) => t('a);
    let whereParam: (string, Params.t, t('a)) => t('a);
    let whereIn: (string, array(_), t('a)) => t('a);
    let orWhere: (string, t('a)) => t('a);
    let orWhereParam: (string, Params.t, t('a)) => t('a);
    let whereEx: (unit => Expression.t, t('a)) => t('a);
    let orWhereEx: (unit => Expression.t, t('a)) => t('a);

    let toString: t(_) => string;
    let execute: t('a) => Js.Promise.t('a);
};
module Update: {
    type t('resultType);
    let make: (string, Types.knex((_, 'a, _, _))) => t('a);

    let set: (Js.Dict.key, _, t('a)) => t('a);
    let returning: (array(string), t('a)) => t('a);

    let where: (string, t('a)) => t('a);
    let whereParam: (string, Params.t, t('a)) => t('a);
    let whereIn: (string, array(_), t('a)) => t('a);
    let orWhere: (string, t('a)) => t('a);
    let orWhereParam: (string, Params.t, t('a)) => t('a);
    let whereEx: (unit => Expression.t, t('a)) => t('a);
    let orWhereEx: (unit => Expression.t, t('a)) => t('a);

    let toString: t(_) => string;
    let execute: t('a) => Js.Promise.t('a);
};
module MSSQL: {
    type resultTypes = (
        /* select */ Js.Json.t,
        /* insert */ Js.Json.t,
        /* update */ Js.Json.t,
        /* delete */ Js.Json.t,
    );
};
module MySQL: {
    type resultTypes = (
        /* select */ array(Js.Json.t),
        /* insert */ array(int),
        /* update */ int,
        /* delete */ int,
    );
};
module PostgreSQL: {
    type resultTypes = (
        /* select */ array(Js.Json.t),
        /* insert */ Js.Json.t,
        /* update */ Js.Json.t,
        /* delete */ int,
    );
};
module SQLite3: {
    type resultTypes = (
        /* select */ Js.Json.t,
        /* insert */ Js.Json.t,
        /* update */ Js.Json.t,
        /* delete */ Js.Json.t,
    );
};

type client('resultTypes) =
    | PostgreSQL: client(PostgreSQL.resultTypes)
    | SQLite3: client(SQLite3.resultTypes)
    | MySQL: client(MySQL.resultTypes)
    | MSSQL: client(MSSQL.resultTypes);

let make:
    (~host: string=?, ~user: string=?, ~password: string=?, ~database: string=?,
     client('resultType)) => Types.knex('resultType);
let destroy: Types.knex('a) => Js.Promise.t(unit);

let raw: Types.knex(_) => string => Js.Promise.t(Js.Json.t);
let transaction: (Types.knex('a), Types.knex('a) => Js.Promise.t('b)) => Js.Promise.t('c);
