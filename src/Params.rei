type t;
let make: 'a => t;
let bind: ('a, t) => t;

module Infix: {
    let ( ?? ): 'a => t;
    let ( |? ): (t, 'a) => t;
};
