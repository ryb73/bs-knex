type any;
external any : _ => any = "%identity";

type t('resultType) = {
    internalUpdate: KnexTypes.knex(unit),
    pendingSets: Js.Dict.t(any)
};

type f('a) = [@bs] string => KnexTypes.knex(unit);
external asFunc : KnexTypes.knex((_, 'a, _, _)) => f('a) = "%identity";
let make = (table, knex) => {
    let f = asFunc(knex);
    {
        internalUpdate: [@bs] f(table),
        pendingSets: Js.Dict.empty()
    };
};

let set = (column, value, { pendingSets } as u) => {
    Js.Dict.set(pendingSets, column, any(value));
    { ...u, pendingSets };
};

let wrap = (f) =>
    ({ internalUpdate } as i) =>
        { ...i, internalUpdate: f(internalUpdate) };

[@bs.send.pipe: KnexTypes.knex('a)] external returning : array(string) => KnexTypes.knex('a) = "returning";
let returning = columns => wrap(returning(columns));

[@bs.send.pipe: KnexTypes.knex('a)] external update : Js.Dict.t(_) => KnexTypes.knex('a) = "update";

module Builder = {
    type nonrec t('a) = t('a);
    let getCore = ({ internalUpdate }) => internalUpdate;
    let setCore = (update, internalUpdate) => { ...update, internalUpdate };
    let finish = ({ internalUpdate, pendingSets }) =>
        internalUpdate
        |> update(pendingSets);
};

include Queryable.Make(Builder);
include Whereable.Make(Builder);
