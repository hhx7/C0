//
// Created by pi on 17-12-10.
//
#include "code_generator.h"
void error(const char msg[]){
    throw std::runtime_error(msg);
}

void code_generator::emit_instruction(Operation_code op, std::shared_ptr<token> cur_token) {

   /* switch (op){
        case Operation_code ::CAL:
            auto symbol_entry=symbol_table_.retrieve_symbol(cur_token->attribute_);
            if(symbol_entry!= symbol_table_.end() && symbol_entry->get_kind()==symbol::Token_name::call)
                codes_.emplace_back(Operation_code::CAL,level_-symbol_entry->get_level(),symbol_entry->get_addr());
            else
                error("no exist func name");
            break;

        case :
    }*/
}

code_generator::code_generator(symbol_table st):level_(0),addr_(0),symbol_table_(st) {}
