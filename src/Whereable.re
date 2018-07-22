module type Builder = {
    type t;
    let toCore: t => Core.t;
    let setCoreResult: t => Core.t => t;
};

module MakeGenericExpr = (Expression: { type t }, M: Builder) => {
    [@bs.send.pipe: Core.t]
    external _where : string => Core.t = "whereRaw";
    let where = (s, builder) =>
        M.toCore(builder)
            |> _where(s)
            |> M.setCoreResult(builder);

    [@bs.send.pipe: Core.t]
    external _whereParam : (string, Params.t) => Core.t = "whereRaw";
    let whereParam = (s, p, builder) =>
        M.toCore(builder)
            |> _whereParam(s, p)
            |> M.setCoreResult(builder);

    [@bs.send.pipe: Core.t]
    external _orWhere : string => Core.t = "orWhereRaw";
    let orWhere = (s, builder) =>
        M.toCore(builder)
            |> _orWhere(s)
            |> M.setCoreResult(builder);

    [@bs.send.pipe: Core.t]
    external _orWhereParam : (string, Params.t) => Core.t = "orWhereRaw";
    let orWhereParam = (s, p, builder) =>
        M.toCore(builder)
            |> _orWhereParam(s, p)
            |> M.setCoreResult(builder);

    [@bs.send.pipe: Core.t]
    external _whereEx : (unit => Expression.t) => Core.t = "where";
    let whereEx = (f, builder) =>
        M.toCore(builder)
            |> _whereEx(f)
            |> M.setCoreResult(builder);

    [@bs.send.pipe: Core.t]
    external _orWhereEx : (unit => Expression.t) => Core.t = "orWhere";
    let orWhereEx = (f, builder) =>
        M.toCore(builder)
            |> _orWhereEx(f)
            |> M.setCoreResult(builder);
};

module Expression = {
    type t = Core.t;
    [@bs.val] external make : t = "this";

    include MakeGenericExpr({ type nonrec t = t }, {
        type nonrec t = t;
        let toCore = (v) => v;
        let setCoreResult = (_, v) => v;
    });
};

module Make = MakeGenericExpr(Expression);