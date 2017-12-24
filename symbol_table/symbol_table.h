//
// Created by pi on 17-11-21.
//

#ifndef C0_SYMBOL_TABLE_H
#define C0_SYMBOL_TABLE_H

#include "symbol_attribute.h"
#include <map>
#include <tuple>
#include <vector>
#include <list>

class symbol_table : virtual private symbol,virtual public function{

public:

    symbol_table();
    void open_scope();
    void close_scope();
    unsigned int get_depth() const;

    void set_depth(unsigned int depth_);
    std::shared_ptr<symbol_attribute> enter_symbol(const std::string& name,Symbol_type type);
    std::shared_ptr<symbol_attribute> enter_symbol(const std::string &name, Symbol_type type, Return_type return_type);
    std::shared_ptr<symbol_attribute> retrieve_symbol(const std::string& name)const;
    bool declared_locally(const std::string& name)const;
    std::shared_ptr<symbol_attribute> erase(std::shared_ptr<symbol_attribute> &sym);
    std::shared_ptr<symbol_attribute> add( std::shared_ptr<symbol_attribute> &sym);
    unsigned get_current_scope_size()const;
    void print()const;


private:
    std::shared_ptr<symbol_attribute> enter_symbol(std::shared_ptr<symbol_attribute> oldsym,
                                                   std::shared_ptr<symbol_attribute> newsym);

private:
    unsigned depth_;
    int var_pos_;
    std::shared_ptr<symbol_attribute> current_function_;
    std::vector<std::pair<unsigned ,std::list<std::shared_ptr<symbol_attribute>>>> scope_display_;
    std::map<std::string,std::shared_ptr<symbol_attribute>> symbol_table_{
            {"int",std::make_shared<symbol_attribute>("int",Symbol_type ::reserved)},
            {"return",std::make_shared<symbol_attribute>("return",Symbol_type ::reserved)},
            {"if",std::make_shared<symbol_attribute>("if",Symbol_type ::reserved)},
            {"else",std::make_shared<symbol_attribute>("else",Symbol_type ::reserved)},
            {"while",std::make_shared<symbol_attribute>("while",Symbol_type ::reserved)},
            {"scanf",std::make_shared<symbol_attribute>("scanf",Symbol_type ::reserved)},
            {"printf",std::make_shared<symbol_attribute>("printf",Symbol_type ::reserved)},
            {"void",std::make_shared<symbol_attribute>("void",Symbol_type ::reserved)},
            {"main",std::make_shared<symbol_attribute>("main",Symbol_type ::reserved)}
    };
};
#endif //C0_SYMBOL_TABLE_H
