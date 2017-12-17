//
// Created by pi on 17-12-10.
//
#include "symbol_table.h"

std::pair<symbol_table::SymbolTablePointer,bool> symbol_table::insert(std::string symbol,symbol_attribute detail){
    symbol_attribute x(Symbol_type::reserved,Token_name::intsym);
    return  symbol_table_.insert({symbol,detail});
}

symbol_table::SymbolTablePointer symbol_table::find(const std::string& symbol){
    return symbol_table_.find(symbol);
}
symbol_table::SymbolTablePointer symbol_table::end(){
    return symbol_table_.end();
}
