type t = Core.t;

type f = [@bs] string => Core.t;
external asFunc : Core.t => f = "%identity";
[@bs.send] external del : Core.t => t = "del";
let make = (table, knex) => {
    let f = asFunc(knex);
    del([@bs] f(table));
};

module Builder = {
    type nonrec t = t;
    type result = int;
    let getCore = (v) => v;
    let setCore = (_, v) => v;
    let finish = getCore;
};

include Queryable.Make(Builder);
include Whereable.Make(Builder);
