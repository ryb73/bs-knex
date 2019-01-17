module Make: (B: Builder.Builder) => {
    let toString: B.t => string;
    let execute: B.t => Reduice.Promise.t(B.result);
};
