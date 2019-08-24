type _any;
external _any : _ => _any = "%identity";

type t = array(_any);

let make = (v) : t => [| _any(v) |];

let bind = (v, bindings) => {
    Js.Array.push(_any(v), bindings) |> ignore;
    bindings;
};

module Infix = {
    let (??) = (v) => make(v);
    let (|?) = (pb, v) => bind(v, pb);
};
