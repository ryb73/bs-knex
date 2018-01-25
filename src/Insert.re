type _any;
external _any : _ => _any = "%identity";

type t = Js.Dict.t(_any);

[@bs.send.pipe: Core.t] external _make : Js.Dict.t(_) => t = "insert";
let make = () : t => Js.Dict.empty();

[@bs.send.pipe: t] external into : string => t = "";
