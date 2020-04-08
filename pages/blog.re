/*
 TODO: The way the blog works right now is very rough.
 We don't do any webpack magic to extract content, title preview or frontmatter, and
 don't do any pagination... for now it's not really needed I guess, it would
 still be good to rethink the ways the blog works in a later point of time.

 Docusaurus does a lot of webpack / remark magic in that regard. For my taste,
 it does too much, but here's a link to draw some inspiration from:

 https://github.com/facebook/docusaurus/tree/master/packages/docusaurus-plugin-content-blog/src

 Features like RSS feed etc might be nice, but I guess it's not a core feature
 we need right away.
 */

open Util.ReactStuff;

module Link = Next.Link;

module BlogCard = {
  [@react.component]
  let make =
      (
        ~previewImg: option(string)=?,
        ~title: string="Unknown Title",
        ~author: BlogFrontmatter.Author.t,
        ~tags: array(string)=[||],
        ~date: Js.Date.t,
        ~slug: string,
      ) => {
    <section className="h-full">
      <div>
        <Link href="/blog/[slug]" _as={"/blog/" ++ slug}>
          <a>
            {switch (previewImg) {
             | Some(src) => <img className="mb-4" src />
             | None => React.null
             }}
          </a>
        </Link>
        <Link href="/blog/[slug]" _as={"/blog/" ++ slug}>
          <a>
            <h2 className="inline-block text-night-dark text-2xl">
              title->s
            </h2>
          </a>
        </Link>
      </div>
      <div className="text-night-light text-sm">
        {switch (author.social->Js.Null.toOption) {
         | Some(social) =>
           let href =
             BlogFrontmatter.Author.socialUrl(social)
             ++ "/"
             ++ author.username;
           <a
             href
             className="hover:text-night"
             rel="noopener noreferrer"
             target="_blank">
             author.username->s
           </a>;
         | None => author.username->s
         }}
        {j| · |j}->s
        {date->Util.Date.toDayMonthYear->s}
      </div>
    </section>;
  };
};

module FeatureCard = {
  [@react.component]
  let make =
      (
        ~previewImg: option(string)=?,
        ~title: string="Unknown Title",
        ~author: BlogFrontmatter.Author.t,
        ~date: Js.Date.t,
        ~firstParagraph: string="",
        ~slug: string,
      ) => {
    <section className="flex h-full">
      <div className="w-1/2 h-full">
        <Link href="/blog/[slug]" _as={"/blog/" ++ slug}>
          <a>
            {switch (previewImg) {
             | Some(src) => <img className="h-full w-full object-cover" src />
             | None => <div className="bg-night-light" />
             }}
          </a>
        </Link>
      </div>
      <div className="w-1/2 mt-8 ml-16">
        <h2 className="text-night-dark font-semibold text-6xl"> title->s </h2>
        <div className="mb-4">
          <p className="text-night-dark text-lg"> firstParagraph->s </p>
          <div className="text-night-light text-sm mt-2 mb-8">
            "by "->s
            {switch (author.social->Js.Null.toOption) {
             | Some(social) =>
               let href =
                 BlogFrontmatter.Author.socialUrl(social)
                 ++ "/"
                 ++ author.username;
               <a
                 className="hover:text-night"
                 href
                 rel="noopener noreferrer"
                 target="_blank">
                 author.username->s
               </a>;
             | None => author.username->s
             }}
            {j| · |j}->s
            {date->Util.Date.toDayMonthYear->s}
          </div>
        </div>
        <Link href="/blog/[slug]" _as={"/blog/" ++ slug}>
          <a> <Button> "Read Article"->s </Button> </a>
        </Link>
      </div>
    </section>;
  };
};

type params = {slug: string};

module Post = {
  type t = {
    id: string,
    frontmatter: BlogFrontmatter.t,
  };

  let orderByDate = (posts: array(t)): array(t) => {
    posts
    ->Js.Array.copy
    ->Js.Array2.sortInPlaceWith((a, b) => {
        let aV = a.frontmatter.date->DateStr.toDate->Js.Date.valueOf;
        let bV = b.frontmatter.date->DateStr.toDate->Js.Date.valueOf;
        if (aV === bV) {
          0;
        } else if (aV > bV) {
          (-1);
        } else {
          1;
        };
      });
  };
};

module Malformed = {
  type t = {
    id: string,
    message: string,
  };
};

type props = {
  posts: array(Post.t),
  malformed: array(Malformed.t),
};

let default = (props: props): React.element => {
  let {posts, malformed} = props;

  let errorBox =
    if (ProcessEnv.env === ProcessEnv.development
        && Belt.Array.length(malformed) > 0) {
      <div className="mb-12">
        <Markdown.Warn>
          <h2 className="font-bold text-night-dark text-2xl mb-2">
            "Some Blog Posts are Malformed!"->s
          </h2>
          <p>
            "Any blog post with invalid data will not be displayed in production."
            ->s
          </p>
          <div>
            <p className="font-bold mt-4"> "Errors:"->s </p>
            <ul>
              {Belt.Array.map(malformed, m => {
                 <li className="list-disc ml-5">
                   {("pages/blog/" ++ m.id ++ ".mdx: " ++ m.message)->s}
                 </li>
               })
               ->ate}
            </ul>
          </div>
        </Markdown.Warn>
      </div>;
    } else {
      React.null;
    };

  let content =
    if (Belt.Array.length(posts) === 0) {
      <div> "Currently no posts available"->s </div>;
    } else {
      let first = Belt.Array.getExn(posts, 0);
      let rest = Js.Array2.sliceFrom(posts, 1);

      <div
        className="grid grid-cols-1 xs:grid-cols-3 gap-20 row-gap-40 w-full">
        <div className="col-span-3 row-span-3">
          <FeatureCard
            previewImg=?{first.frontmatter.previewImg->Js.Null.toOption}
            title={first.frontmatter.title}
            author={first.frontmatter.author}
            firstParagraph=?{first.frontmatter.description->Js.Null.toOption}
            date={first.frontmatter.date->DateStr.toDate}
            slug={first.id}
          />
        </div>
        {Belt.Array.mapWithIndex(rest, (i, post) => {
           <BlogCard
             key={post.id ++ Belt.Int.toString(i)}
             previewImg=?{post.frontmatter.previewImg->Js.Null.toOption}
             title={post.frontmatter.title}
             author={post.frontmatter.author}
             date={post.frontmatter.date->DateStr.toDate}
             slug={post.id}
           />
         })
         ->ate}
      </div>;
    };

  <div> errorBox content </div>;
};

let getStaticProps: Next.GetStaticProps.t(props, params) =
  _ctx => {
    let (posts, malformed) =
      BlogApi.getAllPosts()
      ->Belt.Array.reduce(
          ([||], [||]),
          (acc, postData) => {
            let (posts, malformed) = acc;
            let id = postData.slug;

            let decoded = BlogFrontmatter.decode(postData.frontmatter);

            switch (decoded) {
            | Error(message) =>
              let m = {Malformed.id, message};
              let malformed = Belt.Array.concat(malformed, [|m|]);
              (posts, malformed);
            | Ok(frontmatter) =>
              let p = {Post.id, frontmatter};
              let posts = Belt.Array.concat(posts, [|p|]);
              (posts, malformed);
            };
          },
        );

    let props = {posts: Post.orderByDate(posts), malformed};

    Promise.resolved({"props": props});
  };