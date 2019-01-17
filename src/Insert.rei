type t;
let make: Core.t => t;

let set: (Js.Dict.key, 'a, t) => t;
let into: (string, t) => t;

let toString: t => string;
let execute: t => Reduice.Promise.t(int);
