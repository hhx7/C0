//
// Created by pi on 17-11-21.
//

#ifndef C0_SYMBOL_TABLE_H
#define C0_SYMBOL_TABLE_H

#include "symbol_attribute.h"
#include <map>
#include <tuple>

class symbol_table : virtual private symbol{

    int current_scope_;
    std::map<std::string,symbol_attribute> symbol_table_{
            {"int",symbol_attribute(Symbol_type::reserved,Token_name::intsym)},
            {"return",symbol_attribute(Symbol_type::reserved,Token_name::retsym)},
            {"if",symbol_attribute(Symbol_type::reserved,Token_name::ifsym)},
            {"else",symbol_attribute(Symbol_type::reserved,Token_name::elsesym)},
            {"while",symbol_attribute(Symbol_type::reserved,Token_name::whilesym)},
            {"scanf",symbol_attribute(Symbol_type::reserved,Token_name::scanf)},
            {"printf",symbol_attribute(Symbol_type::reserved,Token_name::printf)},
            {"void",symbol_attribute(Symbol_type::reserved,Token_name::voidsym)},
            {"main",symbol_attribute(Symbol_type::reserved,Token_name::mainsym)}
    };
    using SymbolTablePointer=std::map<std::string,symbol_attribute>::iterator;



public:
    std::pair<SymbolTablePointer,bool> insert(std::string symbol,symbol_attribute detal);
    SymbolTablePointer find(const std::string& symbol);
    SymbolTablePointer end();
    void open_scope();
    void close_scope();
    SymbolTablePointer enter_symbol(const std::string& name,symbol_attribute attribute);
    SymbolTablePointer retrieve_symbol(const std::string& name)const;
    bool declared_locally(const std::string& name)const;

};
#endif //C0_SYMBOL_TABLE_H
