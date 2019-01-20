module Make = (Expression: { type t }, M: Builder.Builder) => {
    let helper = (f, builder) =>
        M.getCore(builder)
        |> f
        |> M.setCore(builder);

    [@bs.send.pipe: Core.t(_)]
    external where : string => Core.t(_) = "whereRaw";
    let where = (s) => helper(where(s));

    [@bs.send.pipe: Core.t(_)]
    external whereParam : (string, Params.t) => Core.t(_) = "whereRaw";
    let whereParam = (s, p) => helper(whereParam(s, p));

    [@bs.send.pipe: Core.t(_)]
    external whereIn : (string, array(_)) => Core.t(_) = "whereIn";
    let whereIn = (s, a) => helper(whereIn(s, a));

    [@bs.send.pipe: Core.t(_)]
    external orWhere : string => Core.t(_) = "orWhereRaw";
    let orWhere = (s) => helper(orWhere(s));

    [@bs.send.pipe: Core.t(_)]
    external orWhereParam : (string, Params.t) => Core.t(_) = "orWhereRaw";
    let orWhereParam = (s, p) => helper(orWhereParam(s, p));

    [@bs.send.pipe: Core.t(_)]
    external whereEx : (unit => Expression.t) => Core.t(_) = "where";
    let whereEx = (f) => helper(whereEx(f));

    [@bs.send.pipe: Core.t(_)]
    external orWhereEx : (unit => Expression.t) => Core.t(_) = "orWhere";
    let orWhereEx = (f) => helper(orWhereEx(f));
};