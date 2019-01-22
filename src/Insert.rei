type t('a);
let make: KnexTypes.knex((_, 'result, _, _)) => t('result);

let set: (Js.Dict.key, 'a, t('b)) => t('b);
let into: (string, t('a)) => t('a);
let returning: (array(string), t('a)) => t('a);

let toString: t(_) => string;
let execute: t('a) => Reduice.Promise.t('a);
