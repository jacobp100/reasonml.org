

import * as Util from "../common/Util.bs.js";
import * as React from "react";
import * as Head from "next/head";

var ogImgDefault = "https://res.cloudinary.com/dmm9n7v9f/image/upload/v1588077512/Reason%20Association/reasonml.org/reasonml-org-social-default_re6vor.jpg";

function Meta(Props) {
  var $staropt$star = Props.siteName;
  var $staropt$star$1 = Props.keywords;
  var $staropt$star$2 = Props.description;
  var canonical = Props.canonical;
  var title = Props.title;
  var $staropt$star$3 = Props.ogLocale;
  var ogSiteName = Props.ogSiteName;
  var $staropt$star$4 = Props.ogDescription;
  var ogTitle = Props.ogTitle;
  var $staropt$star$5 = Props.ogImage;
  var siteName = $staropt$star !== undefined ? $staropt$star : "Reason Documentation";
  var keywords = $staropt$star$1 !== undefined ? $staropt$star$1 : [];
  var description = $staropt$star$2 !== undefined ? $staropt$star$2 : "The Reason language and ecosystem docs";
  var ogLocale = $staropt$star$3 !== undefined ? $staropt$star$3 : "en_US";
  var ogDescription = $staropt$star$4 !== undefined ? $staropt$star$4 : description;
  var ogImage = $staropt$star$5 !== undefined ? $staropt$star$5 : ogImgDefault;
  var title$1;
  if (title !== undefined) {
    var title$2 = title;
    title$1 = title$2 === "" ? siteName : title$2;
  } else {
    title$1 = siteName;
  }
  var ogSiteName$1 = ogSiteName !== undefined ? ogSiteName : siteName;
  var ogTitle$1 = ogTitle !== undefined ? ogTitle : title$1;
  return React.createElement(Head.default, {
              children: null
            }, React.createElement("title", {
                  key: "title"
                }, Util.ReactStuff.s(title$1)), React.createElement("meta", {
                  charSet: "utf-8"
                }), React.createElement("meta", {
                  content: "width=device-width, initial-scale=1, minimum-scale=1, maximum-scale=1, minimal-ui",
                  name: "viewport"
                }), React.createElement("meta", {
                  key: "description",
                  content: description,
                  name: "description"
                }), React.createElement("meta", {
                  key: "keywords",
                  content: keywords.join(","),
                  name: "keywords"
                }), canonical !== undefined ? React.createElement("link", {
                    key: "canonical",
                    href: canonical,
                    rel: "canonical"
                  }) : null, React.createElement("link", {
                  key: "icon",
                  href: "/static/favicon.ico",
                  rel: "icon",
                  sizes: "16x16 32x32 64x64"
                }), React.createElement("meta", {
                  key: "og:site_name",
                  content: ogSiteName$1,
                  property: "og:site_name"
                }), React.createElement("meta", {
                  key: "og:locale",
                  content: ogLocale,
                  property: "og:locale"
                }), React.createElement("meta", {
                  key: "og:title",
                  content: ogTitle$1,
                  property: "og:title"
                }), React.createElement("meta", {
                  key: "og:description",
                  content: ogDescription,
                  property: "og:description"
                }), React.createElement("meta", {
                  key: "og:image",
                  content: ogImage,
                  property: "og:image"
                }), React.createElement("meta", {
                  key: "twitter:title",
                  content: title$1,
                  name: "twitter:title"
                }), React.createElement("meta", {
                  key: "twitter:description",
                  content: description,
                  name: "twitter:description"
                }), React.createElement("meta", {
                  key: "twitter:site",
                  content: "@reasonml",
                  name: "twitter:site"
                }), React.createElement("meta", {
                  key: "twitter:creator",
                  content: "@ReasonAssoc",
                  name: "twitter:creator"
                }), React.createElement("meta", {
                  content: "image/jpeg",
                  property: "og:image:type"
                }), React.createElement("meta", {
                  key: "twitter:card",
                  content: "summary_large_image",
                  name: "twitter:card"
                }), React.createElement("meta", {
                  key: "twitter:image",
                  content: ogImage,
                  property: "twitter:image"
                }));
}

var Head$1 = /* alias */0;

var make = Meta;

export {
  Head$1 as Head,
  ogImgDefault ,
  make ,
  
}
/* react Not a pure module */
