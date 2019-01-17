module type Builder = {
    type t;
    type result;
    let getCore: t => Core.t;
    let setCore: t => Core.t => t;
    let finish: t => Core.t;
};
