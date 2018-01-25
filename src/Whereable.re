type t;

[@bs.send.pipe: Core.builder('builder, t)]
external where : string => Core.builder('builder, t) = "whereRaw";

[@bs.send.pipe: Core.builder('builder, t)]
external orWhere : string => Core.builder('builder, t) = "orWhereRaw";

module Expression = {
    type _t;
    type nonrec t = Core.builder(_t, t);
    [@bs.val] external make : t = "this";
};

[@bs.send.pipe: Core.builder('builder, t)]
external whereEx : (unit => Expression.t) => Core.builder('builder, t) = "where";

[@bs.send.pipe: Core.builder('builder, t)]
external orWhereEx : (unit => Expression.t) => Core.builder('builder, t) = "orWhere";