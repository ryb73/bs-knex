type t = KnexTypes.knex(unit);
[@bs.val] external make: t = "this";

include AbstractExpression.Make({ type nonrec t = t }, {
    type nonrec t('a) = t;
    let getCore = (v) => v;
    let setCore = (_, v) => v;
    let finish = getCore;
});
