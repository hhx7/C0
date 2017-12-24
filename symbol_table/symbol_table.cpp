//
// Created by pi on 17-12-10.
//
#include <iostream>
#include <iomanip>
#include "symbol_table.h"

symbol_table::symbol_table()
        : depth_(0),current_function_(nullptr),var_pos_(0) {
    scope_display_.emplace_back(0,std::list<std::shared_ptr<symbol_attribute>>());
}


void symbol_table::open_scope() {
    depth_+=1;
    scope_display_.emplace_back(0,std::list<std::shared_ptr<symbol_attribute>>());
    var_pos_=0;
}

void symbol_table::close_scope() {
    for(auto& sym : scope_display_.at(depth_).second){
        auto presym=sym->get_same_sym_outer_scope();
        erase(sym);
        if(presym!= nullptr){
            add(presym);
        }

    }

    if(current_function_!= nullptr){
        current_function_->set_func_size(var_pos_);
        current_function_= nullptr;
    }
    var_pos_=0;
    scope_display_.at(depth_).second.clear();
    scope_display_.at(depth_).first=0;
    scope_display_.pop_back();
    depth_=depth_-1;
}

auto symbol_table::erase(std::shared_ptr<symbol_attribute> &sym) ->std::shared_ptr<symbol_attribute> {

    unsigned long p=symbol_table_.erase(sym->get_name());
    if(p){
        return sym;
    }else{
        return nullptr;
    }

}

auto symbol_table::add(std::shared_ptr<symbol_attribute> &sym)->std::shared_ptr<symbol_attribute> {
    auto name=sym->get_name();
    auto ret=symbol_table_.insert({name,sym});
    if(!ret.second){
        //symbol_table_.at(name)=sym;
        return nullptr;
    }
    return sym;
}

auto symbol_table::retrieve_symbol(const std::string &name) const->std::shared_ptr<symbol_attribute> {
    if(auto result=symbol_table_.find(name);result!=symbol_table_.end()){
        return result->second;
    }
    return nullptr;
}

std::shared_ptr<symbol_attribute>
symbol_table::enter_symbol(const std::string &name, Symbol_type type) {
    auto oldsym=retrieve_symbol(name);
    auto newsym=std::make_shared<symbol_attribute>(name,type);
    return enter_symbol(oldsym,newsym);
}

bool symbol_table::declared_locally(const std::string &name) const {
    for(auto sym:scope_display_.at(depth_).second){
        if(sym->get_name()==name){
            return true;
        }
    }
    return false;
}

unsigned int symbol_table::get_depth() const {
    return depth_;
}

void symbol_table::set_depth(unsigned int depth_) {
    symbol_table::depth_ = depth_;
}


std::shared_ptr<symbol_attribute>
symbol_table::enter_symbol(const std::string &name, symbol::Symbol_type type, function::Return_type return_type) {
    auto oldsym=retrieve_symbol(name);
    auto newsym=std::make_shared<symbol_attribute>(name,type,return_type);
    return enter_symbol(oldsym,newsym);
}

std::shared_ptr<symbol_attribute> symbol_table::enter_symbol(std::shared_ptr<symbol_attribute> oldsym,
                                                             std::shared_ptr<symbol_attribute> newsym) {
    if(oldsym!= nullptr && oldsym->get_depth()==depth_){
        throw std::logic_error(" Duplicate defination of"+oldsym->get_name());
    }else{
        if(newsym->get_symbol_type()==Symbol_type::variable){
            ++var_pos_;
            newsym->set_var_pos(var_pos_);
            scope_display_.at(depth_).first+=1;
        } else if(newsym->get_symbol_type()==Symbol_type::function){
            current_function_=newsym;
        }
        newsym->set_depth(depth_);
        scope_display_.emplace_back(0,std::list<std::shared_ptr<symbol_attribute>>());
        scope_display_.at(depth_).second.push_back(newsym);

        if(oldsym==nullptr){
            add(newsym);
        }else{
            erase(oldsym);
            add(newsym);
            newsym->set_same_sym_outer_scope(oldsym);
        }
    }
    return newsym;
}

void symbol_table::print()const{
    std::cout << std::endl << "-----------------------------------Print Symbol Table-------------------------------"
              << std::endl;
    const int space_size=12;
    std::cout<<std::left<<std::setw(space_size)<<"name"<<std::setw(space_size)<<"type"<<std::setw(space_size)<<"var_pos"
             <<std::setw(space_size)<<"return_type"<<std::setw(space_size)<<"func_size"<<std::setw(space_size)<<"depth"<<std::endl;
    for(auto beg=symbol_table_.begin();beg!=symbol_table_.end();++beg){
        auto sym=beg->second;
        std::cout << std::setw(space_size) << sym->get_name() << std::setw(space_size) << sym->get_symbol_type()
                  << std::setw(space_size) << sym->get_var_pos()
                  << std::setw(space_size) << sym->get_return_type() << std::setw(space_size) << sym->get_func_size()
                  << std::setw(space_size) << sym->get_depth() << std::endl;
    }
}

unsigned symbol_table::get_current_scope_size() const {
    return scope_display_.at(depth_).first;
}



