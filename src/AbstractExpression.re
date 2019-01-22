module Make = (Expression: { type t }, M: Builder.Builder) => {
    let helper = (f, builder) =>
        M.getCore(builder)
        |> f
        |> M.setCore(builder);

    [@bs.send.pipe: KnexTypes.knex(_)]
    external where : string => KnexTypes.knex(_) = "whereRaw";
    let where = (s) => helper(where(s));

    [@bs.send.pipe: KnexTypes.knex(_)]
    external whereParam : (string, Params.t) => KnexTypes.knex(_) = "whereRaw";
    let whereParam = (s, p) => helper(whereParam(s, p));

    [@bs.send.pipe: KnexTypes.knex(_)]
    external whereIn : (string, array(_)) => KnexTypes.knex(_) = "whereIn";
    let whereIn = (s, a) => helper(whereIn(s, a));

    [@bs.send.pipe: KnexTypes.knex(_)]
    external orWhere : string => KnexTypes.knex(_) = "orWhereRaw";
    let orWhere = (s) => helper(orWhere(s));

    [@bs.send.pipe: KnexTypes.knex(_)]
    external orWhereParam : (string, Params.t) => KnexTypes.knex(_) = "orWhereRaw";
    let orWhereParam = (s, p) => helper(orWhereParam(s, p));

    [@bs.send.pipe: KnexTypes.knex(_)]
    external whereEx : (unit => Expression.t) => KnexTypes.knex(_) = "where";
    let whereEx = (f) => helper(whereEx(f));

    [@bs.send.pipe: KnexTypes.knex(_)]
    external orWhereEx : (unit => Expression.t) => KnexTypes.knex(_) = "orWhere";
    let orWhereEx = (f) => helper(orWhereEx(f));
};