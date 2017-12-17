//
// Created by pi on 17-12-8.
//

#ifndef C0_SYMBOL_H
#define C0_SYMBOL_H

#include <map>

struct  symbol{
    enum class Token_name {
        nul,         ident,     number,     plus,      minus,
        times,       slash,     eql,        lparen,    rparen,
        comma,       semicolon, ifsym,      whilesym,  printf,

        scanf,       retsym,    elsesym,    lbracket,  rbracket,
        voidsym,     mainsym,   intsym,     call,       exp,
        term,        factor,    assign,      loop,      stmt,

        stmt_seq,   sub_proc,   func_define, ident_def, proc,
        func_call_stmt
    };
    enum class Symbol_type{
        nul,
        literal,
        variable,
        function,
        reserved
    };
};

#endif //C0_SYMBOL_H
