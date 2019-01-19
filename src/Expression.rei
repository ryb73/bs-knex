type t = Core.t(unit);
let make: t;
let where: (string, t) => t;
let whereParam: (string, Params.t, t) => t;
let orWhere: (string, t) => t;
let orWhereParam: (string, Params.t, t) => t;
let whereEx: (unit => t, t) => t;
let orWhereEx: (unit => t, t) => t;
