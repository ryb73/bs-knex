type t = Core.t;
[@bs.val] external make : t = "this";

include AbstractExpression.Make({ type nonrec t = t }, {
    type nonrec t = t;
    type result = unit; /** TODO: result isn't applicable here. refactor? */
    let getCore = (v) => v;
    let setCore = (_, v) => v;
    let finish = getCore;
});
