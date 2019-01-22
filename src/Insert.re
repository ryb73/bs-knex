type any;
external any : _ => any = "%identity";

type t('a) = {
    internalInsert: KnexTypes.knex(unit),
    pendingSets: Js.Dict.t(any)
};

let make = (knex: KnexTypes.knex(_)) => {
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

[@bs.send.pipe: KnexTypes.knex('a)] external into : string => KnexTypes.knex('a) = "into";
let into = table => wrap(into(table));

[@bs.send.pipe: KnexTypes.knex('a)] external returning : array(string) => KnexTypes.knex('a) = "returning";
let returning = columns => wrap(returning(columns));

[@bs.send.pipe: KnexTypes.knex('a)] external insert : Js.Dict.t(_) => KnexTypes.knex('a) = "insert";

module Builder = {
    type nonrec t('a) = t('a);
    let getCore = ({ internalInsert }) => Obj.magic(internalInsert);
    let setCore = (update, internalInsert: KnexTypes.knex(_)) =>
        { ...update, internalInsert: Obj.magic(internalInsert) };
    let finish = ({ internalInsert, pendingSets }) =>
        internalInsert
        |> insert(pendingSets);
};

include Queryable.Make(Builder);
