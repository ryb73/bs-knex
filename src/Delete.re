type t = Core.t;

type _f = [@bs] string => Core.t;
external _asFunc : Core.t => _f = "%identity";
[@bs.send] external _del : Core.t => t = "del";
let make = (table, knex) => {
    let f = _asFunc(knex);
    _del([@bs] f(table));
};

[@bs.send.pipe: t] external toString : string = "";

include Whereable.Make({
    type nonrec t = t;
    let toCore = (v) => v;
    let setCoreResult = (_, v) => v;
});
