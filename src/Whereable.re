type t('builder);

[@bs.send.pipe: t('builder)]
external where : string => t('builder) = "whereRaw";

[@bs.send.pipe: t('builder)]
external whereParam : (string, Params.t) => t('builder) = "whereRaw";

[@bs.send.pipe: t('builder)]
external orWhere : string => t('builder) = "orWhereRaw";

[@bs.send.pipe: t('builder)]
external orWhereParam : (string, Params.t) => t('builder) = "orWhereRaw";

module Expression = {
    type _t;
    type nonrec t = t(_t);
    [@bs.val] external make : t = "this";
};

[@bs.send.pipe: t('builder)]
external whereEx : (unit => Expression.t) => t('builder) = "where";

[@bs.send.pipe: t('builder)]
external orWhereEx : (unit => Expression.t) => t('builder) = "orWhere";