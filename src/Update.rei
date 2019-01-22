type t('resultType);
let make: (string, KnexTypes.knex((_, 'a, _, _))) => t('a);

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
let execute: t('a) => Reduice.Promise.t('a);
