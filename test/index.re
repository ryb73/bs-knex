open Params.Infix;
open PromiseEx;
open Reduice.Promise;

let knex = Core.make(~host="127.0.0.1", ~user="ryan", ~database="mopho", PostgreSQL);

Select.(
    Select.make(knex)
    |> count("blah as b")
    |> column(~alias="ha", "huh")
    |> from(~alias="t", "tbl")
    |> groupBy("ha")
    |> where("b = b")
    |> whereEx(() => { open! Expression;
        Expression.make
        |> whereParam("a = ?", ?? 9)
        |> orWhere("a > 20")
        |> orWhereEx(() => {
            Expression.make
            |> whereParam("? = ?", ?? 9 |? 10)
            |> where("10 = 11")
        })
    })
    |> innerJoin("something as st", "st.id", "=", "b.id")
    |> orderBy("theorder", Ascending)
    |> toString
    |> Js.log
);

Insert.(
    Insert.make(knex)
    |> into("tbl")
    |> set("a", "a\"'y")
    |> set("b", 99)
    |> set("bool", true)
    |> toString
    |> Js.log
);

Update.(
    Update.make("tbl", knex)
    |> set("v", 39)
    |> where("a = 9")
    |> whereParam("a = ?", ?? 10)
    |> toString
    |> Js.log
);

Delete.(
    Delete.make("tbl", knex)
    |> where("a = 9")
    |> whereParam("a = ?", ?? 10)
    |> toString
    |> Js.log
);

Insert.(
    Insert.make(knex)
    |> set("track_id", "680")
    |> set("primary_artist_id", "1214")
    |> set("album_id", "550")
    |> set("created_utc", "12-18-2019 00:00:00")
    |> into("songs")
    |> execute
    |> map(Js.log2("selected"))
    |> catch(exn => { Js.log2("err", exn); resolve(); })
    |> map(_ => Core.destroy(knex))
);
