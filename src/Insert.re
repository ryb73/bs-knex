type any;
external any : _ => any = "%identity";

type t = {
    internalInsert: Core.t,
    pendingSets: Js.Dict.t(any)
};

let make = (knex) => {
    internalInsert: knex,
    pendingSets: Js.Dict.empty()
};

let set = (column, value, { pendingSets } as i) => {
    Js.Dict.set(pendingSets, column, any(value));
    { ...i, pendingSets };
};

[@bs.send.pipe: Core.t] external into : string => Core.t = "into";
let into = (table, { internalInsert } as i) =>
    { ...i, internalInsert: into(table, internalInsert) };

[@bs.send.pipe: Core.t] external insert : Js.Dict.t(_) => Core.t = "insert";

module Builder = {
    type nonrec t = t;
    type result = int;
    let getCore = ({ internalInsert }) => internalInsert;
    let setCore = (update, internalInsert) => { ...update, internalInsert };
    let finish = ({ internalInsert, pendingSets }) =>
        internalInsert
        |> insert(pendingSets);
};

include Queryable.Make(Builder);
