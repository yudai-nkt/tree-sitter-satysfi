#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 6
#define STATE_COUNT 4
#define SYMBOL_COUNT 5
#define ALIAS_COUNT 0
#define TOKEN_COUNT 4
#define EXTERNAL_TOKEN_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 0

enum {
  aux_sym_SLASH_LBRACK_BSLASHt_RBRACK_SLASH = 1,
  sym_mathsymbol = 2,
  sym_comment = 3,
  sym_space = 4,
};

static const char *ts_symbol_names[] = {
  [ts_builtin_sym_end] = "END",
  [aux_sym_SLASH_LBRACK_BSLASHt_RBRACK_SLASH] = "/[ \\t]/",
  [sym_mathsymbol] = "mathsymbol",
  [sym_comment] = "comment",
  [sym_space] = "space",
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_SLASH_LBRACK_BSLASHt_RBRACK_SLASH] = {
    .visible = false,
    .named = false,
  },
  [sym_mathsymbol] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_space] = {
    .visible = true,
    .named = true,
  },
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  switch (state) {
    case 0:
      if (lookahead == 0)
        ADVANCE(1);
      if (lookahead == '%')
        ADVANCE(2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ')
        SKIP(0);
      if (lookahead == '\'' ||
          ('*' <= lookahead && lookahead <= '/') ||
          lookahead == ':' ||
          ('<' <= lookahead && lookahead <= '?') ||
          lookahead == '`' ||
          lookahead == '~')
        ADVANCE(3);
      END_STATE();
    case 1:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 2:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n')
        ADVANCE(2);
      END_STATE();
    case 3:
      ACCEPT_TOKEN(sym_mathsymbol);
      END_STATE();
    case 4:
      if (lookahead == '%')
        ADVANCE(2);
      if (lookahead == '\t' ||
          lookahead == ' ')
        ADVANCE(5);
      if (lookahead == '\n' ||
          lookahead == '\r')
        SKIP(4);
      END_STATE();
    case 5:
      ACCEPT_TOKEN(aux_sym_SLASH_LBRACK_BSLASHt_RBRACK_SLASH);
      END_STATE();
    case 6:
      if (lookahead == 0)
        ADVANCE(1);
      if (lookahead == '%')
        ADVANCE(2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ')
        SKIP(6);
      END_STATE();
    default:
      return false;
  }
}

static TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 4},
  [2] = {.lex_state = 6},
  [3] = {.lex_state = 6},
};

static uint16_t ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_mathsymbol] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_space] = STATE(3),
    [aux_sym_SLASH_LBRACK_BSLASHt_RBRACK_SLASH] = ACTIONS(6),
    [sym_comment] = ACTIONS(8),
  },
  [2] = {
    [ts_builtin_sym_end] = ACTIONS(10),
    [sym_comment] = ACTIONS(12),
  },
  [3] = {
    [ts_builtin_sym_end] = ACTIONS(14),
    [sym_comment] = ACTIONS(12),
  },
};

static TSParseActionEntry ts_parse_actions[] = {
  [0] = {.count = 0, .reusable = false, .depends_on_lookahead = false},
  [1] = {.count = 1, .reusable = true, .depends_on_lookahead = false}, RECOVER(),
  [3] = {.count = 2, .reusable = true, .depends_on_lookahead = true}, SHIFT_EXTRA(), RECOVER(),
  [6] = {.count = 1, .reusable = false, .depends_on_lookahead = false}, SHIFT(2),
  [8] = {.count = 1, .reusable = false, .depends_on_lookahead = false}, SHIFT_EXTRA(),
  [10] = {.count = 1, .reusable = true, .depends_on_lookahead = false}, REDUCE(sym_space, 1),
  [12] = {.count = 1, .reusable = true, .depends_on_lookahead = true}, SHIFT_EXTRA(),
  [14] = {.count = 1, .reusable = true, .depends_on_lookahead = false}, ACCEPT_INPUT(),
};

#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_satysfi() {
  static TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .symbol_metadata = ts_symbol_metadata,
    .parse_table = (const unsigned short *)ts_parse_table,
    .parse_actions = ts_parse_actions,
    .lex_modes = ts_lex_modes,
    .symbol_names = ts_symbol_names,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .lex_fn = ts_lex,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
  };
  return &language;
}
