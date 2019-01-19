module Make = (Expression: { type t }, M: Builder.Builder) => {
    [@bs.send.pipe: Core.t(_)]
    external where : string => Core.t(_) = "whereRaw";
    let where = (s, builder) =>
        M.getCore(builder)
        |> where(s)
        |> M.setCore(builder);

    [@bs.send.pipe: Core.t(_)]
    external whereParam : (string, Params.t) => Core.t(_) = "whereRaw";
    let whereParam = (s, p, builder) =>
        M.getCore(builder)
        |> whereParam(s, p)
        |> M.setCore(builder);

    [@bs.send.pipe: Core.t(_)]
    external orWhere : string => Core.t(_) = "orWhereRaw";
    let orWhere = (s, builder) =>
        M.getCore(builder)
        |> orWhere(s)
        |> M.setCore(builder);

    [@bs.send.pipe: Core.t(_)]
    external orWhereParam : (string, Params.t) => Core.t(_) = "orWhereRaw";
    let orWhereParam = (s, p, builder) =>
        M.getCore(builder)
        |> orWhereParam(s, p)
        |> M.setCore(builder);

    [@bs.send.pipe: Core.t(_)]
    external whereEx : (unit => Expression.t) => Core.t(_) = "where";
    let whereEx = (f, builder) =>
        M.getCore(builder)
        |> whereEx(f)
        |> M.setCore(builder);

    [@bs.send.pipe: Core.t(_)]
    external orWhereEx : (unit => Expression.t) => Core.t(_) = "orWhere";
    let orWhereEx = (f, builder) =>
        M.getCore(builder)
        |> orWhereEx(f)
        |> M.setCore(builder);
};