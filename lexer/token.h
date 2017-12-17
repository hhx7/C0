//
// Created by pi on 17-11-18.
//

#ifndef C0_TOKEN_H
#define C0_TOKEN_H

#include "../constants/symbol.h"
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


    ~token()= default;

};


#endif //C0_TOKEN_H
