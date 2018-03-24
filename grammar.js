module.exports = grammar({
  name: "satysfi",

  extras: $ => [$.comment, /\s/],

  rules: {
    space: $ => /[ \t]/,
    break: $ => /[\n\r]/,
    nonbreak: $ => /[^\n\r]/,
    nzdigit: $ => /[1-9]/,
    digit: $ => choice("0", $.nzdigit),
    hex: $ => choice($.digit, /[A-F]/),
    capital: $ => /[A-Z]/,
    small: $ => /[a-z]/,
    latin: $ => choice($.small, $.capital),
    item: $ => repeat1("*"),

    identifier: $ => seq($.small, repeat($.digit, $.latin, "-")),
    constructor: $ => seq($.capital, repeat($.digit, $.latin, "-")),
    symbol: $ => choice(/[ -@]/, /[[-`]/, /[{-~]/),
    opsymbol: $ => /[-+*/^&|!:=<>~'.?]/,
    str: $ => /[^ \t\n\r@`\\{}<>%|*$#;]/,
    mathsymbol: $ => /[-+*/:=<>~'.,?`]/,

    comment: $ => /%.*/
  }
});
