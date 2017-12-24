//
// Created by pi on 17-12-10.
//

#ifndef C0_CODE_GENERATOR_H
#define C0_CODE_GENERATOR_H

#include "../../lexer/token.h"
#include "../instruction.h"
#include <string>
#include <vector>
#include <memory>


class code_generator : virtual private operation_code,virtual private symbol{
public:
    code_generator(symbol_table&,std::vector<instruction>&);
    unsigned int emit_instruction(Operation_code, unsigned level, unsigned addr);
    void emit_instruction(Operation_code,const std::string name);
    unsigned int emit_instruction(Operation_code);
    void record_func_pos(const std::string& name);
    void complete_instruction(unsigned code_pos);
    void complete_instruction(unsigned code_pos, unsigned right_op_num);
    unsigned int get_current_code_pos()const ;
    void print()const;
private:
    unsigned level_;
    unsigned addr_;
    unsigned current_code_pos_;
    std::vector<instruction>& codes_;
    std::map<std::string,unsigned > ident_pos_;
    symbol_table& symbol_table_;
};
#endif //C0_CODE_GENERATOR_H
