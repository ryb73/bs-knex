module Make:
    (Expression : { type t; }) => (M : Builder.Builder) => {
        let where: (string, M.t('a)) => M.t('a);
        let whereParam: (string, Params.t, M.t('a)) => M.t('a);
        let whereIn: (string, array(_), M.t('a)) => M.t('a);
        let orWhere: (string, M.t('a)) => M.t('a);
        let orWhereParam: (string, Params.t, M.t('a)) => M.t('a);
        let whereEx: (unit => Expression.t, M.t('a)) => M.t('a);
        let orWhereEx: (unit => Expression.t, M.t('a)) => M.t('a);
      };
