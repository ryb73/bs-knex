type t('resultType) = Core.t(unit);

type f('a) = [@bs] string => t('a);
external asFunc : Core.t((_, _, _, 'a)) => f('a) = "%identity";
[@bs.send] external del : t('a) => t('a) = "del";
let make = (table, knex) => {
    let f = asFunc(knex);
    del([@bs] f(table));
};

module Builder = {
    type nonrec t('a) = t('a);
    let getCore = (v) => v;
    let setCore = (_, v) => v;
    let finish = getCore;
};

include Queryable.Make(Builder);
include Whereable.Make(Builder);
