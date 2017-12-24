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

const std::shared_ptr<symbol_attribute> &symbol_attribute::get_same_sym_outer_scope() const {
    return same_sym_outer_scope_;
}

void symbol_attribute::set_same_sym_outer_scope(const std::shared_ptr<symbol_attribute> &same_sym_outer_scope_) {
    symbol_attribute::same_sym_outer_scope_ = same_sym_outer_scope_;
}



unsigned int symbol_attribute::get_depth() const {
    return depth_;
}

void symbol_attribute::set_depth(unsigned int depth_) {
    symbol_attribute::depth_ = depth_;
}

const std::string &symbol_attribute::get_name() const {
    return name_;
}

void symbol_attribute::set_name(const std::string &name_) {
    symbol_attribute::name_ = name_;
}

function::Return_type symbol_attribute::get_return_type() const {
    return return_type_;
}

void symbol_attribute::set_return_type(function::Return_type return_type) {
    symbol_attribute::return_type_ = return_type;
}

int symbol_attribute::get_func_size() const {
    return func_size_;
}

void symbol_attribute::set_func_size(int space_size) {
    symbol_attribute::func_size_ = space_size;
}

int symbol_attribute::get_var_pos() const {
    return var_pos_;
}

void symbol_attribute::set_var_pos(int var_pos_) {
    symbol_attribute::var_pos_ = var_pos_;
}

