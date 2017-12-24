//
// Created by pi on 17-11-18.
//

#ifndef C0_TOKEN_H
#define C0_TOKEN_H

#include "../symbol_table/symbol_table.h"

#include <variant>


#include <string>
#include <map>
#include <iostream>




class token : virtual private symbol{

public:
    Token_name name_;
    int col_=0;
    int row_=0;
    std::variant<char,int,std::string> attribute_;
public:
    token()= default;
    token(int row , int col , Token_name name):row_(row) , col_(col) , name_(name){}
    token(int row , int col ):row_(row) , col_(col) , name_(Token_name ::nul){}

    Token_name get_name()const {
        return name_;
    }
    std::string visit_string() const{

        std::string value;
        std::visit([&](auto& val){
            using T=std::remove_cv_t <std::remove_reference_t <decltype(val)>>;
            if constexpr (std::is_same_v<T,std::string>){
                value=val;
            }
        },attribute_);
        return value;
    }

    int visit_number() const{

        int value;
        std::visit([&](auto& val){
            using T=std::remove_cv_t <std::remove_reference_t <decltype(val)>>;
            if constexpr (std::is_same_v<T,int>){
                value=val;
            }
        },attribute_);
        return value;
    }
    ~token()= default;

};


#endif //C0_TOKEN_H
