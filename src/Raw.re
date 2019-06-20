type t;

[@bs.send] external toString: t => string = "";
[@bs.send] external execute: t => Js.Promise.t(Js.Json.t) = "";
