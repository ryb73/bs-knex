module type Builder = {
    type t('resultType);
    let getCore: t('a) => Core.t(unit);
    let setCore: (t('a), Core.t(unit)) => t('a);
    let finish: t('a) => Core.t(unit);
};
