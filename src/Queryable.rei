module Make: (B: Builder.Builder) => {
    let toString: B.t(_) => string;
    let execute: B.t('a) => Reduice.Promise.t('a);
};
