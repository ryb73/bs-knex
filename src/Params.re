type _any;
external _any : _ => _any = "%identity";

type paramBuilder =
    | ParamBuilder(Core.t, string, array(_any));

let build = (knex, expr) => ParamBuilder(knex, expr, [||]);

let bind = (v, ParamBuilder(knex, expr, bindings)) => {
    Js.Array.push(_any(v), bindings);
    ParamBuilder(knex, expr, bindings)
};

type _t;
[@bs.send] external _raw : Core.t => string => array(_any) => string = "raw";
let toString = (ParamBuilder(knex, expr, bindings)) =>
    _raw(knex, expr, bindings);

module Infix = {
    let (|?) = (pb, v) => bind(v, pb);
    let (|?.) = (pb, v) => pb |? v |> toString;
};
