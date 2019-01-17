[@bs.send.pipe: Core.t] external toString : string = "";

module Make = (M: Builder.Builder) => {
    let toString = (builder) =>
        M.finish(builder)
        |> toString;

    let execute = (builder): Reduice.Promise.t(M.result) =>
        M.finish(builder)
        |> Obj.magic
        |> Reduice.Promise.resolve;
};
