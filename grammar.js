module.exports = grammar({
  name: "satysfi",

  extras: $ => [$.comment, /\s/],

  rules: {
    identifier: $ => /[a-z][-a-zA-Z0-9]*/,

    comment: $ => /%.*/
  }
});
