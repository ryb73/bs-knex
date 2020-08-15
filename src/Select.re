type t('a) = KnexTypes.knex(unit);

[@bs.send] external make : KnexTypes.knex(('a, _, _, _)) => t('a) = "select";

[@bs.send.pipe: t('a)] external columnAlias : Js.Dict.t(string) => t('a) = "column";
[@bs.send.pipe: t('a)] external column : string => t('a) = "column";
let column = (~alias=?, name) =>
    switch alias {
        | Some(alias) => columnAlias(Js.Dict.fromArray([| (alias, name) |]))
        | _ => column(name)
    };

[@bs.send.pipe: t('a)] external count : string => t('a) = "";
[@bs.send.pipe: t('a)] external countDistinct : string => t('a) = "";

[@bs.send.pipe: t('a)] external fromAlias : Js.Dict.t(string) => t('a) = "from";
[@bs.send.pipe: t('a)] external from : string => t('a) = "from";
let from = (~alias=?, table) =>
    switch alias {
        | Some(alias) => fromAlias(Js.Dict.fromArray([| (alias, table) |]))
        | _ => from(table)
    };

[@bs.send.pipe: t('a)] external limit: int => t('a) = "";

[@bs.send.pipe: t('a)] external innerJoin : string => string => string => string => t('a) = "";
[@bs.send.pipe: t('a)] external leftJoin : string => string => string => string => t('a) = "";
[@bs.send.pipe: t('a)] external leftOuterJoin : string => string => string => string => t('a) = "";
[@bs.send.pipe: t('a)] external rightJoin : string => string => string => string => t('a) = "";
[@bs.send.pipe: t('a)] external rightOuterJoin : string => string => string => string => t('a) = "";
[@bs.send.pipe: t('a)] external fullOuterJoin : string => string => string => string => t('a) = "";
[@bs.send.pipe: t('a)] external joinRaw : string => t('a) = "";

[@bs.send.pipe: t('a)] external groupBy : string => t('a) = "";

type order = Ascending | Descending;
[@bs.send.pipe: t('a)] external orderBy : string => string => t('a) = "orderBy";
let orderBy = (column, order, select) => {
    switch order {
        | Ascending => "asc"
        | Descending => "desc"
    }
    |> orderBy(column, _, select)
};

[@bs.send] external forUpdate: t('a) => t('a) = "";

module Builder = {
    type nonrec t('a) = t('a);
    let getCore = (v) => v;
    let setCore = (_, v) => v;
    let finish = getCore;
};

include Queryable.Make(Builder);
include Whereable.Make(Builder);
