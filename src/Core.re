type _opts;
[@bs.obj] external _opts : (~client: string) => _opts = "";

type t;
[@bs.module] external _make : _opts => t = "knex";
let make = (client) => _make(_opts(~client));

type builder('a, 'b);
