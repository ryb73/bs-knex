type _any;
external _any : _ => _any = "%identity";

type t = {
    internalUpdate: Core.t,
    pendingSets: Js.Dict.t(_any)
};

type _f = [@bs] string => Core.t;
external _asFunc : Core.t => _f = "%identity";
let make = (table, knex) => {
    let f = _asFunc(knex);
    {
        internalUpdate: [@bs] f(table),
        pendingSets: Js.Dict.empty()
    };
};

let set = (column, value, { pendingSets } as u) => {
    Js.Dict.set(pendingSets, column, _any(value));
    { ...u, pendingSets };
};

[@bs.send.pipe: Core.t] external _update : Js.Dict.t(_) => Core.t = "update";
[@bs.send.pipe: Core.t] external _toString : unit => string = "toString";
let toString = ({ internalUpdate, pendingSets }) =>
    internalUpdate
        |> _update(pendingSets)
        |> _toString();

include Whereable.Make({
    type nonrec t = t;
    let toCore = ({ internalUpdate }) => internalUpdate;
    let setCoreResult = (update, internalUpdate) => { ...update, internalUpdate };
});
