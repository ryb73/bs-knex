module type Builder = {
    type t('resultType);
    let getCore: t('a) => KnexTypes.knex(unit);
    let setCore: (t('a), KnexTypes.knex(unit)) => t('a);
    let finish: t('a) => KnexTypes.knex(unit);
};
