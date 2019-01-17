module Make = (Expression: { type t }, M: Builder.Builder) => {
    [@bs.send.pipe: Core.t]
    external where : string => Core.t = "whereRaw";
    let where = (s, builder) =>
        M.getCore(builder)
        |> where(s)
        |> M.setCore(builder);

    [@bs.send.pipe: Core.t]
    external whereParam : (string, Params.t) => Core.t = "whereRaw";
    let whereParam = (s, p, builder) =>
        M.getCore(builder)
        |> whereParam(s, p)
        |> M.setCore(builder);

    [@bs.send.pipe: Core.t]
    external orWhere : string => Core.t = "orWhereRaw";
    let orWhere = (s, builder) =>
        M.getCore(builder)
        |> orWhere(s)
        |> M.setCore(builder);

    [@bs.send.pipe: Core.t]
    external orWhereParam : (string, Params.t) => Core.t = "orWhereRaw";
    let orWhereParam = (s, p, builder) =>
        M.getCore(builder)
        |> orWhereParam(s, p)
        |> M.setCore(builder);

    [@bs.send.pipe: Core.t]
    external whereEx : (unit => Expression.t) => Core.t = "where";
    let whereEx = (f, builder) =>
        M.getCore(builder)
        |> whereEx(f)
        |> M.setCore(builder);

    [@bs.send.pipe: Core.t]
    external orWhereEx : (unit => Expression.t) => Core.t = "orWhere";
    let orWhereEx = (f, builder) =>
        M.getCore(builder)
        |> orWhereEx(f)
        |> M.setCore(builder);
};