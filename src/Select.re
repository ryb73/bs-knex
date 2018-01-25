type _t;
type t = Whereable.t(_t);

[@bs.send] external make : Core.t => t = "select";

[@bs.send.pipe: t] external _column : string => t = "column";
[@bs.send.pipe: t] external _columnAlias : Js.Dict.t(string) => t = "column";
let column = (~alias=?, name) =>
    switch alias {
        | Some(alias) => _columnAlias(Js.Dict.fromArray([| (alias, name) |]))
        | _ => _column(name)
    };

[@bs.send.pipe: t] external count : string => t = "";
[@bs.send.pipe: t] external countDistinct : string => t = "";

[@bs.send.pipe: t] external _from : string => t = "from";
[@bs.send.pipe: t] external _fromAlias : Js.Dict.t(string) => t = "from";
let from = (~alias=?, table) =>
    switch alias {
        | Some(alias) => _fromAlias(Js.Dict.fromArray([| (alias, table) |]))
        | _ => _from(table)
    };

[@bs.send.pipe: t] external groupBy : string => t = "";

[@bs.send] external toString : t => string = "";