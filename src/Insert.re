type _any;
external _any : _ => _any = "%identity";

type t = {
    internalInsert: Core.t,
    pendingSets: Js.Dict.t(_any)
};

let make = (knex) => {
    internalInsert: knex,
    pendingSets: Js.Dict.empty()
};

let set = (column, value, { pendingSets } as i) => {
    Js.Dict.set(pendingSets, column, _any(value));
    { ...i, pendingSets };
};

[@bs.send.pipe: Core.t] external _insert : Js.Dict.t(_) => Core.t = "insert";
[@bs.send.pipe: Core.t] external _toString : unit => string = "toString";
let toString = ({ internalInsert, pendingSets }) =>
    internalInsert
        |> _insert(pendingSets)
        |> _toString();

[@bs.send.pipe: Core.t] external _into : string => Core.t = "into";
let into = (table, { internalInsert } as i) =>
    { ...i, internalInsert: _into(table, internalInsert) };
