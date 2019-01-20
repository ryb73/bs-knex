type t('a);
let make: Core.t(('a, _, _, _)) => t('a);

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
let execute: t('a) => Reduice.Promise.t('a);