//
// Created by pi on 17-11-18.
//

#ifndef C0_LEXER_H
#define C0_LEXER_H

#include "../constants/symbol.h"
#include "token.h"
#include "../symbol_table/symbol_table.h"
#include <memory>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

class lexer : virtual private symbol{

public:

    lexer(const std::string& file_name,symbol_table& st);

    std::shared_ptr<token> next_token();

    ~lexer(){input_stream_.close();}

private:
    bool next_char();
    bool is_skipper_symbol();
    bool is_punctuator_token();
    bool is_operator_token();

    void get_identifier_or_keyword_token();
    void get_literal_token();
    void get_operator_token();
    void get_punctuator_token();

    void insert_to_symbol_table(const std::string& lexeme,Symbol_type symbol_type){
        if(auto iter=symbol_table_.find(lexeme);iter==symbol_table_.end()){

            symbol_table_.insert(lexeme,symbol_attribute(Symbol_type::variable,Token_name::ident));
            current_token_->name_=Token_name ::ident;
            current_token_->attribute_=lexeme;
        }else{
            auto symbol_detail=iter->second;
            auto attribute=symbol_detail.get_attribute();
            current_token_->name_=std::any_cast<Token_name >(attribute);
            current_token_->attribute_=lexeme;
        }
    }
private:
    int row_{1};
    int col_{0};
    char last_char_;
    std::fstream input_stream_;
    std::shared_ptr<token> current_token_= nullptr;
    Token_name current_symbol_;
    symbol_table& symbol_table_;
};



#endif //C0_LEXER_H
