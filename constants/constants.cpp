//
// Created by pi on 17-12-24.
//

#include "constants.h"

std::ostream &operator<<(std::ostream &os, const function::Return_type &type) {
    using Type=function::Return_type;
    switch (type) {
        case Type::void_type:
            os << "void_type";
            break;
        case Type::int_type:
            os << "int_type";
            break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const operation_code::Operation_code &type) {
    using Type=operation_code::Operation_code;
    switch (type) {
        case Type::LIT:
            os << "LIT";
            break;
        case Type::LOD:
            os << "LOD";
            break;
        case Type::STO:
            os << "STO";
            break;
        case Type::CAL:
            os << "CAL";
            break;
        case Type::INT:
            os << "INT";
            break;
        case Type::JMP:
            os << "JMP";
            break;
        case Type::JPC:
            os << "JPC";
            break;
        case Type::ADD:
            os << "ADD";
            break;
        case Type::SUB:
            os << "SUB";
            break;
        case Type::MUL:
            os << "MUL";
            break;
        case Type::DIV:
            os << "DIV";
            break;
        case Type::RED:
            os << "RED";
            break;
        case Type::WRT:
            os << "WRT";
            break;
        case Type::RET:
            os << "RET";
            break;
        case Type::NUL:
            os << "MUL";
            break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const symbol::Symbol_type &type) {
    using Type=symbol::Symbol_type;
    switch (type) {
        case Type::nul:
            os << "nul";
            break;
        case Type::literal:
            os << "literal";
            break;
        case Type::variable:
            os << "variable";
            break;
        case Type::function:
            os << "function";
            break;
        case Type::reserved:
            os << "reserved";
            break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const symbol::Token_name &type) {
    using Type=symbol::Token_name;
    switch (type) {
        case Type::nul:
            os << "nul";
            break;
        case Type::ident:
            os << "ident";
            break;
        case Type::number:
            os << "number";
            break;
        case Type::plus:
            os << "plus";
            break;
        case Type::minus:
            os << "minus";
            break;
        case Type::times:
            os << "times";
            break;
        case Type::slash:
            os << "slash";
            break;
        case Type::eql:
            os << "eql";
            break;
        case Type::lparen:
            os << "lparen";
            break;
        case Type::rparen:
            os << "rparen";
            break;
        case Type::comma:
            os << "comma";
            break;
        case Type::semicolon:
            os << "semicolon";
            break;
        case Type::ifsym:
            os << "ifsym";
            break;
        case Type::whilesym:
            os << "whilesym";
            break;
        case Type::printf:
            os << "printf";
            break;
        case Type::scanf:
            os << "scanf";
            break;
        case Type::retsym:
            os << "retsym";
            break;
        case Type::elsesym:
            os << "elsesym";
            break;
        case Type::lbracket:
            os << "lbracket";
            break;
        case Type::rbracket:
            os << "rbracket";
            break;
        case Type::voidsym:
            os << "voidsym";
            break;
        case Type::mainsym:
            os << "mainsym";
            break;
        case Type::intsym:
            os << "intsym";
            break;
        case Type::call:
            os << "call";
            break;
        case Type::exp:
            os << "exp";
            break;
        case Type::term:
            os << "term";
            break;
        case Type::factor:
            os << "factor";
            break;
        case Type::assign:
            os << "assign";
            break;
        case Type::loop:
            os << "loop";
            break;
        case Type::stmt:
            os << "stmt";
            break;
        case Type::stmt_seq:
            os << "stmat_seq";
            break;
        case Type::sub_proc:
            os << "sub_proc";
            break;
        case Type::func_def:
            os << "func_def";
            break;
        case Type::ident_def:
            os << "ident_def";
            break;
        case Type::proc:
            os << "proc";
            break;
        case Type::func_call_stmt:
            os << "func_call_stamt";
            break;
    }
    return os;
}