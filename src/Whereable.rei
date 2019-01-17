module Make: (M : Builder.Builder) => {
    let where: (string, M.t) => M.t;
    let whereParam: (string, Params.t, M.t) => M.t;
    let orWhere: (string, M.t) => M.t;
    let orWhereParam: (string, Params.t, M.t) => M.t;
    let whereEx: (unit => Expression.t, M.t) => M.t;
    let orWhereEx: (unit => Expression.t, M.t) => M.t;
};
