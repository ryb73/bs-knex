type any;
external any : _ => any = "%identity";

type t('resultType) = {
    internalUpdate: Core.t(unit),
    pendingSets: Js.Dict.t(any)
};

type f('a) = [@bs] string => Core.t(unit);
external asFunc : Core.t((_, 'a, _, _)) => f('a) = "%identity";
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

[@bs.send.pipe: Core.t('a)] external returning : array(string) => Core.t('a) = "returning";
let returning = columns => wrap(returning(columns));

[@bs.send.pipe: Core.t('a)] external update : Js.Dict.t(_) => Core.t('a) = "update";

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
