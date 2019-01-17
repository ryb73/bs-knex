type _any;
external _any : _ => _any = "%identity";

type t = {
    internalUpdate: Core.t,
    pendingSets: Js.Dict.t(_any)
};

type f = [@bs] string => Core.t;
external asFunc : Core.t => f = "%identity";
let make = (table, knex) => {
    let f = asFunc(knex);
    {
        internalUpdate: [@bs] f(table),
        pendingSets: Js.Dict.empty()
    };
};

let set = (column, value, { pendingSets } as u) => {
    Js.Dict.set(pendingSets, column, _any(value));
    { ...u, pendingSets };
};

[@bs.send.pipe: Core.t] external update : Js.Dict.t(_) => Core.t = "update";

module Builder = {
    type nonrec t = t;
    type result = int;
    let getCore = ({ internalUpdate }) => internalUpdate;
    let setCore = (update, internalUpdate) => { ...update, internalUpdate };
    let finish = ({ internalUpdate, pendingSets }) =>
        internalUpdate
        |> update(pendingSets);
};

include Queryable.Make(Builder);
include Whereable.Make(Builder);
