type t = Core.t;

[@bs.send] external make : Core.t => t = "select";

[@bs.send.pipe: t] external columnAlias : Js.Dict.t(string) => t = "column";
[@bs.send.pipe: t] external column : string => t = "column";
let column = (~alias=?, name) =>
    switch alias {
        | Some(alias) => columnAlias(Js.Dict.fromArray([| (alias, name) |]))
        | _ => column(name)
    };

[@bs.send.pipe: t] external count : string => t = "";
[@bs.send.pipe: t] external countDistinct : string => t = "";

[@bs.send.pipe: t] external fromAlias : Js.Dict.t(string) => t = "from";
[@bs.send.pipe: t] external from : string => t = "from";
let from = (~alias=?, table) =>
    switch alias {
        | Some(alias) => fromAlias(Js.Dict.fromArray([| (alias, table) |]))
        | _ => from(table)
    };

[@bs.send.pipe: t] external innerJoin : string => string => string => string => t = "";

[@bs.send.pipe: t] external groupBy : string => t = "";


type order = Ascending | Descending;
[@bs.send.pipe: t] external orderBy : string => string => t = "orderBy";
let orderBy = (column, order, select) => {
    switch order {
        | Ascending => "asc"
        | Descending => "desc"
    }
    |> orderBy(column, _, select)
};

module Builder = {
    type nonrec t = t;
    type result = array(Js.Json.t);
    let getCore = (v) => v;
    let setCore = (_, v) => v;
    let finish = getCore;
};

include Queryable.Make(Builder);
include Whereable.Make(Builder);
