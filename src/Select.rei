type t;
let make: Core.t => t;

let column: (~alias: Js.Dict.key=?, string, t) => t;

let count: (string, t) => t;
let countDistinct: (string, t) => t;

let from: (~alias: Js.Dict.key=?, string, t) => t;
let innerJoin: (string, string, string, string, t) => t;

let groupBy: (string, t) => t;

type order = Ascending | Descending;
let orderBy: (string, order, t) => t;

let where: (string, t) => t;
let whereParam: (string, Params.t, t) => t;
let orWhere: (string, t) => t;
let orWhereParam: (string, Params.t, t) => t;
let whereEx: (unit => Expression.t, t) => t;
let orWhereEx: (unit => Expression.t, t) => t;

let toString: t => string;
let execute: t => Reduice.Promise.t(array(Js.Json.t));