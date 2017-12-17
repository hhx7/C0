//
// Created by pi on 17-12-10.
//

#ifndef C0_CODE_GENERATOR_H
#define C0_CODE_GENERATOR_H

#include <string>
#include <vector>
#include <memory>
#include "../../constants/operation_code.h"
#include "../../lexer/token.h"
#include "../instruction.h"

class code_generator : virtual private operation_code{
public:
    code_generator(symbol_table st);
    void emit_instruction(Operation_code,std::shared_ptr<token>);

private:
    unsigned level_;
    unsigned addr_;
    symbol_table symbol_table_;
    std::vector<instruction> codes_;
};
#endif //C0_CODE_GENERATOR_H
