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

    int: $ => choice(
      $.digit,
      seq($.nzdigit, repeat1($.digit)),
      seq(/0[xX]/, repeat1($.hex))
    ),
    float: $ => choice(
      seq(repeat1($.digit), ".", repeat($.digit)),
      seq(".", repeat1($.digit))
    ),
    length: $ => seq(
      choice($.digit, seq($.nzdigit, repeat1($.digit)), $.float),
      choice("pt", "mm", "cm", "inch")
    ),

    comment: $ => /%.*/
  }
});
