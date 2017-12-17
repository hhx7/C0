//
// Created by pi on 17-12-10.
//

#ifndef C0_SYMBOL_TABLE_ITEM_H
#define C0_SYMBOL_TABLE_ITEM_H

#include "../constants/symbol.h"
#include <variant>
#include <any>
class symbol_attribute : virtual public symbol {
public:
    template <typename AttributeType=void>
    symbol_attribute(Symbol_type symbol_type=Symbol_type ::nul,AttributeType attribute= nullptr){
        symbol_type_=symbol_type;

        attribute_=attribute;

    }
    symbol_attribute(const symbol_attribute&);

    Symbol_type get_symbol_type()const;
    std::any get_attribute()const;

private:
    Symbol_type symbol_type_;
    std::any attribute_;
};
#endif //C0_SYMBOL_TABLE_ITEM_H
