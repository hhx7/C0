//
// Created by pi on 17-12-10.
//

#ifndef C0_SYMBOL_TABLE_ITEM_H
#define C0_SYMBOL_TABLE_ITEM_H

#include "../constants/symbol.h"
#include "../constants/function.h"
#include <memory>
#include <variant>
#include <any>
class symbol_attribute : virtual public symbol ,virtual public function{
public:
    template <typename AttributeType=void>
    symbol_attribute(Symbol_type symbol_type=Symbol_type ::nul,AttributeType attribute= nullptr){
        symbol_type_=symbol_type;
        attribute_=attribute;
    }

    symbol_attribute(const std::string name,Symbol_type symbol_type=Symbol_type ::nul)
            :name_(name),symbol_type_(symbol_type),return_type_(Return_type::void_type),depth_(0),func_size_(0){}

    symbol_attribute(const std::string name,Symbol_type symbol_type,Return_type return_type)
            :name_(name),symbol_type_(symbol_type),return_type_(return_type),depth_(0),func_size_(0){}

    symbol_attribute(const symbol_attribute&);

    Symbol_type get_symbol_type()const;
    std::any get_attribute()const;

    const std::shared_ptr<symbol_attribute> &get_same_sym_outer_scope() const;

    void set_same_sym_outer_scope(const std::shared_ptr<symbol_attribute> &same_sym_outer_scope);

    unsigned int get_depth() const;

    void set_depth(unsigned int depth_);

    const std::string &get_name() const;

    void set_name(const std::string &name);

    Return_type get_return_type() const;

    void set_return_type(Return_type return_type);

    int get_func_size() const;

    void set_func_size(int space_size);

    int get_var_pos() const;

    void set_var_pos(int var_pos);

private:

    std::string name_;
    Symbol_type symbol_type_;
    unsigned depth_;
    Return_type return_type_;
    int func_size_;
    int var_pos_;
    std::shared_ptr<symbol_attribute> same_sym_outer_scope_;
private:

    std::any attribute_;
};
#endif //C0_SYMBOL_TABLE_ITEM_H
