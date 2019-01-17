type t;
let make: (string, Core.t) => t;

let set: (Js.Dict.key, 'a, t) => t;

let where: (string, t) => t;
let whereParam: (string, Params.t, t) => t;
let orWhere: (string, t) => t;
let orWhereParam: (string, Params.t, t) => t;
let whereEx: (unit => Expression.t, t) => t;
let orWhereEx: (unit => Expression.t, t) => t;

let toString: t => string;
let execute: t => Reduice.Promise.t(int);
