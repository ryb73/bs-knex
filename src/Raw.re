type t;

[@bs.send] external toString: t => string = "";
let execute = (builder) =>
    Obj.magic(builder: t)
    |> Js.Promise.resolve;
