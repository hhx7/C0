//
// Created by pi on 17-12-10.
//

#include "symbol_attribute.h"

symbol_attribute::symbol_attribute(const symbol_attribute& symbol_detail1){
    this->symbol_type_=symbol_detail1.symbol_type_;
    this->attribute_=symbol_detail1.attribute_;
}

symbol_attribute::Symbol_type symbol_attribute::get_symbol_type()const{
    return symbol_type_;
}

std::any symbol_attribute::get_attribute()const{
    return attribute_;
}

