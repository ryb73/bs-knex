module Make: (B: Builder.Builder) => {
    let toString: B.t(_) => string;
    let execute: B.t('a) => Js.Promise.t('a);
};
