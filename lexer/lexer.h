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

    void handler_indent(const std::string &lexeme, Symbol_type symbol_type){

        if(auto res=keywords_.find(lexeme);res==keywords_.end()){
            current_token_->name_=Token_name ::ident;
        }else{
            current_token_->name_=res->second;
        }
        current_token_->attribute_=lexeme;
    }
private:
    int row_{1};
    int col_{0};
    char last_char_;
    std::fstream input_stream_;
    std::shared_ptr<token> current_token_= nullptr;
    Token_name current_symbol_;
    symbol_table& symbol_table_;
    std::map<std::string,Token_name> keywords_{
            {"int",Token_name ::intsym},
            {"return",Token_name ::retsym},
            {"if",Token_name ::ifsym},
            {"else",Token_name ::elsesym},
            {"while",Token_name ::whilesym},
            {"scanf",Token_name ::scanf},
            {"printf",Token_name ::printf},
            {"void",Token_name ::voidsym},
            {"main",Token_name ::mainsym}
    };
};



#endif //C0_LEXER_H
