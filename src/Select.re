type t = Core.t;

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

[@bs.send.pipe: t] external innerJoin : string => string => string => string => t = "";

[@bs.send.pipe: t] external groupBy : string => t = "";


type order = Ascending | Descending;
[@bs.send.pipe: t] external _orderBy : string => string => t = "orderBy";
let orderBy = (column, order, select) => {
    switch order {
        | Ascending => "asc"
        | Descending => "desc"
    }
    |> _orderBy(column, _, select)
};

[@bs.send.pipe: t] external toString : string = "";

include Whereable.Make({
    type nonrec t = t;
    let toCore = (v) => v;
    let setCoreResult = (_, v) => v;
});