type any;
external any : _ => any = "%identity";

type t('a) = {
    internalInsert: Core.t(unit),
    pendingSets: Js.Dict.t(any)
};

let make = (knex: Core.t(_)) => {
    internalInsert: Obj.magic(knex),
    pendingSets: Js.Dict.empty()
};

let set = (column, value, { pendingSets } as i) => {
    Js.Dict.set(pendingSets, column, any(value));
    { ...i, pendingSets };
};

let wrap = (f) =>
    ({ internalInsert } as i) =>
        { ...i, internalInsert: f(internalInsert) };

[@bs.send.pipe: Core.t('a)] external into : string => Core.t('a) = "into";
let into = table => wrap(into(table));

[@bs.send.pipe: Core.t('a)] external returning : array(string) => Core.t('a) = "returning";
let returning = columns => wrap(returning(columns));

[@bs.send.pipe: Core.t('a)] external insert : Js.Dict.t(_) => Core.t('a) = "insert";

module Builder = {
    type nonrec t('a) = t('a);
    let getCore = ({ internalInsert }) => Obj.magic(internalInsert);
    let setCore = (update, internalInsert: Core.t(_)) =>
        { ...update, internalInsert: Obj.magic(internalInsert) };
    let finish = ({ internalInsert, pendingSets }) =>
        internalInsert
        |> insert(pendingSets);
};

include Queryable.Make(Builder);
